// unité Core — ce qui manquait : modifier un agrégat sans l'écraser.
//
// LES CINQ AUTRES OPÉRATIONS SONT AILLEURS. `keys`, `has`, `get`, `set`, `diff` et le
// setter par champ scalaire sont déjà écrites et rendues ; ce fichier n'ajoute que les
// huit qui touchent un agrégat, parce que ce sont les seules qui manquaient.
//
// POURQUOI ELLES NE SONT PAS UN CONFORT. `set` remplace le document entier, `update`
// remplace ce qui est à une adresse. Celles-ci ajoutent, retirent ou déplacent à
// l'intérieur -- et deux écritures concurrentes sur le même ensemble se fondent là où deux
// remplacements s'écrasent. C'est la différence entre « voici l'ensemble » et « ajoute
// ceci », et elle ne se rattrape pas après coup.
//
// DEUX NIVEAUX, UNE SEULE FORME. Quand le document EST un agrégat, l'adresse est la racine ;
// quand c'est un champ du document, l'adresse est celle du champ. Rien d'autre ne change.

#ifndef Core_Attachments_hpp
#define Core_Attachments_hpp

#include "Core_Data.hpp"

#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <map>
#include <set>

namespace Core::Attachments::Thing {

// ── le document est un ensemble ──

namespace related {

extern Viper::UUId const runtimeId;

/// Ajouter à l'ensemble. `union_` et non `union`, qui est un mot du langage.
void union_(Viper::AttachmentMutating & mutating, ThingKey const & key,
            std::set<ThingKey> const & value);

void subtract(Viper::AttachmentMutating & mutating, ThingKey const & key,
              std::set<ThingKey> const & value);

} // namespace related

// ── le document est une map ──

namespace palette {

extern Viper::UUId const runtimeId;

void union_(Viper::AttachmentMutating & mutating, ThingKey const & key,
            std::map<ThingKey, Colour> const & value);

/// RETIRER D'UNE MAP, C'EST RETIRER DES CLÉS. L'argument est un ensemble de clés et non une
/// map : demander les valeurs pour effacer laisserait croire qu'elles comptent.
void subtract(Viper::AttachmentMutating & mutating, ThingKey const & key,
              std::set<ThingKey> const & value);

void update(Viper::AttachmentMutating & mutating, ThingKey const & key,
            std::map<ThingKey, Colour> const & value);

} // namespace palette

// ── le document est un xarray ──

namespace history {

extern Viper::UUId const runtimeId;

/// Insérer avant une position, à une position neuve. Aucune des trois ne se dit avec un
/// index : un xarray a des positions stables, c'est toute sa raison d'être.
void insert(Viper::AttachmentMutating & mutating, ThingKey const & key,
            Viper::UUId const & beforePosition, Viper::UUId const & newPosition,
            Colour const & value);

void update(Viper::AttachmentMutating & mutating, ThingKey const & key,
            Viper::UUId const & position, Colour const & value);

void remove(Viper::AttachmentMutating & mutating, ThingKey const & key,
            Viper::UUId const & position);

} // namespace history

// ── et les mêmes, sur les champs d'un document ordinaire ──
//
// LE NOM PORTE LE CHAMP, ET IL LE DOIT. Un document peut avoir plusieurs champs agrégés, et
// `union_` ne dirait pas lequel. C'est le même aplatissement qu'ailleurs, et ici il est
// contraint : une portée par champ mettrait quatre niveaux sous l'attachment.

namespace bag {

extern Viper::UUId const runtimeId;

void unionMembers(Viper::AttachmentMutating & mutating, ThingKey const & key,
                  std::set<ThingKey> const & value);
void subtractMembers(Viper::AttachmentMutating & mutating, ThingKey const & key,
                     std::set<ThingKey> const & value);

void unionTints(Viper::AttachmentMutating & mutating, ThingKey const & key,
                std::map<ThingKey, Colour> const & value);
void subtractTints(Viper::AttachmentMutating & mutating, ThingKey const & key,
                   std::set<ThingKey> const & value);
void updateTints(Viper::AttachmentMutating & mutating, ThingKey const & key,
                 std::map<ThingKey, Colour> const & value);

void insertTrail(Viper::AttachmentMutating & mutating, ThingKey const & key,
                 Viper::UUId const & beforePosition, Viper::UUId const & newPosition,
                 Colour const & value);
void updateTrail(Viper::AttachmentMutating & mutating, ThingKey const & key,
                 Viper::UUId const & position, Colour const & value);
void removeTrail(Viper::AttachmentMutating & mutating, ThingKey const & key,
                 Viper::UUId const & position);

} // namespace bag

} // namespace Core::Attachments::Thing

#endif
