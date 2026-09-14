# hand — the club and the untyped key, written from the model

Two shapes that `namespaces/` does not declare, and that the five templates therefore had
never produced. Written the way the rest of the reference is: from the model, compiled, and
with the runtime taken from `../../../runtime` rather than imagined.

```sh
clang++ -std=c++20 -fsyntax-only -I. -I../../../runtime *.cpp
```

## AnyConceptKey — nobody can claim it because it is nobody's

This is the question the whole line of work started from. The answer is a count: the
generated class has nine members, and **seven of them name no concept** — two uuids, their
comparisons, a hash, a validity test. The two that remain, `description()` and `isKnown()`,
need the model to say which concept an instance is.

So it is not a type that no namespace can claim. It is a **runtime type**, with two
operations attached to it that should never have been members. Moved out as free functions
of the injected module, which is the thing that carries the model, the class has nothing
left to generate and moves to `../../../runtime/Viper_AnyConceptKey.hpp`.

Free functions rather than members is the whole mechanism: one member would have forced the
entire class to be generated, which is exactly what happens today, for two lines.

## The club — the conversions belong to the club, not to the member

A club is a named set of concepts, and its key may name an instance of any of them.
Entering is free and implicit: a member is a member, so the constructor copies the two
uuids. Leaving is optional, and asks the same question `from` asks.

**The direction matters and the crossing model is what shows it.** `Woven::Weave` has
`Core::Thing` and `Parts::Thing` as members — two units that know nothing of Woven and that
Woven depends on. A conversion operator on the member would invert that edge. A converting
constructor on the club keeps it.

**And it forces a flat name, for the third time.** Both members are called `Thing`, so the
getters cannot both be `asThingKey()`, and a function name cannot contain `::`. Same shape
as the attachment scope: something has to be distinguished, the namespace is not available
to do it, so the name absorbs it. Here it is unavoidable — but it should happen on
principle rather than on collision, or adding a member renames another member's getter.

## Narrowing cannot be written with what a unit knows

The pack enumerates, in each concept's `from`, the runtime ids of every descendant known at
generation time. Flat, in one file, that works. Per unit it does not: a descendant of
`Core::Thing` may live in `Woven`, so `Core` would have to include `Woven` — the edge
backwards, since Woven is what depends on Core.

And it is not only a dependency problem. A descendant may be declared *after* Core was
generated, which the pack acknowledges in its own comment on `description`: *unknown
descendant at generation time*. The generation-time list is wrong the moment a model
extends.

"Is this instance a Thing?" is a question about the model's concept hierarchy. It is asked
of the model, and answered at run time — `Crossing::Codec::isMember(key, conceptType(…))`.
A club asks the same call with its club descriptor, because membership is not inheritance
and the difference is carried by the descriptor, not by the code.

## A layer the decomposition had not foreseen

`Core_Model.hpp` — the unit's own identity in the model: its runtime ids, and the type
descriptors resolved against the model's `Definitions`.

These were sitting with the codec, because the codec is what asked for them. But
`ThingKey::create()` needs its concept's runtime id and `ThingKey::from()` needs its
descriptor, and layer 1 has nothing to do with serialisation. They are not codec functions:
they are what a unit knows about itself with respect to the model, and two layers use them.

It lives in namespace `Core` and not `Core::Model`: `type(tag<T>)` has to be reachable by
argument-dependent lookup from the injected module, and lookup on `tag<Core::ThingKey>`
associates `Core`, not its sub-scopes. The scope here is the file, not the namespace.

## One hash shape, not two

Layer 1 had a key hashing through a member and a structure through a free function, a
distinction with no reason behind it. Everything now declares
`void hash(Viper::Hash::Accumulator &, T const &)` and every `std::hash` specialisation is
the same line.

The accumulator-first shape is not decoration. `hash(x)` on a `std::uint8_t` cannot work: a
fundamental type has no associated namespace, so argument-dependent lookup reaches nothing
and ordinary lookup stops inside the unit. A runtime-typed first argument restores it for
every type, exactly as the Writer does for `write`.
