// La base de données du runtime.
//
// LA CLASSE GÉNÉRÉE N'AJOUTE RIEN À CELLE-CI. Sur les 1 638 lignes que le pack émet pour la
// base de données, le modèle n'apparaît qu'à quatre endroits, tous dans l'implémentation
// SQLite : deux fois pour écrire les définitions du modèle dans une base neuve, deux fois
// pour vérifier qu'une base ouverte les contient. C'est un argument, pas un type.
//
// ET LE TYPE PAR MODÈLE COÛTE QUELQUE CHOSE. Deux modèles dans un même programme ont deux
// classes `Database` incompatibles sur le même fichier. Avec une seule classe et les
// définitions en paramètre, il y a une poignée, et chaque modèle l'étend des siennes --
// ce que `extendDefinitions` fait déjà.
#ifndef Viper_Database_hpp
#define Viper_Database_hpp
#include "Viper_Definitions.hpp"
#include "Viper_Scalars.hpp"
#include <cstddef>
#include "Viper_Stream.hpp"
#include "Viper_UUId.hpp"
#include <filesystem>
#include <memory>
#include <optional>
#include <set>
#include <string>
namespace Viper {

enum class DatabaseTransactionMode { Deferred, Immediate, Exclusive };

class BlobLayout final {
public:
    std::string representation() const;
};

class BlobStream final {};

struct BlobInfo {
    BlobId blobId;
    BlobLayout blobLayout;
    std::size_t size;
};

/// Une clé, telle que le stockage la connaît : sans type C++, comme tout ce qui est stocké.
struct Key {
    UUId instanceId;
    UUId runtimeId;
    bool operator<(Key const & o) const { return instanceId < o.instanceId; }
};

class Database final {
public:
    // Les définitions du modèle sont un argument : elles sont écrites dans une base neuve
    // et vérifiées sur une base ouverte, et c'est tout ce que le modèle apporte ici.
    static std::shared_ptr<Database> createInMemory(std::shared_ptr<Definitions const> const & definitions);
    static std::shared_ptr<Database> create(std::filesystem::path const & path,
                                            std::string const & documentation,
                                            std::shared_ptr<Definitions const> const & definitions);
    static std::shared_ptr<Database> open(std::filesystem::path const & path,
                                          std::shared_ptr<Definitions const> const & definitions,
                                          bool readonly = false);
    static std::shared_ptr<Database> connect(std::string const & database,
                                             std::filesystem::path const & socketPath,
                                             std::shared_ptr<Definitions const> const & definitions);

    void close();
    bool isClosed() const;

    void beginTransaction(DatabaseTransactionMode mode);
    void commit();
    void rollback();

    std::shared_ptr<StreamCodecInstancing> streamCodecInstancing() const;
    std::shared_ptr<Definitions const> definitions() const;
    Definitions::ExtendInfo extendDefinitions(std::shared_ptr<Definitions const> const & definitions);

    // MARK: - Blobs
    //
    // UNE DONNÉE BRUTE, HORS DU SYSTÈME DE TYPES. Un blob n'est pas une valeur du modèle :
    // c'est une suite d'octets que la base range et à laquelle une valeur peut se référer
    // par son identifiant. Aucun namespace ne la nomme, donc rien n'est généré pour elle --
    // et c'est pourquoi tout ce bloc est du runtime.
    std::set<BlobId> blobIds() const;
    std::optional<BlobInfo> blobInfo(BlobId const & blobId) const;
    std::optional<Blob> blob(BlobId const & blobId) const;

    BlobId createBlob(BlobLayout const & layout, Blob const & data);
    bool delBlob(BlobId const & blobId);

    /// Écrire un blob par morceaux, sans le tenir entier en mémoire.
    BlobStream blobStreamCreate(BlobLayout const & layout, std::size_t size);
    void blobStreamAppend(BlobStream const & stream, std::byte const * data, std::size_t size);
    BlobId blobStreamClose(BlobStream const & stream);

    /// Et le lire par morceaux, à une position donnée.
    bool createZeroBlob(BlobId const & blobId, BlobLayout const & layout, std::size_t size);
    void writeBlob(BlobId const & blobId, std::byte const * data, std::size_t size, std::size_t offset);
    void readBlob(BlobId const & blobId, std::byte * data, std::size_t size, std::size_t offset) const;
    void freezeBlob(BlobId const & blobId);

    // MARK: - Métadonnées
    std::filesystem::path path() const;
    UUId uuid() const;
    std::string documentation() const;
    std::string codecName() const;

    // MARK: - Attachments, sans type
    std::set<Key> keys(UUId const & attachmentRuntimeId) const;
    bool has(UUId const & attachmentRuntimeId, Key const & key) const;
    std::optional<Blob> get(UUId const & attachmentRuntimeId, Key const & key) const;
    bool set(UUId const & attachmentRuntimeId, Key const & key, Blob const & document);
    bool del(UUId const & attachmentRuntimeId, Key const & key);
};

} // ns
#endif
