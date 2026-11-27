PYTHON ?= python3
EXPECTED_BIN := bin/PPC_PMV_SD2_reverse_engineering.bin
CANDIDATE_BIN := reconstruction/new_target/full_image/build/candidate.bin

.PHONY: firmware test clean

firmware:
	$(PYTHON) reconstruction/new_target/full_image/build.py
	cmp -s $(CANDIDATE_BIN) $(EXPECTED_BIN)
	install -m 0644 $(CANDIDATE_BIN) $(EXPECTED_BIN)
	(cd bin && sha256sum -c PPC_PMV_SD2_reverse_engineering.bin.sha256)

test:
	$(PYTHON) -m unittest -v reconstruction/new_target/test_verify.py
	$(PYTHON) -m unittest -v tests/test_project_build.py

clean:
	$(PYTHON) -c 'from pathlib import Path; import shutil; root=Path("reconstruction/new_target"); [shutil.rmtree(p) for p in sorted(root.rglob("build"), key=lambda x: len(x.parts), reverse=True) if p.is_dir()]'
