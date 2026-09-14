#!/usr/bin/env python3
"""Render every model with every target into a scratch tree, and compare two trees.

The working tree is never touched: this reads the `.dsm.json` each model produces and
invokes the jar directly, so it can be run before and after a change without a commit
in between.

    render.py <dir>                 render every model into <dir>
    render.py --diff <before> <after>

A mono-namespace model guards against regression: its diff must be empty. A
multi-namespace model shows the effect a change is meant to have, so its diff is read,
not asserted. `--diff` reports the two separately for that reason.
"""
import os, re, subprocess, sys, difflib
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from models import MODELS

ROOT = Path(__file__).resolve().parent.parent
KIBO = ROOT.parent / "kibo"
TEMPLATES = Path(os.environ.get("KIBO_TEMPLATES") or ROOT.parent / "kibo-template-viper")
BANNER = re.compile(r"by kibo-[0-9.]+\.jar")


def jar():
    if os.environ.get("KIBO_JAR"):
        return os.environ["KIBO_JAR"]
    found = []
    for p in (KIBO / "target").glob("kibo-*.jar"):
        m = re.match(r"^kibo-(\d+)\.(\d+)\.(\d+)\.jar$", p.name)
        if m:
            found.append((tuple(int(g) for g in m.groups()), p))
    if not found:
        sys.exit(f"No kibo jar under {KIBO}/target. Build it, or set KIBO_JAR.")
    return str(max(found)[1])


def definitions(model):
    """Produce the model's .dsm.json beside its sources, and return the path."""
    from dsviper import DSMBuilder
    spec = MODELS[model]
    report, dsm, _ = DSMBuilder.assemble(str(ROOT / spec["definitions"])).parse()
    if report.has_error():
        for e in report.errors():
            print(f"  {model}: {e!r}")
        sys.exit(f"{model}: the model does not parse")
    out = ROOT / model / f'{spec["namespace"]}.dsm.json'
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(dsm.json_encode())
    return out


def kibo(jar_path, target, namespace, dsm, template, out):
    out.mkdir(parents=True, exist_ok=True)
    r = subprocess.run(["java", "-jar", jar_path, "-c", target, "-n", namespace,
                        "-d", str(dsm), "-t", str(template), "-o", str(out)],
                       capture_output=True, text=True)
    noise = [l for l in r.stderr.splitlines() if l.strip()]
    if r.returncode or noise:
        print(f"  !! {target} {Path(template).name}")
        for l in noise[:6]:
            print(f"     {l}")


def render(outdir):
    j = jar()
    print(f"jar: {Path(j).name}\n")
    for model, spec in MODELS.items():
        dsm = definitions(model)
        base = outdir / model
        for feature in spec["cpp"]:
            kibo(j, "cpp", spec["namespace"], dsm, TEMPLATES / "cpp" / feature, base / "cpp")
        kibo(j, "python", spec["package"], dsm, TEMPLATES / "python/package", base / "python")
        kibo(j, "typescript", spec["package"], dsm, TEMPLATES / "typescript", base / "typescript")
        files = sorted(p for p in base.rglob("*") if p.is_file())
        lines = sum(len(p.read_text(errors="replace").splitlines()) for p in files)
        print(f"  {model:12} {spec['shape']:6} {len(files):4} files, {lines:7} lines")


def tree(d):
    return {str(p.relative_to(d)): BANNER.sub("by kibo", p.read_text(errors="replace"))
            for p in d.rglob("*") if p.is_file()}


def diff(before, after):
    worst = 0
    for model, spec in MODELS.items():
        a, b = tree(before / model), tree(after / model)
        added, removed = sorted(set(b) - set(a)), sorted(set(a) - set(b))
        changed = sorted(f for f in set(a) & set(b) if a[f] != b[f])
        gate = "must be empty" if spec["shape"] == "mono" else "read it"
        if not (added or removed or changed):
            print(f"  {model:12} {spec['shape']:6} no change")
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
    if len(sys.argv) == 4 and sys.argv[1] == "--diff":
        sys.exit(diff(Path(sys.argv[2]), Path(sys.argv[3])))
    if len(sys.argv) == 2:
        render(Path(sys.argv[1]))
    else:
        sys.exit(__doc__)
