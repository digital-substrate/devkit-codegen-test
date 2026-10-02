# devkit-codegen-test

Codegen pipeline integration tests for the dsviper DevKit.

One gate for all of it:

    ./check.py              render the five sites and run every suite
    ./check.py features     just one
    ./check.py --no-render  test what is already rendered


Two projects exercise the DSM → Kibo → templates → runtime pipeline:

- `features/` — value-system features: data, stream, json, database, attachments, codecs, hashers, fuzz.
- `service/` — RPC / function-pool features: function pools, attachments pools, remote variants, bridges.

And one site guards the other direction of time:

- `compat-1.2/` — a database written by the 1.2 runtime, committed, read back by what is generated today.

And one check guards the wire across lines: `tools/crossversion.py` builds the 1.2 line's
`service` (this repository's and the template pack's `LTS-1.2` branches, a kibo 1.2 jar, the
sibling viper) and calls it with the kibo 2 Python and TypeScript clients. A pool function travels
under its DSM name in both lines; a change that breaks that fails here. `check.py` runs it last,
and skips it, saying why, when the 1.2 line is not at hand.

Each is generated for three targets — C++, Python and TypeScript — so a change to the
templates can be checked against all of them.

These projects are not built or run by the `dsviper` runtime CI. They serve as a manual
sanity check of the codegen pipeline and as a reference of how a downstream application
wires DSM definitions, Kibo, templates, and the runtime together.

## Layout assumption

This repo expects three sibling checkouts under a common parent directory:

```
<common parent>/
├── com.digitalsubstrate.viper/         # runtime + third_parties (C++ ; private)
├── kibo/                               # Kibo jar (built via `mvn package`)
├── kibo-template-viper/                # Kibo templates (cpp/, python/)
└── devkit-codegen-test/                # this repo
```

The siblings live in their own repositories:

- **viper** — the Viper C++ runtime. Sources are not publicly distributed
  (Digital Substrate Commercial License 1.2); the public artefact is the
  [`dsviper` wheel on PyPI](https://pypi.org/project/dsviper/). The full
  C++ build below therefore requires access to the runtime sources
  (Digital Substrate organisation members or licensed evaluation). The
  Python-only flow (`features/python`) is exercisable against an
  installed `dsviper` wheel without source access.
- [digital-substrate/kibo](https://github.com/digital-substrate/kibo) — code generator.
- [digital-substrate/kibo-template-viper](https://github.com/digital-substrate/kibo-template-viper) — first-party Kibo templates for the Viper ecosystem.

Each site declares its generation in a `kibo.toml`, rendered by the sibling
[kibo-project](https://github.com/digital-substrate/kibo-project) checkout (`KIBO_PROJECT`
overrides its location for `check.py`). It resolves Kibo and templates via:

1. `KIBO_JAR` and `KIBO_TEMPLATES` environment variables, if set.
2. Otherwise, `../kibo/target/kibo-*.jar` and `../kibo-template-viper/`.

`CMakeLists.txt` (via `lib.cmake`) locates the
`com.digitalsubstrate.viper/` checkout to build the third_parties (sqlite,
json, hash, antlr4, cli11) and the `viper` static target. It resolves it via:

1. `-DREPO_VIPER=<path>` or the `REPO_VIPER` environment variable, if set.
2. Otherwise, the sibling `../com.digitalsubstrate.viper/`.

## Usage

```bash
# 1. Generate C++, Python and TypeScript code from the DSM definitions, as each site's
#    kibo.toml declares; --target cpp|python|typescript picks one.
cd features
python3 ../../kibo-project/kibo_project.py generate
cd ../service
python3 ../../kibo-project/kibo_project.py generate

# 2. Build the C++ executables (links viper from the sibling checkout).
cd ..
mkdir build && cd build
cmake ..
cmake --build . -j

# 3. Run the Python tests against the generated `features` package.
cd ../features/python
./run_test.sh

# 4. Build and run a TypeScript client (needs the dsviper npm package).
cd ../../service/typescript
npm install
npm run build
npm run client        # against a running service_server
```

`CMakeLists.txt` skips `features/` or `service/` cleanly when their generated
content is missing, so a fresh clone configures without errors.

## License

MIT — see [LICENSE](LICENSE).
