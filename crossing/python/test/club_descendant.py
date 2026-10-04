#!/usr/bin/env python3
"""A club key designates a member, or an instance of a concept that descends from one.

`Woven::Weave` declares `Core::Thing` as a member; `Core::SubThing` and `Woven::Derived`
descend from it. The runtime makes a club key from any of them, and the generated C++
accepts them through its member's key: the Python key accepts them too.
"""
import sys
from pathlib import Path

package = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else Path.cwd()
sys.path.insert(0, str(package))

from crossing import core, woven                                    # noqa: E402

ok = True


def check(label, condition):
    global ok
    print(f"  {'ok  ' if condition else 'FAIL'} {label}")
    ok = ok and condition


derived = woven.DerivedKey.create()
weave = woven.WeaveKey(derived.to_parent_key())
check("a key of a descendant, held as its member's key, makes a club key",
      weave.instance_id() == derived.instance_id())
check("which reads back as the member's key", weave.to_core_thing_key() is not None)
check("and not as the other member's", weave.to_parts_thing_key() is None)

sub = core.SubThingKey.create()
check("a key of a descendant itself makes a club key",
      woven.WeaveKey(sub).instance_id() == sub.instance_id())
check("from_any_concept_key accepts a descendant",
      woven.WeaveKey.from_any_concept_key(sub.to_any_concept_key()) is not None)
check("from_any_concept_key still answers None outside the club",
      woven.WeaveKey.from_any_concept_key(core.OtherKey.create().to_any_concept_key()) is None)

try:
    woven.WeaveKey(core.OtherKey.create())
    check("a key outside the club is refused", False)
except TypeError:
    check("a key outside the club is refused", True)

raise SystemExit(0 if ok else 1)
