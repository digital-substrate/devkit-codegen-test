// ModelA — l'implémentation de l'adressage de ses champs.
//
// TROIS LIGNES PAR CHAMP, ET UNE OBSERVATION QUI VAUT LE DÉTOUR. Le chemin est construit à
// partir de la constante déclarée juste au-dessus de lui, et non d'un littéral recopié :
// le nom du champ n'apparaît qu'une fois dans toute l'unité. Le pack écrit
// `Viper::Path::makeField("r")` dans un fichier et `std::string const r{"r"}` dans un
// autre, et rien ne garantit que les deux disent la même chose.
//
// Un chemin est une propriété de la structure, pas d'une valeur : il y en a un par champ
// pour la durée du programme, donc il est construit une fois et rendu par référence.

#include "ModelA_Fields.hpp"

namespace ModelA::Fields::Colour {

std::shared_ptr<Viper::Path const> const & rPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{r})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & gPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{g})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & bPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{b})};
    return instance;
}

} // namespace ModelA::Fields::Colour
