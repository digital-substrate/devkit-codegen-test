// unité ModelB — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelB_Attachments.hpp"

#include "ModelB_Codec.hpp"
#include "ModelB_Fields.hpp"
#include "ModelB_Model.hpp"

#include "Topology_Codec.hpp"
#include "Topology_Db.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"
#include "Viper_ValueSetIter.hpp"

namespace ModelB::Attachments::Material::colour {

Viper::UUId const runtimeId{Viper::UUId::parse("09eeb3f7-b0a6-9ad9-a80f-d2a85070ec08")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Topology::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

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

bool set(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key, Colour const & value) {
    return Topology::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key) {
    return Topology::Db::del(db, attachment(), key);
}

void setR(Viper::AttachmentMutating & mutating, MaterialKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), ModelB::Fields::Colour::rPath(),
                    Topology::Codec::encode(value));
}


void setG(Viper::AttachmentMutating & mutating, MaterialKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), ModelB::Fields::Colour::gPath(),
                    Topology::Codec::encode(value));
}


void setB(Viper::AttachmentMutating & mutating, MaterialKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), ModelB::Fields::Colour::bPath(),
                    Topology::Codec::encode(value));
}

} // namespace ModelB::Attachments::Material::colour