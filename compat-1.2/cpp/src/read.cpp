// Read back a database written by the 1.2 runtime, with the code the generation produces today.
//
// Every value is compared, not merely decoded: a transposed mat decodes without error (six
// cells read for six written) and only shows on comparison. The expectations are written in
// the C++ types the generation gives, which is what must stay true from one version to the next.
//
// The values are those `write_1_2.py` wrote; read the two side by side.
#include "compat12_compat_attachments.hpp"

#include "Viper_Database.hpp"
#include "Viper_ValueAny.hpp"
#include "Viper_ValueString.hpp"

#include <iostream>

namespace {

using namespace compat12::compat;
namespace A = compat12::compat::attachments::Probe;

int failures{};

template<class T>
void expect(char const * name, std::optional<T> const & got, T const & expected) {
    if (got && *got == expected) {
        std::cout << "ok " << name << "\n";
        return;
    }
    std::cout << (got ? "DIFFERS " : "ABSENT ") << name << "\n";
    ++failures;
}

Viper::UUId uuid(char const * text) { return Viper::UUId::parse(text); }

} // namespace

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <Compat-1.2.cdb>\n";
        return 2;
    }

    auto const db{Viper::Database::open(argv[1], true)};
    ProbeKey const probe{uuid("c0a7c0de-0001-4000-8000-000000000001")};
    OtherKey const other{uuid("c0a7c0de-0002-4000-8000-000000000002")};
    OtherKey const otherBis{uuid("c0a7c0de-0003-4000-8000-000000000003")};

    Point const point{1.5f, -2.25};
    Record const record{"Record", point, {{{11, 12, 13}, {21, 22, 23}}}, Shade::Dark, {-300, 0, 300}};
    std::array<std::array<std::uint8_t, 3>, 2> const mat{{{1, 2, 3}, {4, 5, 6}}};

    // Numbers
    expect("docBool", A::docBool::get(db, probe), true);
    expect("docUInt8", A::docUInt8::get(db, probe), std::uint8_t{0xA1});
    expect("docUInt16", A::docUInt16::get(db, probe), std::uint16_t{0xA1B2});
    expect("docUInt32", A::docUInt32::get(db, probe), std::uint32_t{0xA1B2C3D4});
    expect("docUInt64", A::docUInt64::get(db, probe), std::uint64_t{0xA1B2C3D4E5F60718});
    expect("docInt8", A::docInt8::get(db, probe), std::int8_t{-0x5F});
    expect("docInt16", A::docInt16::get(db, probe), std::int16_t{-0x5E4E});
    expect("docInt32", A::docInt32::get(db, probe), std::int32_t{-0x5E4D3C2C});
    expect("docInt64", A::docInt64::get(db, probe), std::int64_t{-0x5E4D3C2B1A09F8E8});
    expect("docFloat", A::docFloat::get(db, probe), 1.5f);
    expect("docDouble", A::docDouble::get(db, probe), -2.25);

    // Ids, string, blob
    expect("docUUId", A::docUUId::get(db, probe), uuid("0f1e2d3c-4b5a-4968-8778-a695b4c3d2e1"));
    expect("docBlobId", A::docBlobId::get(db, probe),
           Viper::BlobId{Viper::BlobLayout{}, Viper::Blob{std::vector<std::uint8_t>{1, 2, 3, 4, 5}}});
    expect("docCommitId", A::docCommitId::get(db, probe),
           Viper::CommitId::parse("0123456789abcdef0123456789abcdef01234567"));
    expect("docString", A::docString::get(db, probe), std::string{"Written by 1.2"});
    expect("docBlob", A::docBlob::get(db, probe),
           Viper::Blob{std::vector<std::uint8_t>{0x00, 0x01, 0x7F, 0x80, 0xFE, 0xFF}});

    // Vec & Mat -- the mat reads column by column: mat[1][2] is the third row of the second
    // column, 6.
    expect("docVec", A::docVec::get(db, probe), std::array<std::int32_t, 3>{1, -2, 0x01020304});
    expect("docMat", A::docMat::get(db, probe), mat);

    // Containers
    expect("docTuple", A::docTuple::get(db, probe), std::tuple<std::uint8_t, std::string>{7, "seven"});
    expect("docOptional", A::docOptional::get(db, probe), std::optional<std::uint16_t>{0x0102});
    expect("docVectorMat", A::docVectorMat::get(db, probe),
           std::vector<std::array<std::array<std::uint8_t, 3>, 2>>{mat, {{{7, 8, 9}, {10, 11, 12}}}});
    expect("docSet", A::docSet::get(db, probe), std::set<std::string>{"alpha", "beta", "gamma"});
    expect("docMap", A::docMap::get(db, probe),
           std::map<std::string, Point>{{"a", point}, {"b", Point{-0.5f, 1e300}}});
    expect("docVariant", A::docVariant::get(db, probe),
           std::variant<std::string, std::uint8_t, Point>{point});
    expect("docAny", A::docAny::get(db, probe),
           Viper::Any{Viper::ValueAny::make(Viper::ValueString::make("any"))});

    // An xarray is not compared as a whole: its positions were created in the database. What
    // must survive is the order of its elements, read by index.
    std::vector<std::uint8_t> elements;
    if (auto const xarray{A::docXArray::get(db, probe)})
        for (std::size_t index{}; index < xarray->size(); ++index)
            elements.push_back(xarray->at(index));
    expect("docXArray", std::optional{elements}, std::vector<std::uint8_t>{3, 1, 2});

    // Entities
    expect("docShade", A::docShade::get(db, probe), Shade::Medium);
    expect("docPoint", A::docPoint::get(db, probe), point);
    expect("docRecord", A::docRecord::get(db, probe), record);
    expect("docKey", A::docKey::get(db, probe), other);
    Record bis{record};
    bis.name = "bis";
    bis.shade = Shade::Light;
    expect("docNested", A::docNested::get(db, probe),
           std::map<OtherKey, std::vector<Record>>{{other, {record}}, {otherBis, {record, bis}}});

    if (failures) {
        std::cout << failures << " attachment(s) read back differently from what was written\n";
        return 1;
    }
    return 0;
}
