#!/usr/bin/env python3
"""A service built with the 1.2 line, called by the clients kibo 2 generates.

The runtime's dynamic space names a pool function as the DSM declares it, in the 1.2 line as in
kibo 2, so a 1.2 service and a kibo 2 client call each other. This builds the laboratory's 1.2
service -- its sources from this repository's LTS-1.2 branch, rendered by a 1.2 kibo and the
template pack's LTS-1.2 branch, linked against the sibling viper checkout -- and runs the kibo 2
Python and TypeScript clients of `service/` against it. A change of either line that breaks the
wire fails here.

It needs a kibo 1.2 jar (KIBO_LTS_JAR, else the newest `kibo-1.*.jar` of the line's own checkout,
`../kibo-LTS-1.2/target`, else of `../kibo/target`), an LTS-1.2 branch in this repository and in the sibling
kibo-template-viper, and the sibling com.digitalsubstrate.viper. When one is missing it says
which, and skips (exit 2).

The 1.2 sources and the build live under `build/lts/`; the build is kept between runs, so only
the first one compiles the runtime.
"""
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SIBLINGS = ROOT.parent
PACK = SIBLINGS / "kibo-template-viper"
VIPER = SIBLINGS / "com.digitalsubstrate.viper"
WORK = ROOT / "build" / "lts"
PORT = "54340"

# What each client prints when every call went through. A client skips a pool it does not
# find, so the exit code alone would not tell a missing function from a passing one.
EXPECTED = ["add(32,10) -> 42", "11", "22", "33", "key is", "read-only state: no player",
            "nickname=the shadow man"]


def skip(reason: str) -> int:
    print(f"skipped: {reason}")
    return 2


def jar() -> Path | None:
    if os.environ.get("KIBO_LTS_JAR"):
        return Path(os.environ["KIBO_LTS_JAR"])
    # The line's own checkout first: a jar left in ../kibo/target by an earlier build may carry
    # the same number and miss what the line has gained since.
    for folder in (SIBLINGS / "kibo-LTS-1.2" / "target", SIBLINGS / "kibo" / "target"):
        found = []
        for path in folder.glob("kibo-1.*.jar"):
            match = re.fullmatch(r"kibo-(\d+)\.(\d+)\.(\d+)\.jar", path.name)
            if match:
                found.append((tuple(int(g) for g in match.groups()), path))
        if found:
            return max(found)[1]
    return None


def has_branch(repository: Path, branch: str) -> bool:
    return subprocess.run(["git", "-C", str(repository), "rev-parse", "--verify", "--quiet", branch],
                          capture_output=True).returncode == 0


def export(repository: Path, branch: str, into: Path, *paths: str) -> None:
    """The branch's files, written over `into`: the build that follows reuses the same tree."""
    into.mkdir(parents=True, exist_ok=True)
    archive = subprocess.run(["git", "-C", str(repository), "archive", branch, *paths],
                             capture_output=True, check=True)
    subprocess.run(["tar", "-x", "-C", str(into)], input=archive.stdout, check=True)


def step(command: list[str], cwd: Path, env: dict[str, str] | None = None) -> None:
    result = subprocess.run(command, cwd=cwd, env=env, capture_output=True, text=True)
    if result.returncode:
        raise SystemExit(f"{' '.join(command[:3])} failed:\n{(result.stderr or result.stdout)[-2000:]}")


def build_server(kibo: Path) -> Path:
    export(ROOT, "LTS-1.2", WORK / "src", "service", "CMakeLists.txt", "lib.cmake")
    export(PACK, "LTS-1.2", WORK / "pack")
    env = {**os.environ, "KIBO_JAR": str(kibo), "KIBO_TEMPLATES": str(WORK / "pack")}
    step([sys.executable, "generate.py", "-c"], WORK / "src" / "service", env)
    step(["cmake", "-S", str(WORK / "src"), "-B", str(WORK / "build"), f"-DREPO_VIPER={VIPER}",
          "-DCMAKE_BUILD_TYPE=Release"], WORK)
    step(["cmake", "--build", str(WORK / "build"), "-j", "--target", "service_server"], WORK)
    return WORK / "build" / "service" / "service_server"


def clients() -> list[tuple[str, list[str], Path, dict[str, str], list[str]]]:
    service = ROOT / "service"
    typescript = service / "typescript"
    if not (typescript / "build" / "client.js").exists():
        step(["./node_modules/.bin/tsc", "-p", "generated/tsconfig.json"], typescript)
        step(["./node_modules/.bin/tsc", "src/client.ts", "--outDir", "build", "--module", "nodenext",
              "--target", "es2022", "--moduleResolution", "nodenext", "--types", "node"], typescript)
    python_env = {**os.environ, "PYTHONPATH": str(service / "python" / "generated")}
    return [
        # The 1.2 laboratory documents its pools as this one does, so the Python client also
        # reads the documentation back across the versions.
        ("python", [sys.executable, "src/client.py", "localhost", PORT],
         service / "python", python_env, ["documentation: registered by the server"]),
        ("typescript", ["node", "build/client.js", "localhost", PORT], typescript, dict(os.environ), []),
    ]


def main() -> int:
    kibo = jar()
    if kibo is None or not kibo.is_file():
        return skip("no kibo 1.2 jar (set KIBO_LTS_JAR, or build kibo on LTS-1.2)")
    for repository in (ROOT, PACK):
        if not has_branch(repository, "LTS-1.2"):
            return skip(f"no LTS-1.2 branch in {repository.name}")
    if not (VIPER / "src" / "Viper").is_dir():
        return skip(f"no {VIPER.name} checkout beside this repository")

    if not (ROOT / "service" / "python" / "generated").is_dir():
        return skip("the kibo 2 service is not rendered (run check.py, or kibo-project in service/)")

    server = build_server(kibo)
    process = subprocess.Popen([str(server), "-a", "localhost", "-p", PORT],
                               stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    ok = True
    try:
        time.sleep(1)
        for name, command, cwd, env, also in clients():
            result = subprocess.run(command, cwd=cwd, env=env, capture_output=True, text=True)
            missing = [line for line in EXPECTED + also if line not in result.stdout]
            good = result.returncode == 0 and not missing
            ok &= good
            detail = "every call went through" if good else \
                f"exit {result.returncode}, missing {missing}\n{result.stderr[-600:]}"
            print(f"{'ok  ' if good else 'FAIL'} kibo 2 {name} client -> 1.2 service "
                  f"({kibo.parent.parent.name}/{kibo.name}): {detail}")
    finally:
        process.terminate()
        process.wait()
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
