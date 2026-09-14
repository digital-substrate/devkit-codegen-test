// ModelB — everything its types need in order to cross into the runtime.
//
// Layer 3, the bridge. And it is short, which is the finding: a unit implements two
// things, and every other serialisation in the pack is a generic composition of them.
//
// TRACED, NOT ASSUMED. `encode_ModelB_Colour` writes to a stream and decodes the result
// into a Value. `Json` does the same through a json codec. `hexdigest_X` encodes and then
// hashes. Four domains in the pack -- Stream, ValueCodec, Json, ValueHasher -- and one
// implementation underneath: how ModelB's own types go onto a stream, and what type they
// are. Everything above that is a transformation no namespace needs to know about.

#ifndef ModelB_Codec_hpp
#define ModelB_Codec_hpp

#include "ModelB_Data.hpp"

#include "Viper_Codec.hpp"          // Writer, Reader, tag<T>, and the generic layer

namespace ModelB {

// ── the only thing ModelB genuinely implements ──
//
// Free functions, in the type's own namespace, because that is how the generic layer
// reaches them. `write(w, someSet)` on a std::set<Colour> finds the runtime's template,
// which calls `write(w, element)` on each Colour, and argument-dependent lookup brings it
// here. Nothing names ModelB; the argument does.

void write(Viper::Codec::Writer & w, Colour const & value);
void write(Viper::Codec::Writer & w, MaterialKey const & value);

Colour      read(Viper::Codec::Reader & r, Viper::Codec::tag<Colour>);
MaterialKey read(Viper::Codec::Reader & r, Viper::Codec::tag<MaterialKey>);

// ── and what the runtime must be told about the shape of these types ──

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<MaterialKey>);

} // namespace ModelB

// What is NOT here, and must not be:
//
//   encode / decode        generic, over write / read
//   json encode / decode   generic
//   hash                   generic, over encode
//   write(std::set<T>)     generic, and std::set is not ModelB's
//   write(std::int64_t)    the runtime's, identical in every model ever generated
//
// The pack emits all of them, once per shape per model, under names that carry the
// namespace because nothing else scoped them. Written generically they are nine
// templates in the runtime, and ModelB is left with the seven declarations above.

#endif
