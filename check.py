#!/usr/bin/env python3
"""One entry point: the five sites, rendered and tested.

There are twelve `run_test.sh` and five `generate.py`; this runs them all and gives a
single verdict.

    check.py                render the five sites and run every test
    check.py features       one site only
    check.py --no-render    test what is already rendered, without regenerating

What each site proves, and what it does not:

  features     the whole type system in one namespace, and the project's two suites
               474 Python tests, 465 TypeScript, written before this work and ported once
               proves nothing about pools: the model declares none
  service      two pools, and a running service: a C++ server, three clients
               the only test where generated code crosses a wire
               proves nothing about homonyms: only one meaningful namespace
  namespaces   six namespaces and their edges; two declare the same name
               the smallest statement of this work
               proves nothing about composites: its types do not cross
  crossing     a reference crossing a namespace INSIDE a composite
               a `map<Core::Grade, Parts::Colour>`, a `variant<Core::Colour, ...>`
               proves nothing about the service or the suites

None of the five proves that a developer of the target audience finds the output usable.
`pip install` and `tsc --strict` in an outside consumer are tested by hand for now, not here.
"""
import argparse
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent

# The site name, and what its `generate.py` expects besides the flags. `features` takes its
# `.dsm` as a positional argument; the others read it from `definitions/`.
SITES = {
    "features": ["all.dsm"],
    "service": [],
    "namespaces": [],
    "crossing": [],
    "compat-1.2": [],
}
LANGUAGES = ("cpp", "python", "typescript")

GREEN, RED, GREY, RESET = "\033[32m", "\033[31m", "\033[90m", "\033[0m"


def result(output: str) -> str:
    """What the test said, in a few words.

    Each suite reports in its own format, and a wrong guess is worse than none: a C++ program
    that prints `ok` once has not passed "1 assertion", it compiled, linked and ran. The formats
    are therefore recognised explicitly, and anything unrecognised says so.
    """
    lines = [l.strip() for l in output.splitlines() if l.strip()]

    if any(l.startswith("add(32,10)") for l in lines):
        return "client ↔ server"

    for line in lines:
        if line.startswith("Ran ") and "test" in line:
            return f"{line.split()[1]} project tests"
        if line.startswith("ℹ pass "):
            return f"{line.split()[-1]} tests"

    if lines and lines[-1] == "ok":
        return "compiles, links, runs"

    oks = sum(1 for l in lines if l.startswith("ok"))
    if oks:
        return f"{oks} assertions"
    return f"passes, no recognised summary ({lines[-1][:28]})" if lines else "silent"


def run(command, directory):
    r = subprocess.run(command, cwd=directory, capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("site", nargs="?", choices=sorted(SITES), help="test only this site")
    parser.add_argument("--no-render", action="store_true",
                        help="test what is already rendered")
    arguments = parser.parse_args()

    sites = [arguments.site] if arguments.site else list(SITES)
    failures = []

    for site in sites:
        print(f"\n── {site}")
        directory = HERE / site

        if not arguments.no_render:
            code, output = run([sys.executable, "generate.py", *SITES[site], "-c", "-p", "-t"],
                               directory)
            if code:
                print(f"   {RED}render      fails{RESET}")
                for line in output.splitlines()[-6:]:
                    print(f"      {line}")
                failures.append(f"{site}/render")
                continue

        for language in LANGUAGES:
            script = directory / language / "run_test.sh"
            if not script.exists():
                print(f"   {GREY}{language:11} no test{RESET}")
                continue

            code, output = run(["./run_test.sh"], script.parent)
            if code:
                print(f"   {RED}{language:11} FAILED{RESET}")
                for line in output.splitlines()[-8:]:
                    print(f"      {line}")
                failures.append(f"{site}/{language}")
            else:
                print(f"   {GREEN}{language:11} {result(output)}{RESET}")

    # The feature selection, in addition to the sites. No site renders `Base` without `Pool` on
    # a model that declares pools, yet that is what a pure Python application asks for.
    print("\n── feature selection")
    code, output = run([sys.executable, "tools/selection.py"], HERE)
    for line in output.splitlines():
        print(f"   {GREEN if 'ok' in line else RED}{line.strip()}{RESET}")
    if code:
        failures.append("selection")

    print()
    if failures:
        print(f"{RED}{len(failures)} failure(s): {', '.join(failures)}{RESET}")
        return 1
    print(f"{GREEN}{'all pass':>42}{RESET}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
