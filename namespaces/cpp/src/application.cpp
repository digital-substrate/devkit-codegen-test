// Ce qu'une application écrit, et que le générateur ne produit pas.
//
// LA FRONTIÈRE EST EXACTEMENT LÀ. Le générateur déclare les fonctions d'un pool ; c'est le
// développeur qui les écrit. L'éditeur de liens le dit mieux qu'un commentaire : sur les
// 43 objets du modèle rendu, les seuls symboles qui manquaient étaient ces quatre-là, et
// l'implémentation des deux ajouts au runtime.

#include "ModelA_Data.hpp"
#include "ModelB_Data.hpp"
#include "Projection_Data.hpp"
#include "Projector_Pool.hpp"
#include "Tools_Pool.hpp"
#include "LinkModel_Pool.hpp"

#include <iostream>

namespace topology::tools {

void reset() {}

std::int64_t add(std::int64_t a, std::int64_t b) { return a + b; }

} // namespace topology::tools

namespace topology::projector {

void link(topology::model_a::MaterialKey const &, topology::model_b::MaterialKey const &) {}

} // namespace topology::projector

namespace topology::link_model {

void clear(std::shared_ptr<Viper::AttachmentMutating> const &, topology::projection::LinkKey const &) {}

} // namespace topology::link_model
