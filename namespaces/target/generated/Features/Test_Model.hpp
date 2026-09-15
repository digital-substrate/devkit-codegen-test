// Test — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#ifndef Test_Model_hpp
#define Test_Model_hpp

#include "Test_Data.hpp"

#include "Viper_Codec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace Test {

/// L'identité de chaque type déclaré ici.
namespace RuntimeIds {
extern Viper::UUId const ConceptA;
extern Viper::UUId const ConceptB;
extern Viper::UUId const ConceptCoverage;
extern Viper::UUId const ConceptD;
extern Viper::UUId const ConceptC;
extern Viper::UUId const EmptyKlub;
extern Viper::UUId const Klub;
extern Viper::UUId const EnumerationE;
extern Viper::UUId const StructureS;
extern Viper::UUId const StructureT;
extern Viper::UUId const StructureU;
extern Viper::UUId const StructureV;
extern Viper::UUId const StructureW;
} // namespace RuntimeIds

/// Le concept dont une clé relève -- ce qu'un rétrécissement compare.
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptAKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptBKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptCoverageKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptDKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ConceptCKey>);

/// Le club dont une clé relève. Distinct du précédent : une adhésion n'est pas un
/// héritage, et c'est le descripteur qui porte la différence, pas le code.
std::shared_ptr<Viper::Type> const & clubType(Viper::Codec::tag<EmptyKlubKey>);
std::shared_ptr<Viper::Type> const & clubType(Viper::Codec::tag<KlubKey>);

/// Le type lui-même, tel que le runtime le manipule -- ce que le codec générique demande.
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptAKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptBKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptCoverageKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptDKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ConceptCKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<EmptyKlubKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<KlubKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<EnumerationE>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureS>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureT>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureU>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureV>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<StructureW>);

} // namespace Test

#endif