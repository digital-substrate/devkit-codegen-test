// ModelA — l'implémentation, qui est cinq renvois.
//
// Le corps de chacune est celui du socle, instancié sur la clé et le document. Ce qui reste
// propre à cet attachment est son identifiant -- et il est déjà déclaré à côté de ses
// opérations en mémoire, donc il n'est pas redéclaré ici.

#include "ModelA_Database.hpp"

#include "ModelA_Attachments.hpp"  // runtimeId
#include "ModelA_Codec.hpp"        // write, read

#include "Topology_Db.hpp"

namespace ModelA::Database::Material::colour {

namespace {
auto const & attachment() { return ModelA::Attachments::Material::colour::runtimeId; }
}

std::set<MaterialKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Topology::Db::keys<MaterialKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, MaterialKey const & key) {
    return Topology::Db::has(db, attachment(), key);
}

std::optional<Colour> get(std::shared_ptr<Viper::Database const> const & db, MaterialKey const & key) {
    return Topology::Db::get<Colour>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key, Colour const & document) {
    return Topology::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key) {
    return Topology::Db::del(db, attachment(), key);
}

} // namespace ModelA::Database::Material::colour
