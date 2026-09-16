#!/usr/bin/env python3
import subprocess
import sys
import shutil
import json
import argparse
import os
import re
import zlib
import base64
from pathlib import Path

from dsviper import DSMDefinitions, DefinitionsConst, DSMBuilder

parser = argparse.ArgumentParser()
parser.add_argument("-c", "--cpp", help="Generate C++", action="store_true")
parser.add_argument("-p", "--python", help="Generate Python package", action="store_true")
parser.add_argument("-t", "--typescript", help="Generate the TypeScript package", action="store_true")
arguments = parser.parse_args()

SIBLING_ROOT = Path(__file__).resolve().parent.parent.parent
SIBLING_KIBO = SIBLING_ROOT / "kibo"
SIBLING_TEMPLATES = Path(__file__).resolve().parent.parent / "templates"

# The kibo-template-viper line this repository generates against. A sibling
# checkout's branch decides which templates you get, and a pack from another line
# renders this model differently — a mismatched pair produces plausible output and
# says nothing. KIBO_TEMPLATES still overrides the location, not the check.
TEMPLATES_MAJOR = 2


def _check_templates(root):
    """Fail if the template pack on disk is not the line this repository targets."""
    stamp = re.compile(r"Templates: kibo-template-viper (\d+)\.(\d+)\.(\d+)")
    for stg in sorted(Path(root).rglob("*.stg")):
        found = stamp.search(stg.read_text())
        if not found:
            continue
        version = ".".join(found.groups())
        if int(found.group(1)) != TEMPLATES_MAJOR:
            raise SystemExit(f"Templates at {root} are {version}; this repository "
                             f"generates against kibo-template-viper {TEMPLATES_MAJOR}.x. "
                             f"Check out that line, or set KIBO_TEMPLATES.")
        return version
    raise SystemExit(f"No versioned template under {root} — is that a "
                     f"kibo-template-viper checkout?")

# The kibo line this repository generates against. The newest jar in a sibling
# checkout is not the right answer: a generator from another line renders the same
# model into different output, and nothing here would say so. Declare the line.
# KIBO_JAR still overrides it, for a deliberate experiment.
KIBO_MAJOR = 2

def _resolve_jar():
    env = os.environ.get("KIBO_JAR")
    if env:
        return env
    # Ordered on the parsed (major, minor, patch) tuple: an alphabetical sort
    # puts kibo-1.2.9.jar after kibo-1.2.11.jar and would pick the older jar
    # whenever target/ holds more than one build.
    matches = []
    for jar in SIBLING_KIBO.glob("target/kibo-*.jar"):
        m = re.match(r"^kibo-(\d+)\.(\d+)\.(\d+)\.jar$", jar.name)
        if m:
            matches.append((tuple(int(g) for g in m.groups()), jar))
    if not matches:
        raise SystemExit(f"No kibo jar at {SIBLING_KIBO}/target/. "
                         f"Run `mvn package` in {SIBLING_KIBO} or set KIBO_JAR.")

    line = [m for m in matches if m[0][0] == KIBO_MAJOR]
    if not line:
        found = ", ".join(".".join(map(str, v)) for v, _ in sorted(matches))
        raise SystemExit(f"No kibo {KIBO_MAJOR}.x jar at {SIBLING_KIBO}/target/ "
                         f"(found {found}). This repository generates against kibo "
                         f"{KIBO_MAJOR}.x; a generator from another line renders this "
                         f"model differently. Build kibo {KIBO_MAJOR}.x, or set KIBO_JAR "
                         f"to choose deliberately.")
    return str(max(line)[1])

JAR = _resolve_jar()
TEMPLATES = os.environ.get("KIBO_TEMPLATES") or str(SIBLING_TEMPLATES)
_check_templates(TEMPLATES)
KIBO = ['java', '-jar', JAR]

# LA SÉLECTION EST UNE FEATURE. `templates/features.json` dit quels `.stg` chacune demande et
# ce qu'elle entraîne ; `resolve` calcule la clôture. Ce site les prend toutes -- il est là
# pour éprouver la surface entière -- mais un vrai projet en nomme deux ou trois.
sys.path.insert(0, TEMPLATES)
import resolve                                                          # noqa: E402

RUNTIME = Path(__file__).resolve().parent.parent / "runtime-proposed"
# Les typages Node vivent dans le node_modules du site : le paquet généré est compilé
# là où ses dépendances sont installées, pas ailleurs.
NODE_TYPES = Path(__file__).resolve().parent / "typescript" / "node_modules" / "@types"

