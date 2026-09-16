// ModelA — ce qu'il faut savoir de ModelA pour l'éprouver.
//
// UNE LIGNE, ET C'EST LA CORRECTION QUE CE FICHIER PORTE. Le premier jet déclarait ici un
// `fuzz` par type déclaré, en supposant qu'une unité seule sait fabriquer un de ses types.
// Elle ne le sait pas mieux que le runtime, qui part du descripteur de type -- et ce
// descripteur, l'unité le fournit déjà dans son identité de modèle.
//
// Il ne reste donc à une unité qu'une chose que personne d'autre ne sait : la liste de ce
// qu'elle déclare.

#ifndef ModelA_Test_hpp
#define ModelA_Test_hpp

#include "Viper_Database.hpp"

#include <cstddef>
#include <memory>

namespace ModelA {

/// Éprouver chaque type déclaré ici, par chaque codec.
void test();

/// Éprouver chaque attachment déclaré ici, sur une base de données.
///
/// SÉPARÉ DE `test()` PARCE QU'IL DEMANDE QUELQUE CHOSE. Les codecs n'ont besoin de rien
/// que le modèle ne porte ; une base est un support qu'il faut ouvrir, et l'appelant décide
/// lequel.
void testDatabase(std::shared_ptr<Viper::Database> const & db);

/// Remplir chaque attachment déclaré ici, puis tout relire.
///
/// SÉPARÉ DE `testDatabase` PARCE QU'IL NE VÉRIFIE PAS LA MÊME CHOSE. L'aller-retour dit
/// qu'une écriture se relit ; celui-ci dit que mille tiennent, et il n'assert rien d'autre
/// que l'absence de casse.
void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count);

} // namespace ModelA

#endif
