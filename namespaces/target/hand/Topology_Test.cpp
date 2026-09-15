#include "Topology_Test.hpp"

#include "Viper_Databasing.hpp"
#include "Viper_BlobId.hpp"
#include "Viper_BlobInfo.hpp"
#include "Viper_BlobLayout.hpp"

#include <cstdint>
#include <vector>
#include <iostream>
#include <optional>

namespace Topology::Test {

namespace {
std::optional<std::uint64_t> g_seed;
std::shared_ptr<Viper::Fuzzer> g_fuzzer;
}

void seed(std::uint64_t value) {
    g_seed = value;
    g_fuzzer.reset();
}

std::shared_ptr<Viper::Fuzzer> const & fuzzer() {
    if (!g_fuzzer) {
        g_fuzzer = g_seed ? Viper::Fuzzer::make(Codec::definitions(), *g_seed)
                          : Viper::Fuzzer::make(Codec::definitions());

        // L'IDENTIFIANT DE BLOB EST ÉPINGLÉ, ET IL LE DOIT. Un document peut tenir un
        // `blob_id`, et la base refuse une référence vers un blob absent -- un identifiant
        // tiré au hasard n'en désigne aucun. Épinglé sur le blob vide, que l'épreuve crée
        // autour d'elle. Le pack fait la même chose, à la même ligne.
        g_fuzzer->blobId = Viper::BlobId{Viper::BlobLayout{}, Viper::Blob{}};
    }
    return g_fuzzer;
}

namespace {
/// Le blob que `withBlob` crée, pour que `withoutBlob` sache lequel effacer.
std::optional<Viper::BlobId> g_blob;
}

void testMetadata(std::shared_ptr<Viper::Database> const & db) {
    std::cout << "path: " << db->path() << '\n'
              << "uuid: " << db->uuid().uuidString() << '\n'
              << "documentation: " << db->documentation() << '\n'
              << "codecName: " << db->codecName() << '\n';
}

void testBlobCreate(std::shared_ptr<Viper::Database> const & db) {
    auto const name{"Topology.Test"};
    Viper::Blob const written{std::vector<std::uint8_t>{1, 2, 3, 4}};

    VIPER_ASSERT(name, db->blobIds().empty());

    auto const blobId{db->createBlob(Viper::BlobLayout{}, written)};
    VIPER_ASSERT(name, db->blobIds().size() == 1);

    auto const info{db->blobInfo(blobId)};
    VIPER_ASSERT(name, info != nullptr);
    VIPER_ASSERT(name, info->blobId == blobId);
    VIPER_ASSERT(name, info->size == 4);

    auto const read{db->blob(blobId)};
    VIPER_ASSERT(name, read.has_value());
    VIPER_ASSERT(name, read->storage == written.storage);

    db->delBlob(blobId);
    VIPER_ASSERT(name, db->blobIds().empty());
}

void testBlobStream(std::shared_ptr<Viper::Database> const & db) {
    auto const name{"Topology.Test"};
    Viper::Blob const written{std::vector<std::uint8_t>{1, 2, 3, 4, 5, 6, 7, 8}};

    auto const stream{db->blobStreamCreate(Viper::BlobLayout{}, written.size())};
    db->blobStreamAppend(stream, written.storage.data(), written.size());
    auto const blobId{db->blobStreamClose(stream)};

    auto const info{db->blobInfo(blobId)};
    VIPER_ASSERT(name, info != nullptr);
    VIPER_ASSERT(name, info->size == 8);

    // Relu en deux fois, pour éprouver la position autant que le contenu.
    Viper::Blob read{info->size};
    db->databasing()->readBlob(blobId, &read.storage[0], 4, 0);
    db->databasing()->readBlob(blobId, &read.storage[4], 4, 4);
    VIPER_ASSERT(name, read.storage == written.storage);

    db->delBlob(blobId);
}

void testBlobIO(std::shared_ptr<Viper::Database> const & db) {
    auto const name{"Topology.Test"};
    Viper::Blob const written{std::vector<std::uint8_t>{1, 2, 3, 4, 5, 6, 7, 8}};

    // UN IDENTIFIANT DE BLOB SE CALCULE DEPUIS LE CONTENU, il ne s'invente pas : c'est ce
    // qui rend deux blobs identiques indiscernables, et c'est pourquoi on peut réserver la
    // place avant d'écrire. Le pack l'écrit ainsi, et un identifiant vide est refusé.
    Viper::BlobId const blobId{Viper::BlobLayout{}, written};
    VIPER_ASSERT(name, db->databasing()->createZeroBlob(blobId, Viper::BlobLayout{}, written.size()));

    db->databasing()->writeBlob(blobId, &written.storage[0], 4, 0);
    db->databasing()->writeBlob(blobId, &written.storage[4], 4, 4);
    db->databasing()->freezeBlob(blobId);

    auto const info{db->blobInfo(blobId)};
    VIPER_ASSERT(name, info != nullptr);
    VIPER_ASSERT(name, info->size == 8);

    Viper::Blob read{info->size};
    db->databasing()->readBlob(blobId, &read.storage[0], 4, 0);
    db->databasing()->readBlob(blobId, &read.storage[4], 4, 4);
    VIPER_ASSERT(name, read.storage == written.storage);

    db->delBlob(blobId);
}

std::shared_ptr<Viper::Database> withBlob(std::shared_ptr<Viper::Database> const & db) {
    g_blob = db->createBlob(Viper::BlobLayout{}, Viper::Blob{});
    return db;
}

void withoutBlob(std::shared_ptr<Viper::Database> const & db) {
    if (g_blob) {
        db->delBlob(*g_blob);
        g_blob.reset();
    }
}

} // namespace Topology::Test
