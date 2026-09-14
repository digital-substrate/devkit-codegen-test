#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

struct Writer { std::string out; };

// ── le socle : générique, indépendant du modèle, défini AVANT les namespaces ──
namespace Codec {
    inline void write(Writer & w, std::uint8_t v) { w.out += "u8(" + std::to_string(v) + ")"; }

    template<class K, class V>
    void write(Writer & w, std::map<K, V> const & m) {
        w.out += "map{";
        for (auto const & [k, e] : m) { write(w, k); w.out += "->"; write(w, e); }
        w.out += "}";
    }

    template<class T>
    void write(Writer & w, std::vector<T> const & v) {
        w.out += "vec[";
        for (auto const & e : v) write(w, e);
        w.out += "]";
    }

    template<class T> auto encode(T const & v) { Writer w; write(w, v); return w.out; }
}

// ── les unités, définies APRÈS le socle ──
namespace ModelA {
    struct Material { std::uint8_t id; };
    bool operator<(Material const & a, Material const & b) { return a.id < b.id; }
    void write(Writer & w, Material const & v) { w.out += "A::Material("; Codec::write(w, v.id); w.out += ")"; }
}
namespace ModelB {
    struct Material { std::uint8_t id; };          // même nom, autre type
    void write(Writer & w, Material const & v) { w.out += "B::Material("; Codec::write(w, v.id); w.out += ")"; }
}
namespace Projection {
    struct Pair { ModelA::Material a; ModelB::Material b; };
    void write(Writer & w, Pair const & v) { w.out += "Pair("; write(w, v.a); w.out += ","; write(w, v.b); w.out += ")"; }
}

int main() {
    using Codec::encode;
    std::map<ModelA::Material, ModelB::Material> m{{{1}, {2}}};
    std::cout << "map qui enjambe : " << encode(m) << "\n";
    std::cout << "Pair            : " << encode(Projection::Pair{{7}, {8}}) << "\n";
    std::cout << "vector d'unite  : " << encode(std::vector<ModelA::Material>{{3}, {4}}) << "\n";
}
