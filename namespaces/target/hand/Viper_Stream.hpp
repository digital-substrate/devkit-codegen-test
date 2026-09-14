// Stubs du transport du runtime : un modèle passe par un flux binaire pour aller
// d'une valeur C++ à une Viper::Value et revenir. Signatures reprises de
// Viper_Codec.hpp, Viper_ValueEncoder.hpp et Viper_ValueDecoder.hpp.
#ifndef Viper_Stream_hpp
#define Viper_Stream_hpp
#include "Viper_Scalars.hpp"
#include "Viper_UUId.hpp"
#include "Viper_Values.hpp"
#include <cstdint>
#include <memory>
#include <string>
namespace Viper {

class Definitions;

class StreamWriting {
public:
    virtual ~StreamWriting() = default;
    virtual void writeUInt8(std::uint8_t value) = 0;
    virtual void writeFloat(float value) = 0;
    virtual void writeString(std::string const & value) = 0;
    virtual void writeUUId(UUId const & value) = 0;
};

class StreamReading {
public:
    virtual ~StreamReading() = default;
    virtual std::uint8_t readUInt8() = 0;
    virtual float readFloat() = 0;
    virtual std::string readString() = 0;
    virtual UUId readUUId() = 0;
};

class StreamEncoder : public StreamWriting { public: Blob endEncoding(); };
class StreamDecoder : public StreamReading {};

class StreamCodecInstancing {
public:
    std::shared_ptr<StreamEncoder> createEncoder() const;
    std::shared_ptr<StreamDecoder> createDecoder(Blob const & blob) const;
};

namespace Codec {
static std::string const StreamBinary{"StreamBinary"};
std::shared_ptr<StreamCodecInstancing> check(std::string const & name);
}

namespace ValueEncoder {
Blob encode(std::shared_ptr<Value const> const & value,
            std::shared_ptr<StreamCodecInstancing> const & instancing);
}

namespace ValueDecoder {
std::shared_ptr<Value> decode(Blob const & blob,
                              std::shared_ptr<StreamCodecInstancing> const & instancing,
                              std::shared_ptr<Type> const & type,
                              std::shared_ptr<Definitions const> const & definitions);
}

} // ns
#endif
