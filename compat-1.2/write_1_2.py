#!/usr/bin/env python3
"""Write the reference database under a 1.2 runtime -- once, not on every test run.

The database it produces, `Compat-1.2.cdb`, is committed: the tests read it back, and it is
meaningful because it does not change. Rewrite it only to add a shape, and always under
dsviper 1.2 -- otherwise it would no longer be a 1.2 database.

The database is written by the runtime, not by generated code. What a database holds -- its
definitions, its `Value`s, its codec -- is the runtime's business; generated code only builds
`Value`s the runtime checks against the definitions. Writing through dsviper pins what a 1.2
database is without depending on any generation, old or new.

The values are those `cpp/src/read.cpp` expects. Each is chosen to make a mistake visible:
bytes that all differ, a non-square mat with distinct cells, a variant alternative that is
not the first.
"""
from pathlib import Path

import dsviper
from dsviper import (Database, DSMBuilder, BlobLayout, TypeConcept, TypeKey, TypeVariant, ValueAny, ValueBlob,
                     ValueCommitId, ValueKey, ValueString, ValueUUId, ValueVariant)

HERE = Path(__file__).resolve().parent
BASE = HERE / "Compat-1.2.cdb"

# The keys are fixed: the test rebuilds them without reading anything but this file.
PROBE = "c0a7c0de-0001-4000-8000-000000000001"
OTHER = "c0a7c0de-0002-4000-8000-000000000002"
OTHER_BIS = "c0a7c0de-0003-4000-8000-000000000003"


def main() -> int:
    if dsviper.version()[:2] != (1, 2):
        print(f"dsviper {dsviper.version()}: a reference database must be written under a 1.2 runtime")
        return 1

    report, _, definitions = DSMBuilder.assemble(str(HERE / "definitions")).parse()
    if report.has_error():
        for e in report.errors():
            print(repr(e))
        return 1

    attachments = {a.identifier().rsplit(".", 1)[1]: a for a in definitions.attachments()}
    other = TypeConcept.cast(TypeKey.cast(attachments["docKey"].document_type()).element_type())

    point = {"x": 1.5, "y": -2.25}
    record = {
        "name": "Record",
        "origin": point,
        "grid": [[11, 12, 13], [21, 22, 23]],
        "shade": "dark",
        "samples": [-300, 0, 300],
    }

    values = {
        "docBool": True,
        "docUInt8": 0xA1,
        "docUInt16": 0xA1B2,
        "docUInt32": 0xA1B2C3D4,
        "docUInt64": 0xA1B2C3D4E5F60718,
        "docInt8": -0x5F,
        "docInt16": -0x5E4E,
        "docInt32": -0x5E4D3C2C,
        "docInt64": -0x5E4D3C2B1A09F8E8,
        "docFloat": 1.5,
        "docDouble": -2.25,
        "docUUId": ValueUUId("0f1e2d3c-4b5a-4968-8778-a695b4c3d2e1"),
        "docCommitId": ValueCommitId("0123456789abcdef0123456789abcdef01234567"),
        "docString": "Written by 1.2",
        "docBlob": ValueBlob(bytes([0x00, 0x01, 0x7F, 0x80, 0xFE, 0xFF])),
        "docVec": [1, -2, 0x01020304],
        "docMat": [[1, 2, 3], [4, 5, 6]],
        "docTuple": (7, "seven"),
        "docOptional": 0x0102,
        "docVectorMat": [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]],
        "docSet": {"alpha", "beta", "gamma"},
        "docMap": {"a": point, "b": {"x": -0.5, "y": 1e300}},
        "docXArray": [3, 1, 2],
        "docVariant": ValueVariant(TypeVariant.cast(attachments["docVariant"].document_type()), point),
        "docAny": ValueAny(ValueString("any")),
        "docShade": "medium",
        "docPoint": point,
        "docRecord": record,
        "docKey": ValueKey.create(other, OTHER),
        "docNested": {ValueKey.create(other, OTHER): [record],
                      ValueKey.create(other, OTHER_BIS): [record, {**record, "name": "bis", "shade": "light"}]},
    }

    BASE.unlink(missing_ok=True)
    db = Database.create(str(BASE), documentation="Compat 1.2 -- reference database")
    db.extend_definitions(definitions)
    db.begin_transaction()
    # A blob_id designates a blob the database holds: store the blob first.
    values["docBlobId"] = db.create_blob(BlobLayout(), ValueBlob(bytes([1, 2, 3, 4, 5])))
    for name, value in values.items():
        attachment = attachments[name]
        if not db.set(attachment, attachment.create_key(ValueUUId(PROBE)), value):
            print(f"{name}: rejected")
            return 1
    db.commit()
    db.close()
    print(f"{BASE.name}: {len(values)} attachments, codec {Database.open(str(BASE), True).codec_name()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
