// unité Annotations — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Annotations_Attachments.hpp"

#include "Annotations_Codec.hpp"
#include "Annotations_Fields.hpp"
#include "Annotations_Model.hpp"
#include "ModelB_Codec.hpp"
#include "ModelA_Codec.hpp"
#include "ModelB_Model.hpp"
#include "ModelA_Model.hpp"
#include "ModelB_Fields.hpp"
#include "ModelA_Fields.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"

namespace Annotations::Attachments::ModelA_Material::note {

Viper::UUId const runtimeId{Viper::UUId::parse("a9fc61a4-cc9b-1867-2997-e3e58e3ee6c3")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Topology::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ModelA::MaterialKey const & key) {
    return Viper::ValueKey::cast(Topology::Codec::encode(key));
}

} // namespace

std::set<ModelA::MaterialKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ModelA::MaterialKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Topology::Codec::decode<ModelA::MaterialKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ModelA::MaterialKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::string> get(Viper::AttachmentGetting const & getting, ModelA::MaterialKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Topology::Codec::decode<std::string>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ModelA::MaterialKey const & key, std::string const & value) {
    mutating.set(attachment(), encodeKey(key), Topology::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ModelA::MaterialKey const & key, std::string const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Topology::Codec::encode(value), recursive);
}
} // namespace Annotations::Attachments::ModelA_Material::note

namespace Annotations::Attachments::ModelB_Material::note {

Viper::UUId const runtimeId{Viper::UUId::parse("a032a823-77a9-3b78-6d34-c83670697fd9")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Topology::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ModelB::MaterialKey const & key) {
    return Viper::ValueKey::cast(Topology::Codec::encode(key));
}

} // namespace

std::set<ModelB::MaterialKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ModelB::MaterialKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Topology::Codec::decode<ModelB::MaterialKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ModelB::MaterialKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::string> get(Viper::AttachmentGetting const & getting, ModelB::MaterialKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Topology::Codec::decode<std::string>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ModelB::MaterialKey const & key, std::string const & value) {
    mutating.set(attachment(), encodeKey(key), Topology::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ModelB::MaterialKey const & key, std::string const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Topology::Codec::encode(value), recursive);
}
} // namespace Annotations::Attachments::ModelB_Material::note