#include <cstdint>
#include <map>
#include <string>
#include <iostream>

struct Reader { std::string in; std::size_t p = 0; };

namespace Codec {
    template<class T> struct tag {};                    // le porteur du namespace associé

    inline std::uint8_t read(Reader & r, tag<std::uint8_t>) { return r.in[r.p++] - '0'; }

    template<class K, class V>
    std::map<K, V> read(Reader & r, tag<std::map<K, V>>) {
        std::map<K, V> m;
        auto k = read(r, tag<K>{});                     // ADL : tag<ModelA::Material>
        auto v = read(r, tag<V>{});
        m.emplace(k, v);
        return m;
    }

    template<class T> T decode(Reader & r) { return read(r, tag<T>{}); }
}

namespace ModelA {
    struct Material { std::uint8_t id; };
    bool operator<(Material const & a, Material const & b) { return a.id < b.id; }
    Material read(Reader & r, Codec::tag<Material>) { return {Codec::read(r, Codec::tag<std::uint8_t>{})}; }
}
namespace ModelB {
    struct Material { std::uint8_t id; };
    Material read(Reader & r, Codec::tag<Material>) { return {Codec::read(r, Codec::tag<std::uint8_t>{})}; }
}

int main() {
    Reader r{"47"};
    auto m = Codec::decode<std::map<ModelA::Material, ModelB::Material>>(r);
    for (auto const & [k, v] : m)
        std::cout << "décodé : A::Material(" << int(k.id) << ") -> B::Material(" << int(v.id) << ")\n";
}
