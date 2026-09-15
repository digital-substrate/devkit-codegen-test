// unité Projection — ce qu'il faut en savoir pour l'éprouver.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef Projection_Test_hpp
#define Projection_Test_hpp

#include "Viper_Database.hpp"

#include <cstddef>
#include <memory>

namespace Projection {

/// Éprouver chaque type déclaré ici, par chaque codec.
void test();

/// Éprouver chaque attachment déclaré ici, sur une base de données.
///
/// SÉPARÉ DE `test()` PARCE QU'IL DEMANDE QUELQUE CHOSE. Les codecs n'ont besoin de rien que
/// le modèle ne porte ; une base est un support qu'il faut ouvrir, et l'appelant décide
/// lequel.
void testDatabase(std::shared_ptr<Viper::Database> const & db);

/// Remplir chaque attachment déclaré ici, puis tout relire.
///
/// SÉPARÉ PARCE QU'IL NE VÉRIFIE PAS LA MÊME CHOSE. L'aller-retour dit qu'une écriture se
/// relit ; celui-ci dit que mille tiennent, et il n'assert rien d'autre que l'absence de
/// casse.
void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count);

} // namespace Projection

#endif