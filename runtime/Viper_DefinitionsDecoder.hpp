// Le modèle arrive en octets et se décode en Definitions. C'est ce qui remplace, du côté
// généré, tout enregistrement de types : le .dsm est embarqué tel quel.
#ifndef Viper_DefinitionsDecoder_hpp
#define Viper_DefinitionsDecoder_hpp
#include "Viper_Stream.hpp"
#include <memory>
namespace Viper {
class Definitions;
namespace DefinitionsDecoder {
std::shared_ptr<Definitions const> decode(Blob const & blob,
                                          std::shared_ptr<StreamCodecInstancing> const & instancing);
}
class StreamBinaryCodec { public: static std::shared_ptr<StreamCodecInstancing> Instance(); };
class StreamTokenBinaryCodec { public: static std::shared_ptr<StreamCodecInstancing> Instance(); };
}
#endif
