// unité Projection — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Projection_Attachments.hpp"

#include "Projection_Codec.hpp"
#include "Projection_Fields.hpp"
#include "Projection_Model.hpp"
#include "ModelB_Codec.hpp"
#include "ModelC_Codec.hpp"
#include "ModelA_Codec.hpp"
#include "ModelB_Model.hpp"
#include "ModelC_Model.hpp"
#include "ModelA_Model.hpp"
#include "ModelB_Fields.hpp"
#include "ModelC_Fields.hpp"
#include "ModelA_Fields.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"

namespace Projection::Attachments::Link::mapping {

Viper::UUId const runtimeId{Viper::UUId::parse("e44613ce-ada0-c8a2-a9d1-20b04ae443c0")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Topology::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(LinkKey const & key) {
    return Viper::ValueKey::cast(Topology::Codec::encode(key));
}

} // namespace

std::set<LinkKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<LinkKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Topology::Codec::decode<LinkKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, LinkKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::map<ModelA::MaterialKey, ModelB::MaterialKey>> get(Viper::AttachmentGetting const & getting, LinkKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Topology::Codec::decode<std::map<ModelA::MaterialKey, ModelB::MaterialKey>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value) {
    mutating.set(attachment(), encodeKey(key), Topology::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Topology::Codec::encode(value), recursive);
}
} // namespace Projection::Attachments::Link::mapping

namespace Projection::Attachments::Link::marker {

Viper::UUId const runtimeId{Viper::UUId::parse("5b7db20d-fe60-2c96-206c-ec6686b46822")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Topology::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(LinkKey const & key) {
    return Viper::ValueKey::cast(Topology::Codec::encode(key));
}

} // namespace

std::set<LinkKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<LinkKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Topology::Codec::decode<LinkKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, LinkKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<ModelC::MarkerKey> get(Viper::AttachmentGetting const & getting, LinkKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Topology::Codec::decode<ModelC::MarkerKey>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, LinkKey const & key, ModelC::MarkerKey const & value) {
    mutating.set(attachment(), encodeKey(key), Topology::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, LinkKey const & key, ModelC::MarkerKey const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Topology::Codec::encode(value), recursive);
}
} // namespace Projection::Attachments::Link::marker

namespace Projection::Attachments::Link::pair {

Viper::UUId const runtimeId{Viper::UUId::parse("2b04b57b-9677-e209-6000-91c489d81323")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Topology::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(LinkKey const & key) {
    return Viper::ValueKey::cast(Topology::Codec::encode(key));
}

} // namespace

std::set<LinkKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<LinkKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Topology::Codec::decode<LinkKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, LinkKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Pair> get(Viper::AttachmentGetting const & getting, LinkKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Topology::Codec::decode<Pair>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, LinkKey const & key, Pair const & value) {
    mutating.set(attachment(), encodeKey(key), Topology::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, LinkKey const & key, Pair const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Topology::Codec::encode(value), recursive);
}

void setA(Viper::AttachmentMutating & mutating, LinkKey const & key, ModelA::MaterialKey const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Projection::Fields::Pair::aPath(),
                    Topology::Codec::encode(value));
}

void setB(Viper::AttachmentMutating & mutating, LinkKey const & key, ModelB::MaterialKey const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Projection::Fields::Pair::bPath(),
                    Topology::Codec::encode(value));
}

} // namespace Projection::Attachments::Link::pair