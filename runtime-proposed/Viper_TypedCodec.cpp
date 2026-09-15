// Le côté typé du codec : une valeur C++ sur le flux, et retour.
//
// CHAQUE LIGNE EST UN APPEL DU RUNTIME, et le format vient de `Viper_ValueWriter.cpp`. Ce
// que ces fonctions posent doit être exactement ce que le ValueWriter pose pour la Value
// correspondante -- c'est ce qui rend le pont statique/dynamique possible, et c'est la seule
// chose qu'il faut vérifier dans ce fichier.

#include "Viper_TypedCodec.hpp"

#include "Viper_StreamReading.hpp"
#include "Viper_StreamWriting.hpp"
#include "Viper_TypeAnyConcept.hpp"
#include "Viper_TypeAny.hpp"
#include "Viper_Types.hpp"
#include "Viper_ValueReader.hpp"
#include "Viper_ValueWriter.hpp"
#include "Viper_Values.hpp"

namespace Viper::Codec {

Writer::Writer(std::shared_ptr<StreamWriting> streamWriting)
: streamWriting{std::move(streamWriting)} {}

Reader::Reader(std::shared_ptr<StreamReading> streamReading,
               std::shared_ptr<Definitions const> definitions)
: streamReading{std::move(streamReading)}, definitions{std::move(definitions)} {}

void write(Writer & w, bool value) { w.streamWriting->writeBool(value); }
void write(Writer & w, std::uint8_t value) { w.streamWriting->writeUInt8(value); }
void write(Writer & w, std::uint16_t value) { w.streamWriting->writeUInt16(value); }
void write(Writer & w, std::uint32_t value) { w.streamWriting->writeUInt32(value); }
void write(Writer & w, std::uint64_t value) { w.streamWriting->writeUInt64(value); }
void write(Writer & w, std::int8_t value) { w.streamWriting->writeInt8(value); }
void write(Writer & w, std::int16_t value) { w.streamWriting->writeInt16(value); }
void write(Writer & w, std::int32_t value) { w.streamWriting->writeInt32(value); }
void write(Writer & w, std::int64_t value) { w.streamWriting->writeInt64(value); }
void write(Writer & w, float value) { w.streamWriting->writeFloat(value); }
void write(Writer & w, double value) { w.streamWriting->writeDouble(value); }
void write(Writer & w, std::string const & value) { w.streamWriting->writeString(value); }
void write(Writer & w, UUId const & value) { w.streamWriting->writeUUId(value); }
void write(Writer & w, BlobId const & value) { w.streamWriting->writeBlobId(value); }
void write(Writer & w, CommitId const & value) { w.streamWriting->writeCommitId(value); }
void write(Writer & w, Blob const & value) { w.streamWriting->writeBlob(value); }

/// UN `any` PORTE SA PROPRE VALUE, DONC IL PASSE PAR LE CODEC NON TYPÉ. C'est le seul type
/// dont la forme n'est pas connue à l'écriture : le runtime écrit son type puis son
/// contenu, et c'est exactement ce que `ValueWriter` fait. Le pack écrit la même ligne.
void write(Writer & w, Any const & value) { ValueWriter::write(value.value(), w.streamWriting); }

bool          read(Reader & r, tag<bool>) { return r.streamReading->readBool(); }
std::uint8_t  read(Reader & r, tag<std::uint8_t>) { return r.streamReading->readUInt8(); }
std::uint16_t read(Reader & r, tag<std::uint16_t>) { return r.streamReading->readUInt16(); }
std::uint32_t read(Reader & r, tag<std::uint32_t>) { return r.streamReading->readUInt32(); }
std::uint64_t read(Reader & r, tag<std::uint64_t>) { return r.streamReading->readUInt64(); }
std::int8_t   read(Reader & r, tag<std::int8_t>) { return r.streamReading->readInt8(); }
std::int16_t  read(Reader & r, tag<std::int16_t>) { return r.streamReading->readInt16(); }
std::int32_t  read(Reader & r, tag<std::int32_t>) { return r.streamReading->readInt32(); }
std::int64_t  read(Reader & r, tag<std::int64_t>) { return r.streamReading->readInt64(); }
float         read(Reader & r, tag<float>) { return r.streamReading->readFloat(); }
double        read(Reader & r, tag<double>) { return r.streamReading->readDouble(); }
std::string   read(Reader & r, tag<std::string>) { return r.streamReading->readString(); }
UUId          read(Reader & r, tag<UUId>) { return r.streamReading->readUUId(); }
BlobId        read(Reader & r, tag<BlobId>) { return r.streamReading->readBlobId(); }
CommitId      read(Reader & r, tag<CommitId>) { return r.streamReading->readCommitId(); }
Blob          read(Reader & r, tag<Blob>) { return r.streamReading->readBlob(); }

Any read(Reader & r, tag<Any>) {
    return Any{ValueAny::cast(ValueReader::read(TypeAny::Instance(), r.streamReading, r.definitions))};
}

} // namespace Viper::Codec
