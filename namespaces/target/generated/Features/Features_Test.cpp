#include "Features_Test.hpp"

#include <cstddef>
#include <iostream>
#include <optional>

namespace Features::Test {

namespace {
std::optional<std::uint64_t> g_seed;
std::shared_ptr<Viper::Fuzzer> g_fuzzer;
}

void seed(std::uint64_t value) {
    g_seed = value;
    g_fuzzer.reset();
}

std::shared_ptr<Viper::Fuzzer> const & fuzzer() {
    if (!g_fuzzer)
        g_fuzzer = g_seed ? Viper::Fuzzer::make(Codec::definitions(), *g_seed)
                          : Viper::Fuzzer::make(Codec::definitions());
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
    auto const name{"Features.Test"};
    Viper::Blob const written{{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}}};

    VIPER_ASSERT(name, db->blobIds().empty());

    auto const blobId{db->createBlob(Viper::BlobLayout{}, written)};
    VIPER_ASSERT(name, db->blobIds().size() == 1);

    auto const info{db->blobInfo(blobId)};
    VIPER_ASSERT(name, info.has_value());
    VIPER_ASSERT(name, info->blobId == blobId);
    VIPER_ASSERT(name, info->size == 4);

    auto const read{db->blob(blobId)};
    VIPER_ASSERT(name, read.has_value());
    VIPER_ASSERT(name, read->storage == written.storage);

    db->delBlob(blobId);
    VIPER_ASSERT(name, db->blobIds().empty());
}

void testBlobStream(std::shared_ptr<Viper::Database> const & db) {
    auto const name{"Features.Test"};
    Viper::Blob const written{{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4},
                              std::byte{5}, std::byte{6}, std::byte{7}, std::byte{8}}};

    auto const stream{db->blobStreamCreate(Viper::BlobLayout{}, written.size())};
    db->blobStreamAppend(stream, written.storage.data(), written.size());
    auto const blobId{db->blobStreamClose(stream)};

    auto const info{db->blobInfo(blobId)};
    VIPER_ASSERT(name, info.has_value());
    VIPER_ASSERT(name, info->size == 8);

    // Relu en deux fois, pour éprouver la position autant que le contenu.
    Viper::Blob read{info->size};
    db->readBlob(blobId, &read.storage[0], 4, 0);
    db->readBlob(blobId, &read.storage[4], 4, 4);
    VIPER_ASSERT(name, read.storage == written.storage);

    db->delBlob(blobId);
}

void testBlobIO(std::shared_ptr<Viper::Database> const & db) {
    auto const name{"Features.Test"};
    Viper::Blob const written{{std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4},
                              std::byte{5}, std::byte{6}, std::byte{7}, std::byte{8}}};

    // Réserver la place, écrire dedans, puis figer : l'ordre est celui que la base impose.
    Viper::BlobId const blobId{};
    VIPER_ASSERT(name, db->createZeroBlob(blobId, Viper::BlobLayout{}, written.size()));

    db->writeBlob(blobId, &written.storage[0], 4, 0);
    db->writeBlob(blobId, &written.storage[4], 4, 4);
    db->freezeBlob(blobId);

    auto const info{db->blobInfo(blobId)};
    VIPER_ASSERT(name, info.has_value());
    VIPER_ASSERT(name, info->size == 8);

    Viper::Blob read{info->size};
    db->readBlob(blobId, &read.storage[0], 4, 0);
    db->readBlob(blobId, &read.storage[4], 4, 4);
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

} // namespace Features::Test
