// Test — l'implémentation du pont.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Test_Codec.hpp"

#include "Test_Model.hpp"

#include "Features_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_Stream.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace Test {


void write(Viper::Codec::Writer & w, ConceptAKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

ConceptAKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptAKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, ConceptBKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

ConceptBKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptBKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, ConceptCoverageKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

ConceptCoverageKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptCoverageKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, ConceptDKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

ConceptDKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptDKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, ConceptCKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

ConceptCKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptCKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, EmptyKlubKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

EmptyKlubKey read(Viper::Codec::Reader & r, Viper::Codec::tag<EmptyKlubKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, KlubKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

KlubKey read(Viper::Codec::Reader & r, Viper::Codec::tag<KlubKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, EnumerationE value) {
    switch (value) {
        case EnumerationE::A: w.streamWriting->writeUInt8(0); break;
        case EnumerationE::B: w.streamWriting->writeUInt8(1); break;
        case EnumerationE::C: w.streamWriting->writeUInt8(2); break;
        default:
            throw Viper::TypeErrors::invalidEnumerationIndex(
                "Test", "EnumerationE", __FUNCTION__, static_cast<std::uint8_t>(value));
    }
}

EnumerationE read(Viper::Codec::Reader & r, Viper::Codec::tag<EnumerationE>) {
    switch (auto const index{r.streamReading->readUInt8()}) {
        case 0: return EnumerationE::A;
        case 1: return EnumerationE::B;
        case 2: return EnumerationE::C;
        default:
            throw Viper::TypeErrors::invalidEnumerationIndex("Test", "EnumerationE", __FUNCTION__, index);
    }
}


void write(Viper::Codec::Writer & w, StructureS const & value) {
    write(w, value.f_float);
    write(w, value.f_string);
}

StructureS read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureS>) {
    return {read(r, Viper::Codec::tag<float>{}),
            read(r, Viper::Codec::tag<std::string>{})};
}


void write(Viper::Codec::Writer & w, StructureT const & value) {
    write(w, value.field_string);
    write(w, value.field_structure_s);
}

StructureT read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureT>) {
    return {read(r, Viper::Codec::tag<std::string>{}),
            read(r, Viper::Codec::tag<StructureS>{})};
}


void write(Viper::Codec::Writer & w, StructureU const & value) {
    write(w, value.f_bool);
    write(w, value.f_uint8);
    write(w, value.f_uint16);
    write(w, value.f_uint32);
    write(w, value.f_uint64);
    write(w, value.f_int8);
    write(w, value.f_int16);
    write(w, value.f_int32);
    write(w, value.f_int64);
    write(w, value.f_float);
    write(w, value.f_double);
    write(w, value.f_blob_id);
    write(w, value.f_commit_id);
    write(w, value.f_uuid);
    write(w, value.f_string);
    write(w, value.f_blob);
    write(w, value.f_vec);
    write(w, value.f_mat);
    write(w, value.f_tuple);
    write(w, value.f_optional);
    write(w, value.f_vector);
    write(w, value.f_set);
    write(w, value.f_set_s);
    write(w, value.f_map_s1);
    write(w, value.f_map_s2);
    write(w, value.f_xarray);
    write(w, value.f_xarray_s);
    write(w, value.f_map_vs);
    write(w, value.f_variant);
    write(w, value.f_any);
    write(w, value.f_E);
    write(w, value.f_S);
    write(w, value.f_T);
    write(w, value.f_A);
    write(w, value.f_B);
    write(w, value.f_C);
    write(w, value.f_D);
    write(w, value.f_Klub);
    write(w, value.f_any_concept);
}

