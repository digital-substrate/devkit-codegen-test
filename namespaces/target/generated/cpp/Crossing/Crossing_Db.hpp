// modèle Crossing — les deux opérations qu'une base ajoute à un attachment.
//
// DEUX, ET NON CINQ. C'est ce que le vrai en-tête du runtime dit et que j'avais inventé
// autrement : `Viper::Database` **est** une `AttachmentGetting`. Ses `keys`, `has` et `get`
// sont les mêmes fonctions virtuelles que celles d'un attachment en mémoire, donc les
// opérations de lecture d'une unité marchent déjà sur une base sans qu'on écrive rien.
//
// Ce qu'une base ajoute, c'est d'écrire en rendant un statut -- `set` et `del` rendent un
// booléen là où l'interface mutante ne rend rien, parce qu'un enregistrement peut échouer
// et qu'un changement en mémoire non.
//
// J'AVAIS ÉCRIT CINQ TEMPLATES SUR UN IDENTIFIANT D'ATTACHMENT. Le runtime prend un
// descripteur, comme partout ailleurs, et les anciens templates le montraient ligne pour
// ligne. C'est la moitié de cette couche qui disparaît pour avoir lu ce qui existait.

#ifndef Crossing_Db_hpp
#define Crossing_Db_hpp

#include "Crossing_Codec.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Database.hpp"
#include "Viper_Values.hpp"

#include <memory>

namespace Crossing::Db {

/// Écrire le document, et dire si la base l'a pris.
template<class Document, class Key>
bool set(std::shared_ptr<Viper::Database> const & db,
         std::shared_ptr<Viper::Attachment> const & attachment,
         Key const & key, Document const & document) {
    return db->set(attachment,
                   Viper::ValueKey::cast(Codec::encode(key)),
                   Codec::encode(document));
}

template<class Key>
bool del(std::shared_ptr<Viper::Database> const & db,
         std::shared_ptr<Viper::Attachment> const & attachment, Key const & key) {
    return db->del(attachment, Viper::ValueKey::cast(Codec::encode(key)));
}

} // namespace Crossing::Db

#endif
