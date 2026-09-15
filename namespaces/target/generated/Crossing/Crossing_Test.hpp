// Crossing — de quoi éprouver n'importe quel type du modèle, sans rien savoir d'aucun.
//
// SEPT ARTEFACTS DU PACK TIENNENT ICI, et ce n'est pas une compression : c'est ce que leur
// propre source dit. `TestFuzz::fuzz_X()` vaut `decode_X(TestValueFuzz::fuzz_X())`,
// `TestValueFuzz::fuzz_X()` vaut `fuzzer()->fuzzType(type_X())`, et chaque `test_X` des
// trois codecs est un aller-retour dont seul le suffixe change. Une fois écrits en
// fonctions template au-dessus de `type(tag<T>{})`, il n'en reste rien par type.
//
// LE FUZZ N'EST PAS CELUI D'UNE UNITÉ, et c'est la correction que ce fichier apporte. Le
// premier jet déclarait `fuzz(Rng&, tag<T>)` dans chaque unité, en supposant qu'elle seule
// sait comment fabriquer un de ses types. Elle ne le sait pas mieux que le runtime : celui-
// ci part du descripteur de type, que l'unité fournit déjà. Une unité n'a donc rien à
// implémenter pour être éprouvée.

#ifndef Crossing_Test_hpp
#define Crossing_Test_hpp

#include "Crossing_Codec.hpp"
#include "Crossing_Db.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_ValueSetIter.hpp"
#include "Viper_ValueOptional.hpp"
#include "Viper_Key.hpp"
#include "Viper_TypeConcept.hpp"

#include "Viper_Database.hpp"

#include "Viper_GeneralErrors.hpp"
#include "Viper_Fuzzer.hpp"
#include "Viper_JsonValueEncoder.hpp"
#include "Viper_JsonValueDecoder.hpp"

#include <memory>

