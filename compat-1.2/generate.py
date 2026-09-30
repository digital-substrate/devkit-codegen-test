#!/usr/bin/env python3
"""Render the frozen model, to read the 1.2 database back with what the generation produces today.

Only C++ is rendered for now; -p and -t are accepted so that `check.py` can pass the same
call to every site, and they report that there is nothing to render yet.
"""
import argparse, subprocess, sys
from pathlib import Path

from dsviper import DSMBuilder

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
from models import MODELS
from render import jar, TEMPLATES, LAB_FEATURES

HERE = Path(__file__).resolve().parent
SPEC = MODELS["compat-1.2"]

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("-c", "--cpp", action="store_true", help="Generate C++")
parser.add_argument("-p", "--python", action="store_true", help="(not yet)")
parser.add_argument("-t", "--typescript", action="store_true", help="(not yet)")
arguments = parser.parse_args()

report, dsm, definitions = DSMBuilder.assemble(str(HERE / "definitions")).parse()
if report.has_error():
    for e in report.errors():
        print(repr(e))
    raise SystemExit(1)

DSM_PATH = HERE / f'{SPEC["namespace"]}.dsm.json'
DSM_PATH.write_text(dsm.json_encode())

sys.path.insert(0, str(TEMPLATES))
import resolve                                                          # noqa: E402

CPP_OUT = HERE / "cpp" / "generated"


def resources_hpp():
    """The model, as bytes, in `<Namespace>_resources_definitions` -- what the templates expect."""
    encoded = bytes(definitions.encode().encoded())
    lines = [", ".join(f"0x{b:02x}" for b in encoded[i:i + 12]) for i in range(0, len(encoded), 12)]
    ns = SPEC["namespace"]
    (CPP_OUT / f"{ns}_resources.hpp").write_text(
        f"#ifndef {ns}_resources_hpp\n#define {ns}_resources_hpp\n\n#include <cstddef>\n\n"
        f"inline constexpr unsigned char {ns}_resources_definitions[] = {{\n "
        + ",\n ".join(lines) + f"\n}};\n\n#endif\n")


if arguments.cpp:
    print("** Render C++")
    JAR = jar()
    print(f"using kibo: {Path(JAR).name}")
    CPP_OUT.mkdir(parents=True, exist_ok=True)
    for stg in resolve.templates("cpp", SPEC["cpp"], extra=[LAB_FEATURES]):
        subprocess.run(["java", "-jar", JAR, "-c", "cpp", "-n", SPEC["namespace"],
                        "-d", str(DSM_PATH), "-t", str(stg), "-o", str(CPP_OUT)], check=True)
    resources_hpp()

for language, requested in (("python", arguments.python), ("typescript", arguments.typescript)):
    if requested:
        print(f"** {language}: not yet -- reading back starts with C++")
