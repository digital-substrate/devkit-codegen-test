// ModelC — ce qu'il faut savoir de ModelC pour l'éprouver.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef ModelC_Test_hpp
#define ModelC_Test_hpp

#include "Viper_Database.hpp"

#include <memory>

namespace ModelC {

/// Éprouver chaque type déclaré ici, par chaque codec.
void test();

/// Éprouver chaque attachment déclaré ici, sur une base de données.
///
/// SÉPARÉ DE `test()` PARCE QU'IL DEMANDE QUELQUE CHOSE. Les codecs n'ont besoin de rien que
/// le modèle ne porte ; une base est un support qu'il faut ouvrir, et l'appelant décide
/// lequel.
void testDatabase(std::shared_ptr<Viper::Database> const & db);

} // namespace ModelC

#endif