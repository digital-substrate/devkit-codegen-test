// Les types scalaires du runtime que le modèle peut nommer directement.
#ifndef Viper_Scalars_hpp
#define Viper_Scalars_hpp
#include <cstddef>
#include <string>
#include <vector>
namespace Viper {
struct BlobId { std::string value; bool operator==(BlobId const &) const = default; bool operator<(BlobId const & o) const { return value < o.value; } };
struct CommitId { std::string value; bool operator==(CommitId const &) const = default; bool operator<(CommitId const & o) const { return value < o.value; } };
struct Blob { std::vector<std::byte> bytes; bool operator==(Blob const &) const = default; bool operator<(Blob const & o) const { return bytes < o.bytes; } };
/// Une séquence ordonnée dont les positions sont stables : le conteneur propre au runtime.
template<class T> class XArray final {
public:
    bool operator==(XArray const &) const = default;
    bool operator<(XArray const &) const { return false; }
};

class Any { public: bool operator==(Any const &) const = default; bool operator<(Any const &) const { return false; } };
}
#endif