namespace Crossing::Test {

/// Le fabricant, construit une fois sur le modèle. Une graine le rend reproductible.
std::shared_ptr<Viper::Fuzzer> const & fuzzer();
void seed(std::uint64_t value);

/// Une valeur aléatoire de T, côté dynamique puis côté statique.
template<class T>
std::shared_ptr<Viper::Value> fuzzValue() {
    return fuzzer()->fuzzType(type(Viper::Codec::tag<T>{}));   // ADL : l'unité de T
}

template<class T>
T fuzz() {
    return Codec::decode<T>(fuzzValue<T>());
}

// ── les trois allers-retours, un par codec ──
//
// Chacun est ce que le pack écrit une fois par type et par codec, avec le suffixe pour
// seule variable. Écrits une fois ici, ils ne demandent plus qu'une liste de types.

/// Fabriquer, écrire sur un flux, relire, comparer.
template<class T>
void roundTripStream() {
    auto const value{fuzz<T>()};

    auto const encoder{Codec::stream()->createEncoder()};
    Viper::Codec::Writer writer{encoder};
    write(writer, value);                                      // ADL : l'unité de T

    // LE BLOB EST NOMMÉ, POUR LA MÊME RAISON QUE DANS `decode`. `createDecoder` garde une
    // référence sur ce qu'on lui donne ; un temporaire meurt à la fin de l'expression et le
    // décodeur lit dans le vide. Le défaut s'est présenté deux fois, à deux endroits, et il
    // ne se voit qu'en exécutant.
    auto const blob{encoder->endEncoding()};
    auto const decoder{Codec::stream()->createDecoder(blob)};
    Viper::Codec::Reader reader{decoder, Codec::definitions()};

    VIPER_ASSERT("Crossing.Test", read(reader, Viper::Codec::tag<T>{}) == value);
}

/// Fabriquer une Value, la décoder, la ré-encoder, comparer.
template<class T>
void roundTripValue() {
    auto const value{fuzzValue<T>()};
    auto const back{Codec::encode(Codec::decode<T>(value))};

    VIPER_ASSERT("Crossing.Test", value->equal(back));
}

/// Fabriquer, passer par JSON, comparer.
template<class T>
void roundTripJson() {
    auto const value{fuzzValue<T>()};
    auto const json{Viper::JsonValueEncoder::json_encode(value)};
    auto const back{Viper::JsonValueDecoder::json_decode(json, type(Viper::Codec::tag<T>{}),
                                                         Codec::definitions())};

    VIPER_ASSERT("Crossing.Test", value->equal(back));
}

/// Les trois d'un coup, ce qu'une unité appelle une fois par type qu'elle déclare.
template<class T>
void roundTrip() {
    roundTripStream<T>();
    roundTripValue<T>();
    roundTripJson<T>();
}

// ── et le même sur un support persistant ──
//
// LE CORPS DU PACK, MOT POUR MOT, SUR DEUX PARAMÈTRES. `TestDatabase` écrit ces quinze
// lignes une fois par attachment, et la seule chose qui y varie est la portée appelée --
// donc la clé, le document, et l'identifiant. Écrites une fois, elles ne demandent plus
// qu'une liste, comme les allers-retours de codec au-dessus.

/// Poser, relire, remplacer, effacer -- et vérifier qu'il ne reste rien.
///
/// LA LECTURE PASSE PAR L'ATTACHMENT, PAS PAR UNE COUCHE À PART. `Viper::Database` est une
/// `AttachmentGetting`, donc `keys`, `has` et `get` sont celles-là mêmes qu'en mémoire ; il
/// n'y a que l'écriture qui change, et c'est elle qui rend un statut.
template<class Key, class Document>
void roundTripAttachment(std::shared_ptr<Viper::Database> const & db,
                         std::shared_ptr<Viper::Attachment> const & attachment) {
    auto const name{"Crossing.Test"};

    VIPER_ASSERT(name, db->keys(attachment)->empty());

    auto const key{Viper::ValueKey::cast(Codec::encode(fuzz<Key>()))};
    VIPER_ASSERT(name, db->set(attachment, key, Codec::encode(fuzz<Document>())));
    VIPER_ASSERT(name, !db->get(attachment, key)->isNil());

    // remplacer : la même clé, un autre document
    VIPER_ASSERT(name, db->set(attachment, key, Codec::encode(fuzz<Document>())));
    VIPER_ASSERT(name, !db->get(attachment, key)->isNil());

    VIPER_ASSERT(name, db->del(attachment, key));
    VIPER_ASSERT(name, db->get(attachment, key)->isNil());
    VIPER_ASSERT(name, !db->del(attachment, key));      // effacer deux fois ne ment pas

    VIPER_ASSERT(name, db->keys(attachment)->empty());
}

/// En remplir un, puis tout relire. Ce que `TestDatabaseFuzz` fait, sans la répétition.
template<class Key, class Document>
void fuzzAttachment(std::shared_ptr<Viper::Database> const & db,
                    std::shared_ptr<Viper::Attachment> const & attachment, std::size_t count) {
    for (std::size_t n{}; n < count; ++n)
        db->set(attachment, Viper::ValueKey::cast(Codec::encode(fuzz<Key>())),
                Codec::encode(fuzz<Document>()));

    // RELIRE PAR LA CLÉ QU'ON A ENCODÉE, et non par celle que l'ensemble rend : le runtime
    // rend ses éléments en `const`, et `get` prend une clé mutable. Reconstruire depuis
    // l'identité est plus honnête qu'un const_cast, et c'est ce que le pack fait aussi.
    for (Viper::ValueSetIter it{db->keys(attachment)}; it.hasNext(); it.next()) {
        auto const read{Viper::ValueKey::cast(it.value())};
        Viper::Key const stored{read->instanceId, read->typeConcept->runtimeId};
        (void)db->get(attachment, stored.toKey(attachment->typeKey, db->definitions()));
    }
}

// ── ce qu'une base offre hors du modèle ──
//
// AUCUNE DE CES ÉPREUVES NE NOMME UN TYPE DU MODÈLE, et c'est pourquoi elles sont ici et
// non par unité. Le pack les écrit dans un artefact par modèle parce que tout y est par
// modèle ; une fois qu'une unité existe, la question devient « qu'est-ce qui n'est à aucune
// unité ? », et les métadonnées d'un fichier et son magasin de blobs n'y sont pas.

/// Ce que la base dit d'elle-même.
void testMetadata(std::shared_ptr<Viper::Database> const & db);

/// Créer un blob, le relire, l'effacer -- et vérifier qu'il ne reste rien.
void testBlobCreate(std::shared_ptr<Viper::Database> const & db);

/// Le même, écrit par morceaux plutôt qu'en une fois.
void testBlobStream(std::shared_ptr<Viper::Database> const & db);

/// Et relu par morceaux, à une position donnée.
void testBlobIO(std::shared_ptr<Viper::Database> const & db);

/// UN BLOB EXISTE PENDANT L'ÉPREUVE DES ATTACHMENTS, et ce n'est pas une précaution : un
/// document peut tenir un identifiant de blob, et le modèle refuse une référence vers un
/// blob absent. Le pack en crée un autour de l'épreuve pour la même raison.
std::shared_ptr<Viper::Database> withBlob(std::shared_ptr<Viper::Database> const & db);
void withoutBlob(std::shared_ptr<Viper::Database> const & db);

} // namespace Crossing::Test

#endif
