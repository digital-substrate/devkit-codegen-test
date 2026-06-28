#!/usr/bin/env python3
import subprocess
import argparse
import os
import zlib
import base64
from pathlib import Path

from dsviper import DSMDefinitions, DefinitionsConst, DSMBuilder

parser = argparse.ArgumentParser()
parser.add_argument("definitions", help="Definitions to use")
parser.add_argument("-c", "--cpp", help="Generate C++", action="store_true")
parser.add_argument("-p", "--package", help="Generate the Python package", action="store_true")
parser.add_argument("-ts", "--typescript", help="Generate the TypeScript package", action="store_true")
arguments = parser.parse_args()

SIBLING_ROOT = Path(__file__).resolve().parent.parent.parent
SIBLING_KIBO = SIBLING_ROOT / "kibo"
SIBLING_TEMPLATES = SIBLING_ROOT / "kibo-template-viper"

def _resolve_jar():
    env = os.environ.get("KIBO_JAR")
    if env:
        return env
    matches = sorted(SIBLING_KIBO.glob("target/kibo-*.jar"))
    if not matches:
        raise SystemExit(f"No kibo jar at {SIBLING_KIBO}/target/. "
                         f"Run `mvn package` in {SIBLING_KIBO} or set KIBO_JAR.")
    return str(matches[-1])

JAR = _resolve_jar()
TEMPLATES = os.environ.get("KIBO_TEMPLATES") or str(SIBLING_TEMPLATES)
KIBO = ['java', '-jar', JAR]


def generate(namespace: str, dsm_path: str, template: str, output: str, *args):
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
    blob = definitions.encode()
    with open(f'{output}', 'w') as file:
        file.write(blob.embed("definitions"))


def render_templates(namespace: str, dsm_path: str, output: str):
    templates = [
        'Model',
        'Data',
        'Stream', 'Json',
        'Database',
        'Attachments', 'AttachmentFunctionPool_Attachments',
        'ValueType', 'ValueCodec', 'ValueHasher',
        'Test'
    ]

    for template in templates:
        generate(namespace=namespace, dsm_path=dsm_path, template=template, output=output)


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
    # The TypeScript output is pure templates: it reuses the `python` converter
    # (same Converter, same empty file-prefix policy) pointed at the typescript
    # template directory. No kibo engine change is required.
    output = f'{package_root}/src'

    # TypeScript sources -> package src/
    cmd = KIBO + [
        '-c', 'python',
        '-n', name,
        '-d', dsm_path,
        '-t', f'{TEMPLATES}/typescript',
        '-o', output,
    ]
    subprocess.run(cmd)

    # Package descriptor + tsconfig -> package root
    cmd = KIBO + [
        '-c', 'python',
        '-n', name,
        '-d', dsm_path,
        '-t', f'{TEMPLATES}/typescript/project',
        '-o', package_root,
    ]
    subprocess.run(cmd)

    # Embed the definitions blob with the default codec (StreamTokenBinary), the
    # same codec definitions.ts decodes with — kept symmetric with the Python
    # package. No zlib: definitions.ts base64-decodes the string straight into
    # Definitions.decode.
    blob = definitions.encode()
    string = base64.b64encode(blob).decode("ascii")
    with open(f'{output}/resources.ts', 'w') as file:
        file.write(f'export const B64_DEFINITIONS = "{string}";\n')


PROJECT = 'Features'
DSM_SOURCE = arguments.definitions
DSM_PATH = f'{PROJECT}.dsm.json'
NAMESPACE = f'{PROJECT}'
OUTPUT = f'{NAMESPACE}'

if not os.path.exists(JAR):
    print(f'{JAR} not found.')
    print('Read the documentation to build the jar.')
    exit(1)

print(f' definitions: {DSM_SOURCE}')
print(f'        kibo: {KIBO}')

BUILDER = DSMBuilder.assemble(DSM_SOURCE)
REPORT, DSM_DEFINITIONS, DEFINITIONS = BUILDER.parse()
check_report(report=REPORT)
save_dsm_definitions(dsm_definitions=DSM_DEFINITIONS, dsm_path=DSM_PATH)

if not (arguments.cpp | arguments.package | arguments.typescript):
    parser.print_help()
    exit(0)

if arguments.cpp:
    print('** Render Cpp')
    render_templates(namespace=NAMESPACE, dsm_path=DSM_PATH, output=PROJECT)
    generate_resource(definitions=DEFINITIONS, output=f'{NAMESPACE}/{NAMESPACE}_Resources.hpp')
    generate(namespace=NAMESPACE, dsm_path=DSM_PATH, template='TestApp', output=".")

if arguments.package:
    print('** Render Python Package')
    generate_package(name='features', dsm_path=DSM_PATH, definitions=DEFINITIONS, output=f'python/features')

if arguments.typescript:
    print('** Render TypeScript Package')
    generate_typescript(name='features', dsm_path=DSM_PATH, definitions=DEFINITIONS, package_root=f'typescript/features')
