// Crossing — les attachments du modèle, exposés au monde dynamique.
//
// LE PLUS GROS ARTEFACT DU PACK APRÈS LA BASE DE DONNÉES, ET IL N'A RIEN À GÉNÉRER. 764
// lignes de template qui produisent 9 125 lignes pour un modèle réel, et pas une seule ne
// nomme un type C++ : chaque corps caste ses arguments en `Viper::Value`, appelle
// l'interface, et rend une Value. Ce qui varie d'un attachment à l'autre est l'identifiant
// de l'attachment, les descripteurs de sa clé et de son document, et le nom de la fonction
// -- trois choses que les `Definitions` portent déjà.
//
// Donc la question « que faut-il générer ici ? » a pour réponse : rien. Il faut parcourir
// les attachments du modèle et construire le pool. C'est du code de runtime, identique pour
// tout modèle, et il est ici pour la même raison que la clé non typée : le runtime livré ne
// le porte pas encore.

#ifndef Crossing_AttachmentPool_hpp
#define Crossing_AttachmentPool_hpp

#include "Viper_AttachmentFunctionPool.hpp"

#include <memory>

namespace Crossing {

/// Le pool des attachments, construit une fois depuis le modèle.
std::shared_ptr<Viper::AttachmentFunctionPool> attachments();

} // namespace Crossing

#endif
