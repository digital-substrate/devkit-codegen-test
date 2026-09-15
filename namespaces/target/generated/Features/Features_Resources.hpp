// Le modèle, en octets.
//
// LE .DSM EMBARQUÉ TEL QUEL, et c'est la découverte du jour : le pack ne génère aucun code
// d'enregistrement de types. Il embarque le document et le décode au chargement. Il n'y a
// donc pas d'artefact d'enregistrement à découper par namespace -- et la liste des concepts
// connus, celle que `isKnown` interroge, est cette donnée-là.
#ifndef Features_Resources_hpp
#define Features_Resources_hpp
#include <cstddef>
namespace Features::Resources {
/// Le document, octet par octet. Ici réduit à rien : la référence se compile, elle ne
/// s'exécute pas, et ce qui compte est la forme -- une donnée, pas du code.
inline constexpr unsigned char definitions[]{0};
}
#endif