StructureU read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureU>) {
    return {read(r, Viper::Codec::tag<bool>{}),
            read(r, Viper::Codec::tag<std::uint8_t>{}),
            read(r, Viper::Codec::tag<std::uint16_t>{}),
            read(r, Viper::Codec::tag<std::uint32_t>{}),
            read(r, Viper::Codec::tag<std::uint64_t>{}),
            read(r, Viper::Codec::tag<std::int8_t>{}),
            read(r, Viper::Codec::tag<std::int16_t>{}),
            read(r, Viper::Codec::tag<std::int32_t>{}),
            read(r, Viper::Codec::tag<std::int64_t>{}),
            read(r, Viper::Codec::tag<float>{}),
            read(r, Viper::Codec::tag<double>{}),
            read(r, Viper::Codec::tag<Viper::BlobId>{}),
            read(r, Viper::Codec::tag<Viper::CommitId>{}),
            read(r, Viper::Codec::tag<Viper::UUId>{}),
            read(r, Viper::Codec::tag<std::string>{}),
            read(r, Viper::Codec::tag<Viper::Blob>{}),
            read(r, Viper::Codec::tag<std::array<std::uint8_t, 2>>{}),
            read(r, Viper::Codec::tag<std::array<std::array<std::uint8_t, 2>, 2>>{}),
            read(r, Viper::Codec::tag<std::tuple<std::uint8_t, std::string>>{}),
            read(r, Viper::Codec::tag<std::optional<std::uint8_t>>{}),
            read(r, Viper::Codec::tag<std::vector<std::uint8_t>>{}),
            read(r, Viper::Codec::tag<std::set<std::uint8_t>>{}),
            read(r, Viper::Codec::tag<std::set<StructureS>>{}),
            read(r, Viper::Codec::tag<std::map<StructureS, std::string>>{}),
            read(r, Viper::Codec::tag<std::map<std::string, StructureS>>{}),
            read(r, Viper::Codec::tag<Viper::XArray<std::uint8_t>>{}),
            read(r, Viper::Codec::tag<Viper::XArray<StructureS>>{}),
            read(r, Viper::Codec::tag<std::map<std::vector<StructureS>, std::string>>{}),
            read(r, Viper::Codec::tag<std::variant<std::string, std::uint8_t, StructureS>>{}),
            read(r, Viper::Codec::tag<Viper::Any>{}),
            read(r, Viper::Codec::tag<EnumerationE>{}),
            read(r, Viper::Codec::tag<StructureS>{}),
            read(r, Viper::Codec::tag<StructureT>{}),
            read(r, Viper::Codec::tag<ConceptAKey>{}),
            read(r, Viper::Codec::tag<ConceptBKey>{}),
            read(r, Viper::Codec::tag<ConceptCKey>{}),
            read(r, Viper::Codec::tag<ConceptDKey>{}),
            read(r, Viper::Codec::tag<KlubKey>{}),
            read(r, Viper::Codec::tag<::Features::AnyConceptKey>{})};
}


void write(Viper::Codec::Writer & w, StructureV const & value) {
    write(w, value.f_bool);
    write(w, value.f_uint8);
    write(w, value.f_uint16);
    write(w, value.f_uint32);
    write(w, value.f_uint64);
    write(w, value.f_int8);
    write(w, value.f_int16);
    write(w, value.f_int32);
    write(w, value.f_int64);
    write(w, value.f_float);
    write(w, value.f_double);
    write(w, value.f_uuid);
    write(w, value.f_string);
    write(w, value.f_vec);
    write(w, value.f_mat);
    write(w, value.f_tuple);
    write(w, value.f_optional);
    write(w, value.f_vector);
    write(w, value.f_set);
    write(w, value.f_map);
    write(w, value.f_E);
    write(w, value.f_S);
    write(w, value.f_T);
}

StructureV read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureV>) {
    return {read(r, Viper::Codec::tag<bool>{}),
            read(r, Viper::Codec::tag<std::uint8_t>{}),
            read(r, Viper::Codec::tag<std::uint16_t>{}),
            read(r, Viper::Codec::tag<std::uint32_t>{}),
            read(r, Viper::Codec::tag<std::uint64_t>{}),
            read(r, Viper::Codec::tag<std::int8_t>{}),
            read(r, Viper::Codec::tag<std::int16_t>{}),
            read(r, Viper::Codec::tag<std::int32_t>{}),
            read(r, Viper::Codec::tag<std::int64_t>{}),
            read(r, Viper::Codec::tag<float>{}),
            read(r, Viper::Codec::tag<double>{}),
            read(r, Viper::Codec::tag<Viper::UUId>{}),
            read(r, Viper::Codec::tag<std::string>{}),
            read(r, Viper::Codec::tag<std::array<std::uint8_t, 2>>{}),
            read(r, Viper::Codec::tag<std::array<std::array<std::uint8_t, 3>, 2>>{}),
            read(r, Viper::Codec::tag<std::tuple<std::uint8_t, std::string>>{}),
            read(r, Viper::Codec::tag<std::optional<std::uint8_t>>{}),
            read(r, Viper::Codec::tag<std::vector<std::uint8_t>>{}),
            read(r, Viper::Codec::tag<std::set<std::uint8_t>>{}),
            read(r, Viper::Codec::tag<std::map<std::uint8_t, std::string>>{}),
            read(r, Viper::Codec::tag<EnumerationE>{}),
            read(r, Viper::Codec::tag<StructureS>{}),
            read(r, Viper::Codec::tag<StructureT>{})};
}


void write(Viper::Codec::Writer & w, StructureW const & value) {
    write(w, value.f_single);
}

StructureW read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureW>) {
    return {read(r, Viper::Codec::tag<std::uint8_t>{})};
}


} // namespace Test