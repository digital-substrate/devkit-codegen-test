// ModelA — l'épreuve de ses types.
//
// LE CORPS EST LA LISTE, ET RIEN D'AUTRE. Un aller-retour par type déclaré, et l'aller-
// retour est celui du socle : fabriquer, traverser les trois codecs, comparer. Le pack
// écrit ici sept fonctions par type, une par artefact de test, dont seul le suffixe varie.
//
// ET AUCUN CONTENEUR N'A DE LIGNE. Un std::set<Colour> se fabrique par le descripteur de
// type de l'ensemble, que le runtime compose depuis celui de Colour -- donc le fuzz d'un
// conteneur ne demande rien à l'unité qui possède l'élément. La forme qui traverse deux
// unités ne demande rien non plus.

#include "ModelA_Test.hpp"

#include "ModelA_Codec.hpp"        // write, read
#include "ModelA_Attachments.hpp"   // runtimeId
#include "ModelA_Database.hpp"
#include "ModelA_Model.hpp"        // type -- le descripteur dont le fuzz part

#include "Topology_Test.hpp"       // les allers-retours génériques

namespace ModelA {

void test() {
    Topology::Test::roundTrip<MaterialKey>();
    Topology::Test::roundTrip<Finish>();
    Topology::Test::roundTrip<Colour>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Topology::Test::roundTripAttachment<MaterialKey, Colour>(
        db, Attachments::Material::colour::runtimeId);
}

} // namespace ModelA
