"""End-to-end checks for the downloadable CubeIDE reconstruction project."""
from __future__ import annotations

import hashlib
import subprocess
import unittest
from pathlib import Path
from xml.etree import ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
PROJECT_NAME = "PPC_PMV_SD2_reverse_engineering"
OUTPUT = ROOT / "bin" / f"{PROJECT_NAME}.bin"
EXPECTED_SIZE = 38536
EXPECTED_SHA256 = "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752"


class DownloadableProjectTests(unittest.TestCase):
    def test_cubeide_project_name_matches_repository(self):
        project = ET.parse(ROOT / ".project").getroot()
        self.assertEqual(project.findtext("name"), PROJECT_NAME)

    def test_make_firmware_rebuilds_the_pinned_image(self):
        result = subprocess.run(
            ["make", "firmware"], cwd=ROOT, text=True,
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
        )
        self.assertEqual(result.returncode, 0, result.stdout)
        self.assertTrue(OUTPUT.is_file(), "firmware target did not create the requested BIN")
        data = OUTPUT.read_bytes()
        self.assertEqual(len(data), EXPECTED_SIZE)
        self.assertEqual(hashlib.sha256(data).hexdigest(), EXPECTED_SHA256)


if __name__ == "__main__":
    unittest.main()
