#!/usr/bin/env python3
"""Fail-fast, tested on the rendered package.

A proxy holds nothing: it is an empty box around a `Value`, so every write reaches the
runtime, which raises its typed exception -- fail-fast is inherited, not implemented. What
must be checked is that nothing in the generated layer intercepts or bypasses it.

Both kinds of error count. `ViperError` comes from the runtime, when a value of the wrong
type reaches it. `TypeError` comes from the generated code, when a constructor rejects a
`Value` that is not its own, before any write happens. The pack pins the latter in
`test_fail_fast.py`: these are `raise`, not `assert`, so the contract also holds under
`python -O`, where assertions are stripped.
"""
import sys
from pathlib import Path

package = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else Path.cwd()
sys.path.insert(0, str(package))

import dsviper                                                      # noqa: E402

from crossing import containers, core, parts, definitions           # noqa: E402
from crossing.core import attachments as a                          # noqa: E402
from crossing._codegen import proxy, wrap                           # noqa: E402

ok = True
mutating = dsviper.CommitMutableState(dsviper.CommitState(definitions())).attachment_mutating()


def refuses(label, fn):
    global ok
    try:
        fn()
        print(f"  FAIL {label} -- passes without error")
        ok = False
    except (dsviper.ViperError, TypeError):
        print(f"  ok   {label}")


refuses("a field rejects a string where a number is expected",
        lambda: setattr(core.Colour(), "r", "red"))
refuses("a field rejects the Colour of another unit",
        lambda: setattr(core.Defaults(), "f_colour", parts.Colour()))
refuses("a container rejects an element of the wrong type",
        lambda: setattr(core.Bag(), "tints", [parts.Colour()]))
refuses("a key rejects the identifier of another concept",
        lambda: core.ThingKey(core.OtherKey.create().unwrap_value()))
refuses("an attachment rejects a key of another concept",
        lambda: a.Thing.colour.set(mutating, core.OtherKey.create(), core.Colour()))
refuses("an attachment rejects a document of the wrong type",
        lambda: a.Thing.colour.set(mutating, core.ThingKey.create(), parts.Colour()))
refuses("wrap_value rejects a homonym structure of another namespace",
        lambda: core.Colour.wrap_value(parts.Colour().unwrap_value()))
refuses("wrap_value rejects a homonym enumeration of another namespace",
        lambda: parts.Grade.wrap_value(core.Grade.HIGH.unwrap_value()))
refuses("a tuple refuses its homonym elements swapped",
        lambda: containers.Tuple_of_Core_Colour_and_Parts_Colour([parts.Colour(), core.Colour()]))

# `wrap` must not fall back to returning the bare value when a type has no registered class:
# that would contradict the annotation, which type checking cannot catch, and would only
# surface much later as a missing attribute.
saved = proxy._CLASSES.pop(core.data.COLOUR.encoded())
refuses("wrap fails if a unit is not imported, instead of returning the bare value",
        lambda: wrap(core.Colour(r=1, g=2, b=3).unwrap_value()))
proxy._CLASSES[core.data.COLOUR.encoded()] = saved

raise SystemExit(0 if ok else 1)
