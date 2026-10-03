#!/usr/bin/env python3
"""The Python and TypeScript packages of each site expose the same surface.

The two packages are one design in two idioms (kibo-template-viper, DESIGN.md §7). This
script lists every public member of both packages of a site -- the classes, their members,
an attachment's operations, the containers, the runtime the package re-exports -- and
compares them by name, case and underscores aside (`diff_keys` is `diffKeys`, `f_e` is
`f_E`), along with whether each carries documentation.

A difference is either one of the idioms listed below, each with its reason, or drift: a
member one language has and the other lacks, or documents and the other does not. Drift
fails. An idiom is added here only with the row of DESIGN.md §7 that states it.

    parity.py               every site with both packages
    parity.py features      one site
"""
import importlib
import inspect
import enum
import json
import os
import pkgutil
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SITES = ("features", "service", "namespaces", "crossing")

# The same operation, named by each language's idiom: (Python, TypeScript), normalised.
PAIRS = {
    ("delete", "del"),          # `del` is a Python keyword; TypeScript says `del`, as the C++
    ("contains", "has"),        # a container: `has`, as a native Set or Map
    ("items", "entries"),       # a map, an xarray
    ("tolist", "toarray"),      # a sequence as the language's list
    ("totuple", "toarray"),
}
# What only one language spells as a method, the other having it as a protocol.
PYTHON_ONLY = {
    "empty",                    # TypeScript: `size === 0`
}
TYPESCRIPT_ONLY = {
    "equals", "hashkey", "compare", "tostring", "tojson",   # Python: ==, hash(), <, repr()
    "length",                   # Python: len()
    "concat",                   # Python: v + w
    "setcolumn",                # Python: m[c] = column
}


def norm(name: str) -> str:
    return name.replace("_", "").lower()


# -- the Python surface, read in a process that imports the package ----------------------

def python_surface(package: str) -> list[tuple[str, str, str, str, int]]:
    root = importlib.import_module(package)
    rows: list[tuple[str, str, str, str, int]] = []

    def owned(cls: type) -> bool:
        return getattr(cls, "__module__", "").split(".")[0] == package

    def documented(target: object) -> int:
        return 1 if inspect.getdoc(target) else 0

    def members(module: str, name: str, prefix: str, cls: type, depth: int) -> None:
        names: set[str] = set()
        for base in cls.__mro__:
            if owned(base):
                names |= set(vars(base))
        for member in sorted(names):
            if member.startswith("_"):
                continue
            raw = inspect.getattr_static(cls, member)
            if issubclass(cls, enum.Enum) and isinstance(raw, cls):
                rows.append((module, name, prefix + member, "static", 0))
                continue
            target: object
            if isinstance(raw, (classmethod, staticmethod)):
                kind, target = "static", raw.__func__
            elif isinstance(raw, property) or inspect.isfunction(raw):
                kind, target = "instance", raw
            else:
                kind, target = "static", None
            rows.append((module, name, prefix + member, kind,
                         documented(target) if target is not None else 0))
            if depth > 0 and target is None:
                held = getattr(cls, member)
                if not inspect.isclass(held) and owned(type(held)):
                    members(module, name, f"{prefix}{member}.", type(held), depth - 1)

    modules = [root] + [importlib.import_module(m.name)
                        for m in pkgutil.walk_packages(root.__path__, package + ".")
                        if "._codegen" not in m.name]
    for module in modules:
        relative = module.__name__[len(package) + 1:].replace(".", "/") or "index"
        listed = getattr(module, "__all__", None)
        for name, value in list(vars(module).items()):
            if name.startswith("_") or inspect.ismodule(value):
                continue
            home = getattr(value, "__module__", module.__name__)
            if listed is not None:
                if name not in listed:
                    continue
                if home != module.__name__ and home.startswith(package + ".") and "._codegen" not in home:
                    continue                                # counted where it is defined
            elif getattr(value, "__module__", module.__name__) != module.__name__:
                continue                                    # an import, not an export
            if inspect.isclass(value):
                rows.append((relative, name, "", "class", 1 if value.__dict__.get("__doc__") else 0))
                members(relative, name, "", value, 1)
            elif inspect.isfunction(value):
                rows.append((relative, name, "", "function", documented(value)))
            else:
                rows.append((relative, name, "", "const", 0))
    return rows


# -- the comparison ----------------------------------------------------------------------

