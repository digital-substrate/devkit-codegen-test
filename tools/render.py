#!/usr/bin/env python3
"""Render every site into a scratch tree, and compare two trees.

The working tree is never touched: each site's `kibo.toml` is rendered through kibo-project
into `<dir>/<site>`, so this can be run before and after a change without a commit in
between.

    render.py <dir>                 render every site into <dir>
    render.py --diff <before> <after> [--renames <map> | --only <artefact>]

A mono-namespace model guards against regression: its diff must be empty. A
multi-namespace model shows the effect a change is meant to have, so its diff is read,
not asserted. `--diff` reports the two separately for that reason.
"""
import os, re, subprocess, sys, difflib
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from models import SITES

ROOT = Path(__file__).resolve().parent.parent
# kibo-project, from the sibling checkout unless KIBO_PROJECT names the script.
KIBO_PROJECT = Path(os.environ.get("KIBO_PROJECT") or ROOT.parent / "kibo-project" / "kibo_project.py")
# What changes with every generator release, and says nothing about the output.
BANNER = re.compile(r"by kibo-[0-9.]+\.jar|by kibo-project [0-9.]+")


def generate(project, into, *options):
    """Render a project file into a directory through kibo-project. Returns the error output."""
    r = subprocess.run([sys.executable, str(KIBO_PROJECT), "generate", str(project),
                        "--into", str(into), *options], capture_output=True, text=True)
    return r.stderr.strip() if r.returncode else ""


def outputs(d):
    """The generated files under d: the .dsm.json beside them is kibo's input, not its output."""
    return [p for p in d.rglob("*") if p.is_file() and not p.name.endswith(".dsm.json")]


def render(outdir):
    for site, spec in SITES.items():
        base = outdir / site
        error = generate(ROOT / site / "kibo.toml", base)
        if error:
            print(f"  !! {site}")
            for l in error.splitlines()[:6]:
                print(f"     {l}")
            continue
        files = sorted(outputs(base))
        lines = sum(len(p.read_text(errors="replace").splitlines()) for p in files)
        print(f"  {site:12} {spec['shape']:6} {len(files):4} files, {lines:7} lines")


def tree(d):
    return {str(p.relative_to(d)): BANNER.sub("by kibo", p.read_text(errors="replace"))
            for p in outputs(d)}


def renames(path):
    """Read a rename map: one `model: old -> new` per line, # for a comment.

    A step that moves output declares what it moved, and the diff is then taken after
    applying the map: anything the map does not explain is a real change wearing a
    rename's clothes. Without this the instrument says `everything moved` and stops
    being able to distinguish, which is exactly when it is needed most.

    Entries are per model because a rename is: the same artefact is
    Features_ValueHexdigest.hpp in one model and Service_ValueHexdigest.hpp in another.

    A map cannot express a split -- one file becoming several, each holding a part of
    the old content. That is what a multi-namespace model does under this work, which
    is why its gate is to be read rather than asserted.
    """
    out = {}
    for line in Path(path).read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        model, _, rest = line.partition(":")
        old, _, new = rest.partition("->")
        out.setdefault(model.strip(), {})[old.strip()] = new.strip()
    return out


def diff(before, after, rename=None, scope=None):
    worst = 0
    mapping = renames(rename) if rename else {}
    for model, spec in SITES.items():
        a, b = tree(before / model), tree(after / model)
        renamed = mapping.get(model, {})
        if renamed:
            unknown = [k for k in renamed if k not in a]
            if unknown:
                worst = 1
                print(f"  {model:12} {spec['shape']:6} {len(unknown)} rename(s) name a file that was not there")
                for k in unknown[:3]:
                    print(f"      ? {k}")
            a = {renamed.get(k, k): v for k, v in a.items()}
        added, removed = sorted(set(b) - set(a)), sorted(set(a) - set(b))
        changed = sorted(f for f in set(a) & set(b) if a[f] != b[f])
        # A migration moves one artefact. Everything outside it must be still, whatever
        # the model's shape -- a step that spills is a step that was not understood.
        expected = [f for f in added + removed + changed if scope and scope in f]
        added   = [f for f in added   if f not in expected]
        removed = [f for f in removed if f not in expected]
        changed = [f for f in changed if f not in expected]
        if expected:
            print(f"  {model:12} {spec['shape']:6} {len(expected)} in '{scope}', as declared")

        gate = "must be empty" if spec["shape"] == "mono" else "read it"
        if not (added or removed or changed):
            print(f"  {model:12} {spec['shape']:6} nothing else moved")
            continue
        worst = max(worst, 1 if spec["shape"] == "mono" else 0)
        print(f"  {model:12} {spec['shape']:6} +{len(added)} -{len(removed)} ~{len(changed)}   ({gate})")
        for f in added[:5]:   print(f"      + {f}")
        for f in removed[:5]: print(f"      - {f}")
        for f in changed[:5]:
            d = list(difflib.unified_diff(a[f].splitlines(), b[f].splitlines(), lineterm="", n=0))
            print(f"      ~ {f}  ({sum(1 for l in d[2:] if l[:1] in '+-')} lines)")
    return worst


if __name__ == "__main__":
    if len(sys.argv) in (4, 6) and sys.argv[1] == "--diff":
        rename = sys.argv[5] if len(sys.argv) == 6 and sys.argv[4] == "--renames" else None
        scope  = sys.argv[5] if len(sys.argv) == 6 and sys.argv[4] == "--only" else None
        sys.exit(diff(Path(sys.argv[2]), Path(sys.argv[3]), rename, scope))
    if len(sys.argv) == 2:
        render(Path(sys.argv[1]))
    else:
        sys.exit(__doc__)
