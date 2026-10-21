"""The documents both applications write, each through its own usage: the same keys and values as
the C++ fixture, so that what the library reads back can be compared across the two."""

from __future__ import annotations

from shop import store

PRODUCTS = [
    ("0b0f8a52-58a3-4bd1-9b8e-1f4a0f3f6a01", "drill", 129.5, {"tool", "electric"}),
    ("7c2d9e10-4b11-4c2a-8d33-2a5b6c7d8e02", "hammer", 19.0, {"tool"}),
]
PARTS = [
    ("3e4f5a6b-7c8d-4e9f-a0b1-c2d3e4f5a603", "bit-8mm", 12),
]


def products() -> list[tuple[store.ProductKey, store.ProductProperties]]:
    result = []
    for uuid, name, price, tags in PRODUCTS:
        value = store.ProductProperties()
        value.name = name
        value.price = price
        for tag in tags:
            value.tags.add(tag)
        result.append((store.ProductKey(uuid), value))
    return result


def parts() -> list[tuple[store.PartKey, store.PartProperties]]:
    result = []
    for uuid, reference, quantity in PARTS:
        value = store.PartProperties()
        value.reference = reference
        value.quantity = quantity
        result.append((store.PartKey(uuid), value))
    return result
