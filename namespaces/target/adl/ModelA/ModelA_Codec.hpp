// WHAT MODELA ACTUALLY OWNS: how its own types are written. Nothing else.
//
// This is the residue once the container machinery is a template. It is small, it is
// obviously ModelA's -- it knows Colour has three channels -- and it is the only thing
// that had to be generated per namespace all along.

#include "ModelA_Data.hpp"

namespace ModelA {

// `write`, not `write_ModelA_Colour`: the namespace is the scope, and overload
// resolution distinguishes the types. ModelB declares its own `write(Colour const&)`
// on a different Colour and neither is renamed -- which is what a namespace is for.
inline void write(Viper::Codec::Writer & w, Colour const & value) {
    write(w, value.r);      // ADL again, on std::uint8_t -> the primitive overload
    write(w, value.g);
    write(w, value.b);
}

inline void write(Viper::Codec::Writer & w, MaterialKey const & value) {
    w.stream()->writeUUId(value.instanceId());
    w.stream()->writeUUId(value.runtimeId());
}

// The type descriptor, which encode() needs and cannot get by ADL -- see the note in
// the Projection file.
template<> std::shared_ptr<Viper::Type> const & Viper::Codec::type<Colour>();
template<> std::shared_ptr<Viper::Type> const & Viper::Codec::type<MaterialKey>();

} // ns ModelA
