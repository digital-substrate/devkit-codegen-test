// unité ModelA — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelA_Attachments.hpp"

#include "ModelA_Codec.hpp"
#include "ModelA_Fields.hpp"
#include "ModelA_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"

namespace ModelA::Attachments::Material::colour {

Viper::UUId const runtimeId{Viper::UUId::parse("faf658ea-5586-890a-0c4a-5cd2c9209b28")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Topology::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
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

void setR(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    ModelA::Fields::Colour::rPath(),
                    Topology::Codec::encode(value));
}

void setG(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    ModelA::Fields::Colour::gPath(),
                    Topology::Codec::encode(value));
}

void setB(Viper::AttachmentMutating & mutating, MaterialKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    ModelA::Fields::Colour::bPath(),
                    Topology::Codec::encode(value));
}

} // namespace ModelA::Attachments::Material::colour