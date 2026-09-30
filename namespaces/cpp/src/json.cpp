// What JSON and hashing allow, checked by the compiler -- by composing the bridge.
//
// The pack generates neither `jsonEncode` nor `hexdigest`: they are just the static ⇄
// dynamic bridge followed by a transition the runtime already has. A developer writes each
// in one line, and gets any transition the runtime adds for free -- including XML, which no
// generation had ever covered.
#include "topology_model_a_codec.hpp"
#include "topology_model_a_model.hpp"
#include "topology_codec.hpp"

#include "Viper_HashSHA1.hpp"
#include "Viper_JsonValueDecoder.hpp"
#include "Viper_JsonValueEncoder.hpp"
#include "Viper_ValueHasher.hpp"
#include "Viper_XmlValueEncoder.hpp"

#include <map>
#include <set>

namespace {

std::string hexdigest(std::shared_ptr<Viper::Value const> const & value) {
    auto const hasher = Viper::HashSHA1::make();
    Viper::ValueHasher::hash(value, hasher);
    return hasher->hexDigest();
}

} // namespace

void use_json() {
    using namespace topology::codec;
    topology::model_a::Colour const c{1, 2, 3};

    // a unit type: the bridge, then the runtime's transition
    auto const j = Viper::JsonValueEncoder::json_encode(encode(c));
    auto const back = decode<topology::model_a::Colour>(
        Viper::JsonValueDecoder::json_decode(j, type(tag<topology::model_a::Colour>{}), definitions()));
    auto const h = hexdigest(encode(c));
    auto const x = Viper::XmlValueEncoder::to_string(encode(c));

    // and any shape built on top, without any unit declaring anything
    std::map<topology::model_a::MaterialKey, topology::model_a::Colour> m;
    auto const jm = Viper::JsonValueEncoder::json_encode(encode(m));
    auto const hm = hexdigest(encode(m));

    (void)back; (void)h; (void)x; (void)jm; (void)hm;
}
