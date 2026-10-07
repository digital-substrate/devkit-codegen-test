#!/usr/bin/env python3
"""One entry point: the five sites, rendered and tested.

There are twelve `run_test.sh` and five `kibo.toml`; this renders every site through
kibo-project, runs every test, and gives a single verdict.

    check.py                render the five sites and run every test
    check.py features       one site only
    check.py --no-render    test what is already rendered, without regenerating
    check.py --edge-names   also run the edge names bench, a few minutes

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

Parity, `tools/parity.py`: on every site with both packages, the Python and the TypeScript
packages expose the same members and document the same ones, the idioms the pack lists aside.

Across versions, `tools/crossversion.py`: a service built with the 1.2 line, called by the kibo 2
clients -- the wire both lines share.

Template Model, `tools/template_model.py`: every value a Template Model 1 template reads, read
again through Model 2 -- each change one the documentation lists.

Typing, `tools/typing_floor.py`: every site's Python package passes `mypy --strict` for this
Python and for the oldest its pyproject declares, and its tests run under that oldest Python when
one is at hand (PYTHON_FLOOR, or `python3.10` with dsviper). The TypeScript packages already
compile with their generated `"strict": true`.

Edge names, `tools/edge_names.py`: one small model per name a target may not take -- a keyword,
a name of the pack's own code, a primitive's name, a documentation with quotes -- in each family
of names; each target's output judged ok, refused explicitly, or silently wrong, and compared with
`tools/edge_names.expected`, where each defect is named. It renders some seven hundred small
outputs, so it runs only on request (`--edge-names`): when kibo's naming, a pack's reserved names
or the validation it declares change.

None of the five proves that a developer of the target audience finds the output usable.
`pip install` and `tsc --strict` in an outside consumer are tested by hand for now, not here.
"""
import argparse
import os
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent

# Each site declares its generation in a `kibo.toml`, rendered by kibo-project, from the
# sibling checkout unless KIBO_PROJECT names the script.
KIBO_PROJECT = Path(os.environ.get("KIBO_PROJECT") or HERE.parent / "kibo-project" / "kibo_project.py")

sys.path.insert(0, str(HERE / "tools"))
from models import SITES                                # noqa: E402
from parity import SITES as PARITY_SITES                # noqa: E402
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
    parser.add_argument("--edge-names", action="store_true",
                        help="also run the edge names bench (a few minutes)")
    arguments = parser.parse_args()

    sites = [arguments.site] if arguments.site else list(SITES)
    failures = []

    for site in sites:
        print(f"\n── {site}")
        directory = HERE / site

        if not arguments.no_render:
            code, output = run([sys.executable, str(KIBO_PROJECT), "generate"], directory)
            # kibo renders past what it cannot resolve -- a property a template reads that the
            # model does not have -- and says so; the text it wrote has a hole there. A first-party
            # template owes none.
            warnings = [line for line in output.splitlines() if line.strip().startswith("kibo: /")]
            if warnings and not code:
                code, output = 1, "\n".join(warnings)
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

    # Parity: the Python and TypeScript packages of a site expose the same surface, the idioms
    # of the pack's DESIGN.md §7 aside. Read from what the sites above rendered.
    parity_sites = [s for s in sites if s in PARITY_SITES]
    if parity_sites:
        print("\n── parity")
        code, output = run([sys.executable, "tools/parity.py", *parity_sites], HERE)
        for line in output.splitlines():
            print(f"   {GREEN if line.startswith('ok') else RED}{line.rstrip()}{RESET}")
        if code:
            failures.append("parity")

    # The feature selection, in addition to the sites. No site renders `Base` without `Pool` on
    # a model that declares pools, yet that is what a pure Python application asks for.
    print("\n── feature selection")
    code, output = run([sys.executable, "tools/selection.py"], HERE)
    for line in output.splitlines():
        print(f"   {GREEN if 'ok' in line else RED}{line.strip()}{RESET}")
    if code:
        failures.append("selection")

    # Across versions: a service built with the 1.2 line, called by the kibo 2 clients. Skipped,
    # and said so, when the 1.2 line is not at hand.
    print("\n── across versions")
    code, output = run([sys.executable, "tools/crossversion.py"], HERE)
    for line in output.splitlines():
        colour = GREEN if line.startswith("ok") else (GREY if line.startswith("skipped") else RED)
        print(f"   {colour}{line.strip()}{RESET}")
    if code not in (0, 2):
        failures.append("crossversion")

    # The Python packages are fully annotated down to the oldest Python they declare, and run
    # there when such an interpreter is at hand. Skipped, and said so, without mypy.
    print("\n── typing")
    code, output = run([sys.executable, "tools/typing_floor.py"], HERE)
    for line in output.splitlines():
        colour = GREEN if line.startswith("ok") else (GREY if line.startswith("skipped") else RED)
        print(f"   {colour}{line.rstrip()}{RESET}")
    if code not in (0, 2):
        failures.append("typing")

    # Edge names: each target's verdict on names the DSM accepts, against the recorded ones.
    # On request only; skipped, and said so, without mypy, a C++ compiler or the TypeScript tooling.
    print("\n── edge names")
    if arguments.edge_names:
        code, output = run([sys.executable, "tools/edge_names.py"], HERE)
        for line in output.splitlines():
            colour = GREEN if line.startswith("ok") else (GREY if line.startswith("skipped") else RED)
            print(f"   {colour}{line.rstrip()}{RESET}")
        if code not in (0, 2):
            failures.append("edge names")
    else:
        print(f"   {GREY}skipped: --edge-names runs it, when naming or a pack's reserved names change{RESET}")

    # Template Model 1 to 2: every value a Model 1 template reads, through Model 2; each change
    # must be one the documentation lists. Skipped, and said so, without a kibo 1.2 jar.
    print("\n── template model")
    code, output = run([sys.executable, "tools/template_model.py"], HERE)
    for line in output.splitlines():
        colour = GREEN if line.startswith("ok") else (GREY if line.startswith("skipped") else RED)
        print(f"   {colour}{line.rstrip()}{RESET}")
    if code not in (0, 2):
        failures.append("template model")

    print()
    if failures:
        print(f"{RED}{len(failures)} failure(s): {', '.join(failures)}{RESET}")
        return 1
    print(f"{GREEN}{'all pass':>42}{RESET}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
