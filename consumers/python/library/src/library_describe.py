"""The library's hand-written code, in Python: what it does with what it reads. It reads through its
own reads only, so it runs beside an application of either usage."""

from __future__ import annotations

import dsviper

from library import reads


def describe(getting: dsviper.AttachmentGetting | dsviper.Database) -> str:
    """Every product and part of a base, one line each, in key order: the same text for the same
    documents, whichever base holds them."""
    lines = []
    for key in sorted(reads.Product.properties.keys(getting), key=lambda k: str(k.instance_id())):
        line = f"product {key.instance_id()} has={int(reads.Product.properties.has(getting, key))}"
        document = reads.Product.properties.get(getting, key)
        if not document.is_nil():
            p = document.unwrap()
            line += f" name={p.name} price={p.price:g} tags={','.join(sorted(p.tags))},"
        lines.append(line)
    for part_key in sorted(reads.Part.properties.keys(getting), key=lambda k: str(k.instance_id())):
        line = f"part {part_key.instance_id()}"
        part = reads.Part.properties.get(getting, part_key)
        if not part.is_nil():
            q = part.unwrap()
            line += f" reference={q.reference} quantity={q.quantity}"
        lines.append(line)
    return "\n".join(lines)
