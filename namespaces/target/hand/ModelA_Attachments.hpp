// ModelA — les données accrochées à ses concepts.
//
// Couche 4 : c'est ici que le runtime apparaît dans les signatures. Un attachment est une
// donnée nommée posée sur les instances d'un concept, et les opérations dessus sont celles
// de l'unité -- ModelA déclare `attachment<Material, Colour> colour`, donc ModelA dit
// comment on le lit et comment on l'écrit.
//
// LA SURFACE EST CELLE DU RUNTIME, PAS UNE INVENTION. Viper::AttachmentMutating offre set,
// diff et update ; elle n'offre aucun remove, et le premier jet en déclarait un. Ce que le
// modèle permet de plus, c'est d'écrire un champ plutôt que le document entier -- update
// prend un chemin -- et cela donne un setter par champ du document, pas une surcharge
// générique : `setR` lie le chemin et le type ensemble, une surcharge prenant (chemin,
// valeur) laisserait les deux se contredire sans que rien ne le dise.

#ifndef ModelA_Attachments_hpp
#define ModelA_Attachments_hpp

#include "ModelA_Data.hpp"

#include "Viper_AttachmentGetting.hpp"
#include "Viper_Attachment.hpp"
#include "Viper_Database.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <cstdint>
#include <optional>
#include <set>

namespace ModelA::Attachments::Material {

/// La couleur attachée à un Material.
///
/// NOMMÉ `colour`, COMME LE MODÈLE L'ÉCRIT, ET NON `Colour`. Un scope nommé `Colour` ici
/// masquerait le type `Colour` déclaré un en-tête plus loin, et chaque signature ci-dessous
/// devrait qualifier le type de son propre namespace. Le pack évite la collision en
/// aplatissant le scope en `Material_Colour`, ce qui est le préfixe plat une fois de plus.
namespace colour {

/// L'identité de cet attachment dans le modèle.
///
/// Le pack la range dans `ModelA::AttachmentRuntimeIds::Material_Colour` -- un nom plat,
/// parce qu'une seule portée devait porter les identifiants de tous les attachments. Ici la
/// portée nomme déjà l'attachment, et il ne reste que `runtimeId`.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. Il était privé au fichier tant que seules les
/// cinq opérations s'en servaient ; l'épreuve sur base et le pont dynamique le veulent
/// aussi, et chacun le re-résoudrait depuis l'identifiant. Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<MaterialKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, MaterialKey const & key);

std::optional<Colour> get(Viper::AttachmentGetting const & getting, MaterialKey const & key);

void set(Viper::AttachmentMutating & mutating, MaterialKey const & key, Colour const & value);

void diff(Viper::AttachmentMutating & mutating, MaterialKey const & key, Colour const & value,
          bool recursive = false);

// ── un setter par champ du document ──
//
// Le document est une structure, donc chacun de ses champs est adressable seul. C'est
// l'unique consommateur des chemins de la couche 2, et la raison pour laquelle elle existe.

void setR(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value);
void setG(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value);
void setB(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.
//
// Surcharges sur le premier argument, dans la même portée : c'est le même attachment, sur
// un autre support, et le lecteur le cherche là.

bool set(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key, Colour const & value);
bool del(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key);

} // namespace colour

} // namespace ModelA::Attachments::Material

#endif
