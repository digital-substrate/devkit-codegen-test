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

namespace ModelA {

/// Éprouver chaque type déclaré ici, par chaque codec.
void test();

} // namespace ModelA

#endif
