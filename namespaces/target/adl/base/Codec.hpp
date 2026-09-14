// THE BASE, AND IT IS NO LONGER GENERATED PER MODEL.
//
// Every container encoder kibo emits today has the same body, differing only in the
// name it calls. Written once as a template, that name is resolved by the compiler:
//
//   Today, generated once per shape per model:
//
//     void Writer::write_map_ModelA_MaterialKey_to_ModelB_MaterialKey(
//             std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value) {
//         streamWriting->writeUInt64(value.size());
//         for (auto const & [k, e] : value) {
//             write_ModelA_MaterialKey(k);
//             write_ModelB_MaterialKey(e);
//         }
//     }
//
// The two inner calls are what typeSuffix exists to spell. Overload resolution plus
// argument-dependent lookup spell them for free, and they land in the namespace that
// owns each type -- which is the whole objective: the base builds ON the per-namespace
// implementation rather than containing it.

namespace Viper::Codec {

// One template per DSM container kind. Nine of them, model-independent, so they belong
// in the runtime rather than in generated output.

template<class K, class V>
void write(Writer & w, std::map<K, V> const & value) {
    w.stream()->writeUInt64(value.size());
    for (auto const & [k, e] : value) {
        write(w, k);        // ADL: ModelA::write
        write(w, e);        // ADL: ModelB::write
    }
}

template<class T>
void write(Writer & w, std::vector<T> const & value) {
    w.stream()->writeUInt64(value.size());
    for (auto const & e : value) write(w, e);
}

template<class T> void write(Writer &, std::set<T> const &);
template<class T> void write(Writer &, std::optional<T> const &);
template<class... T> void write(Writer &, std::variant<T...> const &);
template<class T, std::size_t N> void write(Writer &, std::array<T, N> const &);
// ... xarray, tuple, mat ...

// encode() likewise: one template, where today there is one function per shape.
template<class T>
auto encode(T const & value) {
    auto const encoder{instancing()->createEncoder()};
    Writer w{encoder};
    write(w, value);                                   // ADL
    return Viper::ValueDecoder::decode(encoder->endEncoding(), instancing(),
                                       type<T>(),      // see the note on decode below
                                       definitions());
}

} // ns Viper::Codec
