// Topology — les cinq opérations d'un attachment stocké, une fois pour toutes.
//
// LA MÊME SURFACE QU'UN ATTACHMENT EN MÉMOIRE, SUR UN AUTRE SUPPORT. `keys`, `has`, `get`,
// `set`, `del` -- et rien de ce qu'elles font ne dépend d'un attachment en particulier :
// convertir la clé, encoder ou décoder le document, appeler la base. Le pack écrit les cinq
// une fois par attachment ; écrites en templates sur la clé et le document, elles ne
// demandent plus qu'un identifiant.
//
// ET ELLES PRENNENT LA BASE DU RUNTIME. La classe `Database` que le pack génère n'ajoute
// rien : sur ses 1 638 lignes, le modèle n'apparaît qu'aux quatre endroits où les
// définitions sont écrites dans une base neuve ou vérifiées sur une base ouverte. C'est un
// argument, et le prendre comme tel laisse deux modèles partager une poignée.

#ifndef Topology_Db_hpp
#define Topology_Db_hpp

#include "Topology_Codec.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

namespace Topology::Db {

/// La clé, telle que le stockage la connaît.
template<class Key>
Viper::Key stored(Key const & key) {
    return {key.instanceId(), key.runtimeId()};
}

template<class Key>
std::set<Key> keys(std::shared_ptr<Viper::Database const> const & db, Viper::UUId const & attachment) {
    std::set<Key> result;
    for (auto const & k : db->keys(attachment))
        result.insert(Key{k.instanceId, k.runtimeId});

    return result;
}

template<class Key>
bool has(std::shared_ptr<Viper::Database const> const & db, Viper::UUId const & attachment, Key const & key) {
    return db->has(attachment, stored(key));
}

/// LE DOCUMENT EST STOCKÉ ENCODÉ, donc il traverse le même flux que partout ailleurs -- et
/// le contrat de format est celui du ValueWriter, comme pour le pont statique/dynamique.
template<class Document, class Key>
std::optional<Document> get(std::shared_ptr<Viper::Database const> const & db,
                            Viper::UUId const & attachment, Key const & key) {
    auto const encoded = db->get(attachment, stored(key));
    if (!encoded)
        return std::nullopt;

    auto const decoder = db->streamCodecInstancing()->createDecoder(*encoded);
    Viper::Codec::Reader reader{decoder, db->definitions()};

    return read(reader, Viper::Codec::tag<Document>{});     // ADL : l'unité du document
}

template<class Document, class Key>
bool set(std::shared_ptr<Viper::Database> const & db, Viper::UUId const & attachment,
         Key const & key, Document const & document) {
    auto const encoder = db->streamCodecInstancing()->createEncoder();
    Viper::Codec::Writer writer{encoder};
    write(writer, document);                                // ADL : l'unité du document

    return db->set(attachment, stored(key), encoder->endEncoding());
}

template<class Key>
bool del(std::shared_ptr<Viper::Database> const & db, Viper::UUId const & attachment, Key const & key) {
    return db->del(attachment, stored(key));
}

} // namespace Topology::Db

#endif
