// Projection — ce qu'il faut savoir de Projection pour l'éprouver.
//
// UNE LIGNE, ET C'EST LA CORRECTION QUE CE FICHIER PORTE. Le premier jet déclarait ici un
// `fuzz` par type déclaré, en supposant qu'une unité seule sait fabriquer un de ses types.
// Elle ne le sait pas mieux que le runtime, qui part du descripteur de type -- et ce
// descripteur, l'unité le fournit déjà dans son identité de modèle.
//
// Il ne reste donc à une unité qu'une chose que personne d'autre ne sait : la liste de ce
// qu'elle déclare.

#ifndef Projection_Test_hpp
#define Projection_Test_hpp

#include "Viper_Database.hpp"

#include <memory>

namespace Projection {

/// Éprouver chaque type déclaré ici, par chaque codec.
void test();

/// Éprouver chaque attachment déclaré ici, sur une base de données.
///
/// SÉPARÉ DE `test()` PARCE QU'IL DEMANDE QUELQUE CHOSE. Les codecs n'ont besoin de rien
/// que le modèle ne porte ; une base est un support qu'il faut ouvrir, et l'appelant décide
/// lequel.
void testDatabase(std::shared_ptr<Viper::Database> const & db);

} // namespace Projection

#endif
