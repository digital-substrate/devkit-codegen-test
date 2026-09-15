// unité Demo — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Demo_Model.hpp"

#include "Features_Codec.hpp"

#include "Viper_Definitions.hpp"

namespace Demo {

namespace RuntimeIds {
Viper::UUId const ConceptA{Viper::UUId::parse("bcc4e978-a438-ddba-66b9-d767b3b2649e")};
Viper::UUId const ConceptB{Viper::UUId::parse("cdb6cd9f-f1b4-03b0-dff8-b8a2092ec01c")};
Viper::UUId const ConceptCoverage{Viper::UUId::parse("28892760-a292-acbb-40ba-1aa63fc833e6")};
Viper::UUId const ConceptD{Viper::UUId::parse("edc1351f-a74f-2036-f170-e1a67570b90a")};
Viper::UUId const ConceptC{Viper::UUId::parse("ce7c9e3d-ae5f-2e57-c693-4b3e351d105b")};
Viper::UUId const EmptyKlub{Viper::UUId::parse("f1a3dba5-200b-4fb9-e8e7-a5a62af2a843")};
Viper::UUId const Klub{Viper::UUId::parse("0e64c619-6b27-330c-52ca-d2b0b6d88c0a")};
Viper::UUId const EnumerationE{Viper::UUId::parse("57233334-ee71-b77f-d6a6-b4ff25bb2350")};
Viper::UUId const StructureS{Viper::UUId::parse("c4f62cf6-2d27-05b0-018c-67d1b99df4a6")};
Viper::UUId const StructureT{Viper::UUId::parse("773ad0a2-1c7b-302e-e1b5-314ab0edb74a")};
Viper::UUId const StructureU{Viper::UUId::parse("019d066d-bd5a-19b7-4565-9c5a6f95c808")};
Viper::UUId const StructureV{Viper::UUId::parse("8b5d06ab-5a9f-d427-23b8-7ec3611aabde")};
Viper::UUId const StructureW{Viper::UUId::parse("df0e54fc-b3ac-a527-d8d7-678fc2d56d3f")};
} // namespace RuntimeIds

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptAKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkConcept(RuntimeIds::ConceptA)};
    return instance;
}

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptBKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkConcept(RuntimeIds::ConceptB)};
    return instance;
}

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptCoverageKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkConcept(RuntimeIds::ConceptCoverage)};
    return instance;
}

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptDKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkConcept(RuntimeIds::ConceptD)};
    return instance;
}

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptCKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkConcept(RuntimeIds::ConceptC)};
    return instance;
}

std::shared_ptr<Viper::Type> const & clubType(Viper::Codec::tag<EmptyKlubKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkClub(RuntimeIds::EmptyKlub)};
    return instance;
}

std::shared_ptr<Viper::Type> const & clubType(Viper::Codec::tag<KlubKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkClub(RuntimeIds::Klub)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptAKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<ConceptAKey>{}))};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptBKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<ConceptBKey>{}))};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptCoverageKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<ConceptCoverageKey>{}))};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptDKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<ConceptDKey>{}))};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptCKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<ConceptCKey>{}))};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<EmptyKlubKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(clubType(Viper::Codec::tag<EmptyKlubKey>{}))};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<KlubKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(clubType(Viper::Codec::tag<KlubKey>{}))};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<EnumerationE>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkEnumeration(RuntimeIds::EnumerationE)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureS>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkStructure(RuntimeIds::StructureS)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureT>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkStructure(RuntimeIds::StructureT)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureU>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkStructure(RuntimeIds::StructureU)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureV>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkStructure(RuntimeIds::StructureV)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureW>) {
    static std::shared_ptr<Viper::Type> const instance{
        Features::Codec::definitions()->checkStructure(RuntimeIds::StructureW)};
    return instance;
}

} // namespace Demo