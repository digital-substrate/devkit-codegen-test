#!/usr/bin/env python3
"""The generated Python is fully annotated, down to the oldest Python it declares.

For every site with a Python package, as rendered:

  1. `mypy --strict` on the package, for the running Python;
  2. `mypy --strict --python-version <floor>`, the floor being the package's own
     `requires-python` (pyproject.toml) -- an annotation newer than the floor fails here,
     though nothing fails at run time (the package postpones its annotations);
  3. the site's Python tests under an interpreter of the floor: PYTHON_FLOOR names one that
     has dsviper installed, else `python<floor>` on the PATH is used if it imports dsviper.

1 and 2 need mypy; 3 is skipped, and says so, without an interpreter of the floor.
Exit 0 when everything that ran passed, 1 on a failure, 2 when nothing could run.
"""

from __future__ import annotations

import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
LAB = HERE.parent
sys.path.insert(0, str(HERE))

from models import SITES  # noqa: E402


def skip(reason: str) -> int:
    print(f"skipped: {reason}")
    return 2


def package(site: str) -> tuple[Path, str, str] | None:
    """(generated dir, package name, floor) of a site's Python package, or None."""
    generated = LAB / site / "python" / "generated"
    pyproject = generated / "pyproject.toml"
    if not pyproject.is_file():
        return None
    text = pyproject.read_text()
    name = re.search(r'^name\s*=\s*"([^"]+)"', text, re.M)
    floor = re.search(r'^requires-python\s*=\s*">=\s*([\d.]+)', text, re.M)
    if not name or not floor:
        return None
    return generated, name.group(1), floor.group(1)


def mypy(generated: Path, name: str, cache: Path, version: str | None) -> tuple[bool, str]:
    command = [sys.executable, "-m", "mypy", "--strict", "--cache-dir", str(cache), name]
    if version:
        command[3:3] = ["--python-version", version]
    out = subprocess.run(command, cwd=generated, capture_output=True, text=True)
    last = (out.stdout.strip().splitlines() or [out.stderr.strip()])[-1]
    return out.returncode == 0, last


def floor_interpreter(floor: str) -> Path | None:
    """An interpreter of the floor that imports dsviper, or None."""
    candidates = [os.environ.get("PYTHON_FLOOR"), shutil.which(f"python{floor}")]
    for candidate in filter(None, candidates):
        check = subprocess.run([candidate, "-c", "import sys, dsviper; print('%d.%d' % sys.version_info[:2])"],
                               capture_output=True, text=True)
        if check.returncode == 0 and check.stdout.strip() == floor:
            return Path(candidate)
    return None


def run_tests(site: str, interpreter: Path) -> tuple[bool, str]:
    """The site's python/run_test.sh, with `python3` meaning the floor's interpreter."""
    with tempfile.TemporaryDirectory(prefix="python-floor-") as shim:
        # A script, not a symlink: a venv's interpreter finds its venv from the path it is
        # called by, so a link elsewhere would lose dsviper.
        launcher = Path(shim) / "python3"
        launcher.write_text(f'#!/bin/sh\nexec "{interpreter}" "$@"\n')
        launcher.chmod(0o755)
        env = {**os.environ, "PATH": f"{shim}{os.pathsep}{os.environ['PATH']}"}
        script = LAB / site / "python" / "run_test.sh"
        out = subprocess.run(["bash", str(script)], cwd=script.parent, env=env,
                             capture_output=True, text=True)
    tail = (out.stdout + out.stderr).strip().splitlines()
    return out.returncode == 0, (tail[-1] if tail else "")


def main() -> int:
    sites = [(site, found) for site in SITES if (found := package(site))]
    if not sites:
        return skip("no rendered Python package")
    if subprocess.run([sys.executable, "-m", "mypy", "--version"], capture_output=True).returncode:
        return skip(f"no mypy for {sys.executable}")

    failed = False
    floors = {floor for _, (_, _, floor) in sites}
    interpreters = {floor: floor_interpreter(floor) for floor in floors}
    with tempfile.TemporaryDirectory(prefix="mypy-") as cache:
        for site, (generated, name, floor) in sites:
            for version in (None, floor):
                ok, last = mypy(generated, name, Path(cache) / (version or "current"), version)
                label = f"Python {version}" if version else "this Python"
                print(f"{'ok  ' if ok else 'FAIL'} {site}: mypy --strict for {label}: {last}")
                failed |= not ok
            interpreter = interpreters[floor]
            if interpreter is None:
                print(f"skipped: {site}: tests under Python {floor} "
                      f"(no python{floor} with dsviper; set PYTHON_FLOOR)")
                continue
            ok, last = run_tests(site, interpreter)
            print(f"{'ok  ' if ok else 'FAIL'} {site}: tests under Python {floor}: {last}")
            failed |= not ok
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
