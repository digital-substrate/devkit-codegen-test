#!/usr/bin/env python3
"""Écrire la base de référence, sous un runtime 1.2 -- une fois, pas à chaque épreuve.

La base qu'elle produit, `Compat-1.2.cdb`, est versionnée : c'est elle que les épreuves
relisent, et c'est parce qu'elle ne bouge pas qu'elle dit quelque chose. La réécrire n'a de
sens que pour y ajouter une forme, et toujours sous un dsviper 1.2 -- sinon ce ne serait plus
une base 1.2.

LE RUNTIME, PAS UN CODE GÉNÉRÉ. Ce qu'une base contient -- ses définitions, ses `Value`, son
codec -- est l'affaire du runtime seul ; un code généré ne fait que bâtir des `Value` que le
runtime vérifie contre les définitions. Écrire ici par dsviper, c'est fixer ce qu'une base 1.2
est, sans dépendre d'aucune génération, ancienne ou nouvelle.

Les valeurs sont celles que `cpp/src/read.cpp` attend. Chacune est choisie pour qu'une erreur
se lise : des octets tous différents, une mat non carrée aux cases toutes distinctes, une
alternative de variant qui n'est pas la première.
"""
from pathlib import Path

import dsviper
from dsviper import (Database, DSMBuilder, BlobLayout, TypeConcept, TypeKey, TypeVariant, ValueAny, ValueBlob,
                     ValueCommitId, ValueKey, ValueString, ValueUUId, ValueVariant)

HERE = Path(__file__).resolve().parent
BASE = HERE / "Compat-1.2.cdb"

# Les clés sont fixées : l'épreuve les reconstruit sans rien lire d'autre que ce fichier.
PROBE = "c0a7c0de-0001-4000-8000-000000000001"
OTHER = "c0a7c0de-0002-4000-8000-000000000002"
OTHER_BIS = "c0a7c0de-0003-4000-8000-000000000003"


def main() -> int:
    if dsviper.version()[:2] != (1, 2):
        print(f"dsviper {dsviper.version()} : une base de référence s'écrit sous un runtime 1.2")
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
        "docString": "Écrit par la 1.2",
        "docBlob": ValueBlob(bytes([0x00, 0x01, 0x7F, 0x80, 0xFE, 0xFF])),
        "docVec": [1, -2, 0x01020304],
        "docMat": [[1, 2, 3], [4, 5, 6]],
        "docTuple": (7, "sept"),
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
    db = Database.create(str(BASE), documentation="Compat 1.2 -- base de référence")
    db.extend_definitions(definitions)
    db.begin_transaction()
    # Un blob_id désigne un blob que la base tient : il y entre d'abord.
    values["docBlobId"] = db.create_blob(BlobLayout(), ValueBlob(bytes([1, 2, 3, 4, 5])))
    for name, value in values.items():
        attachment = attachments[name]
        if not db.set(attachment, attachment.create_key(ValueUUId(PROBE)), value):
            print(f"{name} : refusé")
            return 1
    db.commit()
    db.close()
    print(f"{BASE.name} : {len(values)} attachments, codec {Database.open(str(BASE), True).codec_name()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