TSCONFIG = {
    "compilerOptions": {
        "target": "ES2022", "module": "NodeNext", "moduleResolution": "NodeNext",
        "declaration": True, "strict": True, "esModuleInterop": True, "skipLibCheck": True,
        "outDir": "dist", "rootDir": "src",
        "typeRoots": [str(NODE_TYPES)], "types": ["node"],
    },
    "include": ["src/**/*.ts"],
}

CPP_OUT = 'cpp/generated'
PY_PROJECT = Path('python/generated')          # ce que `pip install` reçoit
PY_PACKAGE = PY_PROJECT / 'service'           # ce que `import` trouve
TS_PACKAGE = Path('typescript/generated')


def render(target: str, namespace: str, dsm_path: str, stgs, output):
    """Render each resolved template in turn; `kibo -t` takes one .stg as well as a dir."""
    Path(output).mkdir(parents=True, exist_ok=True)
    for stg in stgs:
        subprocess.run(KIBO + ['-c', target, '-n', namespace,
                               '-d', dsm_path, '-t', str(stg), '-o', str(output)])

def generate(namespace: str, dsm_path: str, template:str, output:str, *args):
    options = [
        '-c', 'cpp', 
        '-n', namespace, 
        '-d', dsm_path, 
        '-t', f'{TEMPLATES}/cpp/{template}',
        '-o', output
        ]

    cmd = KIBO + options + list(args)
    subprocess.run(cmd)

def generate_resource(definitions: DefinitionsConst, output: str):
    """Le modèle, en octets, dans un namespace.

    LE .DSM EMBARQUÉ TEL QUEL. Le générateur ne produit aucun code d'enregistrement de types :
    le document est embarqué et décodé au chargement. C'est aussi la réponse à « qui tient la
    liste des concepts connus » -- cette donnée-là.

    Ce n'est pas un texte écrit à la main : ce sont les octets que la chaîne de production
    encode, enveloppés dans `<Namespace>::Resources` -- ce que les templates attendent.
    """
    octets = bytes(definitions.encode().encoded())
    lignes = [", ".join(f"0x{b:02x}" for b in octets[i:i + 12]) for i in range(0, len(octets), 12)]
    corps = ",\n ".join(lignes)
    Path(output).parent.mkdir(parents=True, exist_ok=True)
    Path(output).write_text(
        f"#ifndef {NAMESPACE}_Resources_hpp\n"
        f"#define {NAMESPACE}_Resources_hpp\n\n"
        f"#include <cstddef>\n\n"
        f"namespace {NAMESPACE}::Resources {{\n\n"
        f"inline constexpr unsigned char definitions[] = {{\n {corps}\n}};\n\n"
        f"}} // namespace {NAMESPACE}::Resources\n\n"
        f"#endif\n")


def render_templates(namespace: str, dsm_path: str, output: str):
    templates =  [
        'Model', 
        'Data', 
        'Stream', 
        'ValueType', 'ValueCodec', 
        'FunctionPool', 'FunctionPoolRemote',
        'Attachments', 'AttachmentFunctionPool', 'AttachmentFunctionPoolRemote'
        ]

    for template in templates:
        generate(namespace=namespace, dsm_path=dsm_path, template=template , output=output)

def check_report(report):
    if report.has_error():
        for err in report.errors():
            print(repr(err))
        exit(0)

def save_dsm_definitions(dsm_definitions: DSMDefinitions, dsm_path: str):
    with open(dsm_path, "w") as file:
        file.write(dsm_definitions.json_encode())

def generate_package(name: str, dsm_path: str, definitions: DefinitionsConst, output: str):
    options = [
        '-c', 'python', 
        '-n', name, 
        '-d', dsm_path, 
        '-t', f'{TEMPLATES}/python/package',
        '-o', output
        ]

    cmd = KIBO + options
    subprocess.run(cmd)

    blob = definitions.encode()
    string = base64.b64encode(zlib.compress(blob))
    with open(f'{output}/resources.py', 'w') as file:
        file.write(f"B64_DEFINITIONS = {string}")

