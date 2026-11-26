PYTHON ?= python3

.PHONY: test clean
# Rebuild and hash-check all source sections; requires GNU Arm Embedded 13.3.
test:
	$(PYTHON) tests/test_sources.py

clean:
	rm -rf build Debug Release
