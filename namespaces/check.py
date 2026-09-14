#!/usr/bin/env python3
"""Prove this model exercises what it claims to. Run after regenerating the JSON.

Each assertion below corresponds to a defect that has shipped, or to a path the
rest of the validation corpus -- all of it mono-namespace -- cannot reach.
"""
import json, sys, collections
from pathlib import Path

d = json.load(open(Path(__file__).parent / "Topology.dsm.json"))
ok, bad = [], []
def check(label, cond, detail=""):
    (ok if cond else bad).append(f"{label}{(' — ' + detail) if detail else ''}")

def refs(node, out):
    """Every concept/structure reference inside a type, at any depth."""
    if isinstance(node, dict):
        if node.get("class_name") == "reference":
            out.append((node.get("namespace_name"), node.get("name")))
        for v in node.values(): refs(v, out)
    elif isinstance(node, list):
        for v in node: refs(v, out)
    return out

ns = lambda e: e.get("namespace_name")
namespaces = {ns(e) for k in ("concepts", "structures", "enumerations", "clubs", "attachments")
              for e in d[k] if ns(e)}

check("multi-namespace", len(namespaces) >= 3, f"{len(namespaces)}: {', '.join(sorted(namespaces))}")

names = collections.Counter()
for k in ("concepts", "structures", "enumerations"):
    for e in d[k]: names[e["name"]] += 1
clash = [n for n, c in names.items() if c > 1]
check("name collision across namespaces", clash, ", ".join(clash))

# which namespaces are reached, and through what
by_attachment, by_field, by_parent = set(), set(), set()
for a in d["attachments"]:
    for n, _ in refs(a.get("document_type"), []) + refs(a.get("key_type"), []):
        if n and n != ns(a): by_attachment.add(n)
for s in d["structures"]:
    for f in s.get("fields", []):
        for n, _ in refs(f, []):
            if n and n != ns(s): by_field.add(n)
for c in d["concepts"]:
    for n, _ in refs(c.get("parent"), []):
        if n and n != ns(c): by_parent.add(n)

only_attachment = by_attachment - by_field - by_parent
check("a namespace reached ONLY through an attachment", only_attachment, ", ".join(sorted(only_attachment)))
check("a key<NS::C> edge in a structure field", by_field, ", ".join(sorted(by_field)))
check("a concept parent crossing namespaces", by_parent, ", ".join(sorted(by_parent)))

holders = collections.defaultdict(set)
for k in ("concepts", "structures", "enumerations", "clubs", "attachments"):
    for e in d[k]:
        if ns(e): holders[ns(e)].add(k)
bare = [n for n, kinds in holders.items() if kinds == {"attachments"}]
check("a namespace holding only attachments", bare, ", ".join(bare))

spanning = []
for a in d["attachments"]:
    seen = {n for n, _ in refs(a.get("document_type"), []) if n}
    if len(seen) >= 2: spanning.append(f'{a["name"]} → {", ".join(sorted(seen))}')
check("a container shape spanning two namespaces", spanning, "; ".join(spanning))

pools = d["function_pools"] + d["attachment_function_pools"]
voids, bare_pool, spanning_pool = [], [], []
for p in pools:
    for f in p.get("functions", []):
        proto = f.get("prototype", f)
        ret = proto.get("return_type") or {}
        if ret.get("domain") == "primitive" and ret.get("name") == "void":
            voids.append(f'{p["name"]}.{proto.get("name")}')
    seen = {n for n, _ in refs(p.get("functions"), []) if n}
    (bare_pool if not seen else spanning_pool if len(seen) >= 2 else []).append(p["name"])

check("a pool referencing no namespaced type", bare_pool, ", ".join(bare_pool))
check("a pool spanning two namespaces", spanning_pool, ", ".join(spanning_pool))
check("a void return in a pool", voids, ", ".join(voids))

# Two attachments in one namespace, same name, on same-named concepts of two others.
# The generator must qualify both scopes; it qualifies none while only one exists, so
# adding the second renames the first.
seen, clashing = {}, []
for a in d["attachments"]:
    concept = refs(a.get("key_type"), [])
    if not concept: continue
    cns, cname = concept[0]
    k = (ns(a), a["name"], cname)
    if k in seen and seen[k] != cns: clashing.append(f'{ns(a)}.{a["name"]} on {seen[k]}::{cname} and {cns}::{cname}')
    seen[k] = cns
check("two attachments needing their key namespace to tell them apart", clashing, "; ".join(clashing))

for line in ok:  print(f"  ok    {line}")
for line in bad: print(f"  MANQUE {line}")
sys.exit(1 if bad else 0)