def generate_typescript(name: str, dsm_path: str, definitions: DefinitionsConst, package_root: str):
    # kibo 2.0 has a `typescript` target of its own; TypeScript no longer
    # borrows the `python` one.
    output = f'{package_root}/src'
    subprocess.run(KIBO + [
        '-c', 'typescript', '-n', name, '-d', dsm_path,
        '-t', f'{TEMPLATES}/typescript', '-o', output,
    ])
    subprocess.run(KIBO + [
        '-c', 'typescript', '-n', name, '-d', dsm_path,
        '-t', f'{TEMPLATES}/typescript/project', '-o', package_root,
    ])
    # Embed the definitions blob with the default codec (StreamTokenBinary), the
    # same codec definitions.ts decodes with — kept symmetric with the Python
    # package. No zlib: definitions.ts base64-decodes the string straight into
    # Definitions.decode.
    blob = definitions.encode()
    string = base64.b64encode(blob).decode("ascii")
    with open(f'{output}/resources.ts', 'w') as file:
        file.write(f'export const B64_DEFINITIONS = "{string}";\n')

PROJECT = 'Service'
DSM_SOURCE = f'definitions/Service'
DSM_PATH = f'{PROJECT}.dsm.json'
NAMESPACE = f'{PROJECT}'

if not os.path.exists(JAR):
    print(f'{JAR} not found.')
    print('Read the documentation of kibo to build the jar.')
    exit(1)

print(f'using kibo: {KIBO}')
BUILDER = DSMBuilder.assemble(DSM_SOURCE)
REPORT, DSM_DEFINITIONS, DEFINITIONS = BUILDER.parse()
check_report(report=REPORT)
save_dsm_definitions(dsm_definitions=DSM_DEFINITIONS, dsm_path=DSM_PATH)

if not (arguments.cpp | arguments.python | arguments.typescript):
    parser.print_help()
    exit(0)

if arguments.cpp:
    print('** Render Cpp')
    render('cpp', NAMESPACE, DSM_PATH,
           resolve.templates('cpp', ['Pool', 'AttachmentPool', 'Test']), CPP_OUT)
    generate_resource(definitions=DEFINITIONS, output=f'{CPP_OUT}/{NAMESPACE}_Resources.hpp')

if arguments.python:
    print('** Render Python Package')
    base = resolve.templates('python', ['Base', 'Pool'])
    render('python', NAMESPACE, DSM_PATH, base, PY_PACKAGE)
    # La roue n'atterrit pas au même endroit : py.typed dans le paquet, pyproject.toml un
    # cran au-dessus. Sans py.typed, toutes les annotations sont invisibles au consommateur.
    for stg in resolve.templates('python', ['Wheel']):
        if stg in base:
            continue
        render('python', NAMESPACE, DSM_PATH, [stg],
               PY_PACKAGE if stg.name.startswith('py.typed') else PY_PROJECT)
    # Ce qui ne sort pas des templates : les octets du modèle, et le runtime que la liaison
    # devrait porter et ne porte pas encore.
    blob = DEFINITIONS.encode()
    (PY_PACKAGE / 'resources.py').write_text(
        f"B64_DEFINITIONS = {base64.b64encode(zlib.compress(blob))}")
    shutil.rmtree(PY_PACKAGE / '_codegen', ignore_errors=True)
    shutil.copytree(RUNTIME / 'python', PY_PACKAGE / '_codegen',
                    ignore=shutil.ignore_patterns('__pycache__', '*.md'))

if arguments.typescript:
    print('** Render TypeScript Package')
    source = TS_PACKAGE / 'src'
    render('typescript', NAMESPACE, DSM_PATH,
           resolve.templates('typescript', ['Base', 'Pool']), source)
    blob = DEFINITIONS.encode()
    (source / 'resources.ts').write_text(
        f'export const B64_DEFINITIONS = "{base64.b64encode(blob).decode("ascii")}";\n')
    shutil.rmtree(source / '_codegen', ignore_errors=True)
    shutil.copytree(RUNTIME / 'node', source / '_codegen',
                    ignore=shutil.ignore_patterns('*.md'))
    # Le calage du projet. Il n'y a pas encore de template pour ça : `templates/typescript`
    # n'a pas de feature `Project`, contrairement au pack. Écrit ici en attendant, et c'est
    # une dette, pas un choix -- un paquet npm n'est pas au projet de l'inventer.
    (TS_PACKAGE / 'package.json').write_text(json.dumps(
        {"name": NAMESPACE.lower(), "private": True, "type": "module"}, indent=4) + "\n")
    (TS_PACKAGE / 'tsconfig.json').write_text(json.dumps(TSCONFIG, indent=4) + "\n")
