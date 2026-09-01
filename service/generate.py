#!/usr/bin/env python3
import subprocess
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
SIBLING_TEMPLATES = SIBLING_ROOT / "kibo-template-viper"

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
    return str(max(matches)[1])

JAR = _resolve_jar()
TEMPLATES = os.environ.get("KIBO_TEMPLATES") or str(SIBLING_TEMPLATES)
KIBO = ['java', '-jar', JAR]

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
    blob = definitions.encode()
    with open(f'{output}', 'w') as file:
        file.write(blob.embed("definitions"))

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
    # Reuse the `python` converter (engine-agnostic) on the typescript templates;
    # no kibo engine change is required.
    output = f'{package_root}/src'
    subprocess.run(KIBO + [
        '-c', 'python', '-n', name, '-d', dsm_path,
        '-t', f'{TEMPLATES}/typescript', '-o', output,
    ])
    subprocess.run(KIBO + [
        '-c', 'python', '-n', name, '-d', dsm_path,
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
    print('** Render C++')
    render_templates(namespace=NAMESPACE, dsm_path=DSM_PATH, output=f'{NAMESPACE}')
    generate_resource(definitions=DEFINITIONS, output=f'{NAMESPACE}/{NAMESPACE}_Resources.hpp')

if arguments.python:
    print('** Render Python Package')
    generate_package(name='service', dsm_path=DSM_PATH, definitions=DEFINITIONS, output=f'python/service')

if arguments.typescript:
    print('** Render TypeScript Package')
    generate_typescript(name='service', dsm_path=DSM_PATH, definitions=DEFINITIONS, package_root=f'typescript/service')