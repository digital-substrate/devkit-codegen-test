// Test — everything its types need in order to cross into the runtime.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar
//
// Deux déclarations par type, et c'est toute la part d'un namespace dans le pont.
// Le descripteur de type, qui était ici, est passé dans son identité de modèle : la couche
// des types en a besoin aussi, et elle ne sérialise rien. Encoding to a Value, to JSON, and hashing are compositions of the two below,
// and every container is the runtime's -- ModelA owns Material, not std::set.

#ifndef Test_Codec_hpp
#define Test_Codec_hpp

#include "Test_Data.hpp"

#include "Viper_Codec.hpp"

#include <memory>

namespace Test {

void write(Viper::Codec::Writer & w, ConceptAKey const & value);
ConceptAKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptAKey>);

void write(Viper::Codec::Writer & w, ConceptBKey const & value);
ConceptBKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptBKey>);

void write(Viper::Codec::Writer & w, ConceptCoverageKey const & value);
ConceptCoverageKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptCoverageKey>);

void write(Viper::Codec::Writer & w, ConceptDKey const & value);
ConceptDKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptDKey>);

void write(Viper::Codec::Writer & w, ConceptCKey const & value);
ConceptCKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ConceptCKey>);

void write(Viper::Codec::Writer & w, EmptyKlubKey const & value);
EmptyKlubKey read(Viper::Codec::Reader & r, Viper::Codec::tag<EmptyKlubKey>);

void write(Viper::Codec::Writer & w, KlubKey const & value);
KlubKey read(Viper::Codec::Reader & r, Viper::Codec::tag<KlubKey>);

void write(Viper::Codec::Writer & w, EnumerationE value);
EnumerationE read(Viper::Codec::Reader & r, Viper::Codec::tag<EnumerationE>);

void write(Viper::Codec::Writer & w, StructureS const & value);
StructureS read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureS>);

void write(Viper::Codec::Writer & w, StructureT const & value);
StructureT read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureT>);

void write(Viper::Codec::Writer & w, StructureU const & value);
StructureU read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureU>);

void write(Viper::Codec::Writer & w, StructureV const & value);
StructureV read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureV>);

void write(Viper::Codec::Writer & w, StructureW const & value);
StructureW read(Viper::Codec::Reader & r, Viper::Codec::tag<StructureW>);

} // namespace Test

#endif