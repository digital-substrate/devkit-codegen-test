# devkit-codegen-test

Codegen pipeline integration tests for the dsviper DevKit.

Two projects exercise the DSM → Kibo → templates → runtime pipeline:

- `features/` — value-system features: data, stream, json, database, attachments, codecs, hashers, fuzz.
- `service/` — RPC / function-pool features: function pools, attachments pools, remote variants, bridges.

These projects are not built or run by the `dsviper` runtime CI. They serve as a manual
sanity check of the codegen pipeline and as a reference of how a downstream application
wires DSM definitions, Kibo, templates, and the runtime together.

## Layout assumption

This repo expects three sibling checkouts under a common parent directory:

```
<common parent>/
├── com.digitalsubstrate.viper/         # runtime + third_parties (C++)
├── kibo/                               # Kibo jar (built via `mvn package`)
├── kibo-template-viper/                # Kibo templates (cpp/, python/)
└── devkit-codegen-test/                # this repo
```

The siblings live in their own repositories:

- [digital-substrate/viper](https://github.com/digital-substrate/viper) — Viper runtime.
- [digital-substrate/kibo](https://github.com/digital-substrate/kibo) — code generator.
- [digital-substrate/kibo-template-viper](https://github.com/digital-substrate/kibo-template-viper) — first-party Kibo templates for the Viper ecosystem.

`generate.py` resolves Kibo and templates via:

1. `KIBO_JAR` and `KIBO_TEMPLATES` environment variables, if set.
2. Otherwise, `../kibo/target/kibo-*.jar` and `../kibo-template-viper/`.

`CMakeLists.txt` (via `lib.cmake`) locates the sibling
`com.digitalsubstrate.viper/` checkout to build the third_parties (sqlite,
json, hash, antlr4, cli11) and the `viper` static target.

## Usage

```bash
# 1. Generate C++ and Python code from the DSM definitions.
cd features
python3 generate.py all.dsm -c -p
cd ../service
python3 generate.py -c -p

# 2. Build the C++ executables (links viper from the sibling checkout).
cd ..
mkdir build && cd build
cmake ..
cmake --build . -j

# 3. Run the Python tests against the generated `features` package.
cd ../features/python
./run_test.sh
```

`CMakeLists.txt` skips `features/` or `service/` cleanly when their generated
content is missing, so a fresh clone configures without errors.

## License

MIT — see [LICENSE](LICENSE).