def typescript_surface(site: Path) -> list[tuple[str, str, str, str, int]]:
    directory = site / "typescript"
    output = subprocess.run(
        ["node", str(ROOT / "tools" / "parity_surface.cjs"),
         str(directory / "node_modules" / "typescript"), str(directory / "generated")],
        capture_output=True, text=True, check=True).stdout
    rows = []
    for line in output.splitlines():
        module, name, member, kind, doc = line.split("\t")
        # `definitions()` has a module of its own in TypeScript, and is the entry point's in Python.
        module = "index" if module == "definitions" else module
        rows.append((module, name, member, kind, int(doc)))
    return rows


def read_python(site: Path) -> list[tuple[str, str, str, str, int]]:
    generated = site / "python" / "generated"
    package = next(p.parent.name for p in generated.glob("*/__init__.py"))
    output = subprocess.run([sys.executable, __file__, "--python-surface", package],
                            cwd=generated, env={**os.environ, "PYTHONPATH": str(generated)},
                            capture_output=True, text=True, check=True).stdout
    return [tuple(json.loads(line)) for line in output.splitlines()]


def is_pool(module: str) -> bool:
    """A pool's module, `<pool>/pool` in both packages."""
    return module.endswith("/pool")


def by_idiom(row: tuple[str, str, str, str, int], python: bool) -> bool:
    """Whether a member one language alone has is an idiom of DESIGN.md §7."""
    module, name, member, kind, _ = row
    last = norm(member.split(".")[-1]) if member else ""
    if python:
        # The abstract Key inherits the classmethod from the proxy base, and refuses every call.
        if module == "index" and name == "Key" and last == "wrapvalue":
            return True
        if last in PYTHON_ONLY or last in {p for p, _ in PAIRS}:
            return True
        # The local function pool: TypeScript has the remote side only (DESIGN.md §9).
        return is_pool(module) and name == "Pool"
    if last in TYPESCRIPT_ONLY or last in {t for _, t in PAIRS}:
        return True
    if not member and kind == "type":
        return True                                         # `…Init`: Python names fields by keyword
    # A pool's name and uuid: on its module in TypeScript, on its Pool in Python.
    return is_pool(module) and not member and name in ("NAME", "UUID")


def compare(site: str) -> list[str]:
    directory = ROOT / site
    key = lambda row: (row[0], norm(row[1]), norm(row[2]))
    python = {key(r): r for r in read_python(directory)}
    typescript = {key(r): r for r in typescript_surface(directory)}

    drift = []
    for k, row in sorted(python.items()):
        if k not in typescript and not by_idiom(row, python=True):
            drift.append(f"python only: {row[0]}:{row[1]}{'.' + row[2] if row[2] else ''}")
    for k, row in sorted(typescript.items()):
        if k not in python and not by_idiom(row, python=False):
            drift.append(f"typescript only: {row[0]}:{row[1]}{'.' + row[2] if row[2] else ''}")
    for k in sorted(python.keys() & typescript.keys()):
        p, t = python[k], typescript[k]
        if p[4] != t[4]:
            side = "python" if p[4] else "typescript"
            drift.append(f"documented in {side} only: {p[0]}:{p[1]}{'.' + p[2] if p[2] else ''}")
    common = len(python.keys() & typescript.keys())
    return drift if drift else [f"ok   {site}: {common} members alike, the rest by idiom"]


def summarise(drift: list[str]) -> list[str]:
    """Drift grouped by what it is, so that one missing method on every class reads as one line."""
    groups: Counter[tuple[str, str]] = Counter()
    example: dict[tuple[str, str], str] = {}
    for line in drift:
        what, where = line.split(": ", 1)
        member = where.rsplit(".", 1)[-1] if "." in where else where.split(":")[1]
        groups[(what, member)] += 1
        example.setdefault((what, member), where)
    return [f"{what}: {member} ({count}x, e.g. {example[(what, member)]})"
            for (what, member), count in groups.most_common()]


def main() -> int:
    if sys.argv[1:2] == ["--python-surface"]:
        for row in python_surface(sys.argv[2]):
            print(json.dumps(row))
        return 0

    sites = sys.argv[1:] or SITES
    failed = False
    for site in sites:
        lines = compare(site)
        if lines[0].startswith("ok"):
            print(lines[0])
            continue
        failed = True
        print(f"FAIL {site}: {len(lines)} differences no idiom explains")
        for line in summarise(lines)[:12]:
            print(f"     {line}")
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
