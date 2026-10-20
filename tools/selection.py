#!/usr/bin/env python3
"""What the feature selection renders -- and what it does not.

A model that declares pools does not impose pools on the generated code. A pure Python
application cannot build a pool: it selects `Base`, and must receive a package without a
single pool directory. While a pool's entry point lived in the unit template, it received one
per pool, importing a missing module. This script renders the `namespaces` model -- three
pools -- with `Base` alone and then with each binding's pool clients.

Nor does a model with attachments impose them: `Base` is the data alone, `CommitAttachments`
brings the attachments of a Commit state with the paths and field names they address, and
`DatabaseAttachments` the attachments of a Database, with nothing of Commit: no Commit module,
no Commit type outside the runtime.
"""
import json
import re
import sys
import tempfile
import tomllib
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from render import ROOT, generate                       # noqa: E402

SITE = ROOT / "namespaces"


def pools(dsm: Path) -> set[str]:
    """The package directory each pool of the model renders to."""
    data = json.loads(dsm.read_text())
    names = [p["name"] for key in ("function_pools", "attachment_function_pools")
             for p in data.get(key, [])]
    # A pool's package is its name in lower snake case, as the layout writes it.
    return {re.sub(r"(?<!^)(?=[A-Z])", "_", n).lower() for n in names}


def rendered(language: str, features: list[str]) -> tuple[set[str], set[str], set[str], str]:
    """Render the site's model with these features alone; return the directories rendered, the
    pools the model declares, the file stems and the text of the files outside the runtime. The
    project is the site's, but for the target."""
    site = tomllib.loads((SITE / "kibo.toml").read_text())
    with tempfile.TemporaryDirectory() as out:
        project = Path(out) / "kibo.toml"
        project.write_text(
            "[project]\n"
            f"definitions = {json.dumps(str(SITE / site['project']['definitions']))}\n"
            f"infrastructure = {json.dumps(site['project']['infrastructure'])}\n"
            "[generator]\n"
            f"templates = {json.dumps(site['generator']['templates'])}\n"
            f"[target.{language}]\n"
            f"features = {json.dumps(features)}\n"
            'output = "out"\n')
        error = generate(project, out)
        if error:
            raise SystemExit(error)
        dsm = Path(out) / f"{site['project']['infrastructure']}.dsm.json"
        generated = [p for p in (Path(out) / "out").rglob("*") if p.is_file()]
        files = {p.stem for p in generated}
        text = "\n".join(p.read_text() for p in generated
                         if "_codegen" not in p.parts and p.suffix in (".py", ".ts"))
        return {p.name for p in (Path(out) / "out").rglob("*") if p.is_dir()}, pools(dsm), files, text


def main() -> int:
    ok = True
    for language in ("python", "typescript"):
        alone, expected, alone_files, _ = rendered(language, ["Base"])
        with_pool, _, _, _ = rendered(language, ["Base", "PoolRemote", "AttachmentPoolRemote"])
        _, _, attached_files, _ = rendered(language, ["Base", "CommitAttachments"])
        _, _, database_files, database_text = rendered(language, ["Base", "DatabaseAttachments"])
        addressing = {"commit_attachments", "paths", "fields"}
        separate = not (alone_files & addressing) and addressing <= attached_files
        ok &= separate
        print(f"  {'ok  ' if separate else 'FAIL'} {language}: Base alone -> "
              f"{sorted(alone_files & addressing) or 'no attachments'}, with CommitAttachments -> "
              f"{sorted(attached_files & addressing)}")
        commit = sorted({w for w in ("AttachmentMutating", "AttachmentGetting", "CommitState", "Mutating")
                         if re.search(rf"\b{w}\b", database_text)})
        alone_db = "database_attachments" in database_files and not (database_files & addressing) and not commit
        ok &= alone_db
        print(f"  {'ok  ' if alone_db else 'FAIL'} {language}: DatabaseAttachments -> "
              f"{sorted(database_files & (addressing | {'database_attachments'}))}, Commit types: "
              f"{commit or 'none'}")
        alone, with_pool = alone & expected, with_pool & expected
        good = bool(expected) and not alone and with_pool == expected
        ok &= good
        print(f"  {'ok  ' if good else 'FAIL'} {language}: Base alone -> {sorted(alone) or 'no pool'}, "
              f"with the pool clients -> {sorted(with_pool)}")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
