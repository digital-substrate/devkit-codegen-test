// ModelA — ses attachments, vus depuis une base de données.
//
// LA MÊME PORTÉE QUE L'ATTACHMENT EN MÉMOIRE, à un niveau près : `Database` au lieu
// d'`Attachments`. Le pack aplatit en `DatabaseAttachments::Material_Colour` pour la même
// raison qu'ailleurs -- une portée qui n'existait pas.
//
// ET LA BASE EST CELLE DU RUNTIME. Rien ici ne demande une classe par modèle.

#ifndef ModelA_Database_hpp
#define ModelA_Database_hpp

#include "ModelA_Data.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

namespace ModelA::Database::Material::colour {

std::set<MaterialKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, MaterialKey const & key);
std::optional<Colour> get(std::shared_ptr<Viper::Database const> const & db, MaterialKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key, Colour const & document);
bool del(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key);

} // namespace ModelA::Database::Material::colour

#endif
