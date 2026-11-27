import json
import os
import subprocess
import sys
import unittest
from pathlib import Path

CASE = Path(__file__).resolve().parent
TARGET_SHA = "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752"


class NewTargetVerificationTests(unittest.TestCase):
    def test_adc_c_baseline_stays_unaccepted(self):
        accepted = json.loads((CASE / "evidence/accepted.json").read_text())
        self.assertNotIn("FUN_08003cec", {item["name"] for item in accepted["functions"]})
        reconstructed = json.loads((CASE / "evidence/reconstructed_assembly_accepted.json").read_text())
        self.assertEqual(reconstructed["classification"], "reconstructed_assembly_not_C")
        self.assertEqual(reconstructed["assembly_bytes"], 2176)

    def test_full_image_builder_emits_byte_identical_candidate(self):
        result = subprocess.run([sys.executable, str(CASE / "full_image/build.py")], cwd=CASE,
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("differing bytes: 0", result.stdout)
        full = json.loads((CASE / "full_image/build/verification.json").read_text())
        target = (CASE.parents[1] / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
        self.assertTrue(full["candidate_binary_written"])
        self.assertTrue(full["match"])
        self.assertEqual(full["actual_size"], len(target))
        self.assertEqual(full["actual_sha256"], TARGET_SHA)
        self.assertEqual(full["different_bytes"], 0)
        self.assertEqual(full["unverified_image_bytes"], 0)
        self.assertFalse(full["single_link_from_all_sources"])
        candidate = CASE / full["candidate_binary"]
        self.assertTrue(candidate.is_file())
        self.assertEqual(candidate.read_bytes(), target)

    def test_harness_discards_unreferenced_functions_from_translation_unit(self):
        source = CASE / "candidates/src/core.c"
        result = subprocess.run([
            sys.executable, str(CASE / "tools/harness.py"), "HAL_IncTick", str(source),
            "0x0800296c", "36", "-O0", "--defsym", "uwTick=0x2000035c",
            "--defsym", "uwTickFreq=0x20000008"
        ], cwd=CASE, capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("PASS HAL_IncTick: exact 36 bytes", result.stdout)

    def test_rebuilds_and_reports_only_exact_target_sections(self):
        result = subprocess.run([sys.executable, str(CASE / "verify.py")], cwd=CASE,
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        report = json.loads((CASE / "build/verification.json").read_text())
        target = (CASE.parents[1] / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
        self.assertEqual(report["firmware_sha256"], TARGET_SHA)
        self.assertEqual(report["image_bytes"], len(target))
        manifest = json.loads((CASE / "evidence/accepted.json").read_text())
        expected_functions = len(manifest["functions"])
        expected_bytes = sum(item["size"] for item in manifest["functions"])
        self.assertEqual(report["matched_C_functions"], expected_functions)
        init_array = next(item for item in manifest["functions"] if item["name"] == "FUN_080095f4")
        self.assertEqual((init_array["address"], init_array["size"]), ("0x080095f4", 72))
        init_array_match = next(item for item in report["matches"] if item["name"] == "FUN_080095f4")
        self.assertIn("14.3.1", init_array_match["compiler"])
        self.assertIn("14.3.1", " ".join(report["compilers"]))

        runtime = json.loads((CASE / "evidence/runtime_accepted.json").read_text())
        expected_runtime_bytes = sum(item["size"] for item in runtime["blocks"])
        runtime_names = {item["name"] for item in runtime["blocks"]}
        self.assertIn("crtbegin.o:.init_array", runtime_names)
        self.assertIn("crtbegin.o:.fini_array", runtime_names)
        self.assertEqual(report["matched_runtime_bytes"], expected_runtime_bytes)
        self.assertEqual(report["matched_runtime_blocks"], len(runtime["blocks"]))

        data = json.loads((CASE / "evidence/data_accepted.json").read_text())
        expected_data_bytes = sum(item["size"] for item in data["blocks"])
        data_ranges = {item["name"]: (item["address"], item["size"]) for item in data["blocks"]}
        self.assertEqual(data_ranges["clock prescaler lookup tables"], ("0x08009654", 32))
        self.assertEqual(data_ranges["initvals (initialized data)"], ("0x0800967c", 12))
        self.assertEqual(report["matched_data_bytes"], expected_data_bytes)
        self.assertEqual(report["matched_data_blocks"], len(data["blocks"]))

        vendor_startup = json.loads((CASE / "evidence/assembly_accepted.json").read_text())
        self.assertEqual(vendor_startup["assembly_bytes"], 80)
        self.assertEqual(vendor_startup["blocks"][0]["kind"], "vendor_startup_assembly")
        self.assertEqual(len(report["vendor_startup_matches"]), 1)
        self.assertEqual(report["vendor_startup_matches"][0]["address"], "0x08002874")
        self.assertEqual(report["matched_vendor_startup_bytes"], 80)

        reconstructed = json.loads((CASE / "evidence/reconstructed_assembly_accepted.json").read_text())
        self.assertEqual(reconstructed["classification"], "reconstructed_assembly_not_C")
        self.assertEqual(reconstructed["assembly_bytes"], 2176)
        self.assertIn("ADC function only", reconstructed["authorization_context"])
        self.assertEqual(len(reconstructed["blocks"]), 1)
        self.assertTrue(reconstructed["blocks"][0]["matched"])
        self.assertEqual(reconstructed["blocks"][0]["name"], "FUN_08003cec")
        self.assertEqual(reconstructed["blocks"][0]["address"], "0x08003cec")
        self.assertEqual(report["reconstructed_assembly_bytes"], 2176)
        self.assertEqual(len(report["assembly_matches"]), 1)
        self.assertEqual(report["assembly_matches"][0]["kind"], "reconstructed_assembly_not_C")
        self.assertIn("FUN_08003cec", {item["name"] for item in report["pending"]})

        self.assertEqual(report["matched_C_bytes_including_pools"], expected_bytes)
        combined = expected_bytes + expected_runtime_bytes + expected_data_bytes + 80 + 2176
        expected_gaps = {
            "0x08000a94": 4, "0x08001652": 2, "0x080028f6": 2, "0x08002c8a": 2,
            "0x080034ae": 2, "0x08004e06": 2, "0x08004eca": 2, "0x08006676": 2,
            "0x080091fe": 2, "0x0800934e": 2,
        }
        linker_gaps = {item["gap_start"]: item["gap_bytes"] for item in report["linker_gap_ranges"]}
        gap_bytes = sum(expected_gaps.values())
        self.assertEqual(linker_gaps, expected_gaps)
        self.assertEqual(report["matched_linker_gap_bytes"], gap_bytes)
        self.assertEqual(report["matched_image_bytes_total"], combined + gap_bytes)
        self.assertEqual(report["pending_detected_functions"], len(report["pending"]))
        self.assertLess(report["pending_detected_functions"], report["detected_functions"])
        nmi = next(item for item in report["matches"] if item["name"] == "NMI_Handler")
        self.assertEqual(nmi["address"], "0x080025d2")
        self.assertEqual(report["image_percentage_from_matched_C"], round(100 * expected_bytes / len(target), 4))
        self.assertEqual(report["image_percentage_from_C_plus_runtime"],
                         round(100 * (expected_bytes + expected_runtime_bytes) / len(target), 4))
        self.assertEqual(report["image_percentage_total"], round(100 * (combined + gap_bytes) / len(target), 4))

        full = json.loads((CASE / "full_image/build/verification.json").read_text())
        self.assertEqual(full["matched_C_entries"], expected_functions)
        self.assertEqual(full["runtime_bytes"], expected_runtime_bytes)
        self.assertEqual(full["verified_C_plus_runtime_bytes"], expected_bytes + expected_runtime_bytes)
        self.assertEqual(full["verified_C_plus_runtime_data_bytes"], expected_bytes + expected_runtime_bytes + expected_data_bytes)
        self.assertEqual(full["verified_C_plus_runtime_data_startup_bytes"], expected_bytes + expected_runtime_bytes + expected_data_bytes + 80)
        self.assertEqual(full["verified_C_plus_runtime_data_startup_reconstructed_assembly_bytes"], combined)
        self.assertEqual(full["verified_linker_gap_bytes"], gap_bytes)
        self.assertEqual(full["verified_all_categories_plus_linker_alignment_bytes"], combined + gap_bytes)
        self.assertEqual(full["matched_image_bytes_total"], combined + gap_bytes)
        self.assertEqual(full["unverified_image_bytes"], len(target) - combined - gap_bytes)
        self.assertEqual(full["reconstructed_assembly_entries"], 1)
        self.assertEqual(full["reconstructed_assembly_bytes"], 2176)
        self.assertEqual(full["vendor_startup_entries"], 1)
        self.assertEqual(full["actual_size"], 0)
        self.assertFalse(full["match"])
        self.assertFalse(full["single_link_from_all_sources"])


if __name__ == "__main__":
    unittest.main()
