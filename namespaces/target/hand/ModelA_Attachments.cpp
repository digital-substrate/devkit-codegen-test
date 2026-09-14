// ModelA — l'implémentation des attachments qu'il déclare.
//
// C'EST LE FICHIER QUI DÉPARTAGE LES TROIS MODULES, parce que c'est le premier où ils
// apparaissent tous les trois dans le même corps de fonction :
//
//   ModelA::            ce que l'unité implémente -- write, read, type pour ses types
//   Topology::Codec::   ce que kibo injecte -- encode, decode, definitions()
//   Viper::             le runtime -- l'attachment, les valeurs, les interfaces
//
// Et il tient en quarante lignes, ce qui est le résultat. Le pack écrit ici, par
// attachment, des appels à ValueEncoder::encode_ModelA_MaterialKey et
// ValueDecoder::decode_ModelA_Colour : des noms plats qui existaient parce que rien ne
// permettait de résoudre `encode(key)` autrement que par le nom. Avec le namespace comme
// élément structurant, encode est une fonction template unique et c'est l'argument qui
// dit dans quelle unité aller la chercher.

#include "ModelA_Attachments.hpp"

#include "ModelA_Codec.hpp"        // write, read, type -- ce que ModelA implémente
#include "ModelA_Fields.hpp"       // les chemins, pour les setters de champ

#include "Topology_Codec.hpp"      // encode, decode, definitions() -- le module injecté

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"

namespace ModelA::Attachments::Material::colour {

Viper::UUId const runtimeId{0x7f3c4d0e1a2b5c6d, 0x8e9f0a1b2c3d4e5f};

namespace {

/// L'attachment tel que le runtime le connaît.
///
/// Résolu une fois : `definitions()` est le modèle entier, enregistré au chargement, donc
/// le descripteur ne change pas d'un appel à l'autre. Il est privé au fichier -- personne
/// hors de ce scope n'a de raison de le nommer.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Topology::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Trois lignes se la partagent, et le cast dit ce que le modèle sait
/// déjà : la clé d'un attachment est une clé.
std::shared_ptr<Viper::ValueKey> encodeKey(MaterialKey const & key) {
    return Viper::ValueKey::cast(Topology::Codec::encode(key));
}

} // namespace

std::set<MaterialKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<MaterialKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Topology::Codec::decode<MaterialKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, MaterialKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Colour> get(Viper::AttachmentGetting const & getting, MaterialKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Topology::Codec::decode<Colour>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, MaterialKey const & key, Colour const & value) {
    mutating.set(attachment(), encodeKey(key), Topology::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, MaterialKey const & key, Colour const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Topology::Codec::encode(value), recursive);
}

// ── les setters de champ ──
//
// LA COUCHE 2 SERT ICI, ET NULLE PART AILLEURS. `update` prend un chemin et une valeur
// encodée ; le chemin vient de Fields, la valeur du module injecté, et le type du champ
// vient de la signature. Les trois lignes sont identiques au nom du champ près -- ce qui
// est la forme qu'un template reproduit sans rien inventer.

void setR(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Fields::Colour::rPath(), Topology::Codec::encode(value));
}

void setG(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Fields::Colour::gPath(), Topology::Codec::encode(value));
}

void setB(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Fields::Colour::bPath(), Topology::Codec::encode(value));
}

} // namespace ModelA::Attachments::Material::colour
