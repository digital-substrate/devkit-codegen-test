#!/usr/bin/env python3
"""Rendre les quatre modèles en TypeScript, les compiler et les importer.

DEUX ÉPREUVES ET NON UNE. `tsc --strict` dit que les annotations tiennent ; l'import dit que
les modules se résolvent, que les classes se construisent et que les descripteurs se trouvent
dans les définitions embarquées. Le C++ a un compilateur et un lien ; ici ce sont les deux.

    render.py            rend, écrit dans generated/node/, compile, importe
    render.py --check    échoue si generated/node/ n'est pas à jour
"""
import argparse
import importlib.util
import json
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent.parent
ROOT = HERE.parents[1]


def _module(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


jar = _module(ROOT / "tools" / "render.py", "kibo_tools_render").jar
MODELS = _module(ROOT / "tools" / "models.py", "kibo_tools_models").MODELS

resolve = _module(ROOT / "templates" / "resolve.py", "kibo_templates_resolve")
# Même principe qu'en Python : la feature choisit, le dossier ne choisit rien.
TEMPLATES = resolve.templates("typescript", ["Base", "Pool"])
RESOURCES = HERE / "cpp" / "link" / "resources"

# CE QUE LA LIAISON DEVRAIT PORTER ET NE PORTE PAS. Aucun de ces modules ne nomme un type d'un
# modèle et aucun ne varie d'un modèle à l'autre : leur place est dans `@digitalsubstrate/dsviper`.
# En attendant ils sont déposés sous `_codegen`, et le code rendu écrit `from "../_codegen/…"`.
PROPOSED = HERE / "runtime-proposed" / "node"

# LA BOÎTE À OUTILS EST CELLE D'UN PROJET EXISTANT : `tsc` et la liaison y sont déjà.
TOOLING = ROOT / "features" / "typescript" / "node_modules"
BINDING = ROOT.parent / "com.digitalsubstrate.viper" / "dsviper_node"
NODE_TYPES = BINDING / "node_modules" / "@types"

arguments = argparse.ArgumentParser(description=__doc__,
    formatter_class=argparse.RawDescriptionHelpFormatter)
arguments.add_argument("--check", action="store_true",
                       help="échouer si generated/node/ n'est pas à jour")
arguments = arguments.parse_args()

# ET LA SUITE QUE LE PROJET A ÉCRITE, PORTÉE SUR LE RENDU. 15 fichiers, 4 000 lignes, contre
# le paquet de l'ancien pack. `node/link/migrate.py` ne contient que des renommages.
def suite(target):
    source = ROOT / "features" / "typescript" / "test"
    package = target / "features"
    if not source.exists() or not package.exists():
        return 0

    sys.path.insert(0, str(HERE / "node" / "link"))
    import migrate
    scratch = HERE / "build" / "node-suite"
    shutil.rmtree(scratch, ignore_errors=True)
    scratch.mkdir(parents=True, exist_ok=True)
    substitutions = sum(migrate.migrate(scratch / "test", package).values())
    (scratch / "features").symlink_to(package)
    (scratch / "node_modules").symlink_to(package / "node_modules")
    sys.path.pop(0)

    r = subprocess.run(["node", "--test", *[str(p) for p in sorted((scratch / "test").glob("*.mjs"))]],
                       cwd=scratch, capture_output=True, text=True)
    passed = sum(1 for l in r.stdout.splitlines() if l.startswith("\u2714"))
    failed = sum(1 for l in r.stdout.splitlines() if l.startswith("\u2716"))
    print(f"  {'la suite':11} {passed:3} / {passed + failed} tests du projet, "
          f"{substitutions} substitutions de portage")
    return 0



target = HERE / (".check-node" if arguments.check else "generated/node")
if target.exists():
    shutil.rmtree(target)

TSCONFIG = {
    "compilerOptions": {
        "target": "ES2022", "module": "NodeNext", "moduleResolution": "NodeNext",
        "declaration": True, "strict": True, "esModuleInterop": True, "skipLibCheck": True,
        "outDir": "dist", "rootDir": "src",
        "typeRoots": [str(NODE_TYPES)], "types": ["node"],
    },
    "include": ["src/**/*.ts"],
}

status = 0
for model, spec in MODELS.items():
    namespace = spec["namespace"]
    definitions = ROOT / model / f"{namespace}.dsm.json"
    package = target / namespace.lower()
    source = package / "src"

    noise = []
    echec = False
    for stg in TEMPLATES:
        r = subprocess.run(["java", "-jar", jar(), "-c", "typescript", "-n", namespace,
                            "-d", str(definitions), "-t", str(stg), "-o", str(source)],
                           capture_output=True, text=True)
        noise += [l for l in r.stderr.splitlines() if l.strip()]
        echec = echec or bool(r.returncode)
    for line in noise[:8]:
        print(f"  !! {line}")
    if echec or noise:
        status = 1
        continue

    # Ce qui ne sort pas des templates : les octets du modèle, le paquet que la liaison
    # devrait porter, et le calage du projet.
    shutil.copy(RESOURCES / f"{namespace}_resources.ts", source / "resources.ts")
    shutil.copytree(PROPOSED, source / "_codegen",
                    ignore=shutil.ignore_patterns("*.md"))
    (package / "package.json").write_text(json.dumps(
        {"name": namespace.lower(), "private": True, "type": "module"}, indent=4) + "\n")
    (package / "tsconfig.json").write_text(json.dumps(TSCONFIG, indent=4) + "\n")
    link = package / "node_modules" / "@digitalsubstrate"
    link.mkdir(parents=True, exist_ok=True)
    (link / "dsviper").symlink_to(BINDING)

    modules = sorted(p.relative_to(source).with_suffix("") for p in source.rglob("*.ts"))
    tsc = TOOLING / ".bin" / "tsc"
    if not tsc.exists():
        print(f"  {namespace:11} {len(modules):3} modules, tsc absent")
        continue

    r = subprocess.run([str(tsc), "-p", "tsconfig.json"], cwd=package,
                       capture_output=True, text=True)
    errors = [l for l in (r.stdout + r.stderr).splitlines() if l.strip()]
    if errors:
        print(f"  {namespace:11} {len(modules):3} modules, {len(errors)} erreur(s) de typage")
        for line in errors[:5]:
            print(f"     {line}")
        status = 1
        continue

    names = [str(m).replace("\\", "/") for m in modules if not str(m).startswith("_codegen")]
    script = ";".join(f'await import("./dist/{n}.js")' for n in names)
    r = subprocess.run(["node", "--input-type=module", "-e", script],
                       cwd=package, capture_output=True, text=True)
    ok = "compile et tout s'importe" if r.returncode == 0 else "L'IMPORT ÉCHOUE"
    print(f"  {namespace:11} {len(modules):3} modules, {ok}")
    if r.returncode:
        status = 1
        for line in r.stderr.strip().splitlines()[-3:]:
            print(f"     {line}")
        continue

    if model == "features":
        suite(target)

    # ET L'ÉPREUVE QUE CE MODÈLE-LÀ PERMET. `Crossing` porte toutes les formes de conteneurs
    # traversant deux unités ; aucune unité de la référence n'en a, et lui en ajouter
    # reviendrait à écrire à la main ce que les templates produisent déjà.
    for assertions in sorted((HERE / "node" / "checks").glob(f"{model}*.mjs")):
        shutil.copy(assertions, package)
        r = subprocess.run(["node", assertions.name], cwd=package, capture_output=True, text=True)
        (package / assertions.name).unlink()
        passed = sum(1 for line in r.stdout.splitlines() if line.strip().startswith("ok"))
        label = assertions.stem.split("-")[-1] if "-" in assertions.stem else namespace
        print(f"  {'épreuve':11} {passed:3} assertions, {label}, "
              + ("toutes passent" if r.returncode == 0 else "ÉCHEC"))
        if r.returncode:
            status = 1
            for line in (r.stdout + r.stderr).splitlines():
                if "ÉCHEC" in line or "Error" in line:
                    print(f"     {line.strip()}")

if arguments.check:
    same = subprocess.run(["diff", "-r", "-x", "dist", "-x", "node_modules",
                           str(HERE / "generated/node"), str(target)],
                          capture_output=True, text=True)
    print(same.stdout.strip() or "generated/node/ est à jour")
    shutil.rmtree(target)
    status |= 1 if same.returncode else 0

raise SystemExit(status)
