// Ce que JSON et l'empreinte permettent, vérifié par le compilateur -- en composant le pont.
//
// Le pack ne génère ni `jsonEncode` ni `hexdigest` : ce ne sont que le pont statique ⇄
// dynamique suivi d'une transition que le runtime possède déjà. Un développeur les écrit en
// une ligne, et reçoit d'office toute transition que le runtime ajoutera -- le XML compris,
// qu'aucune génération n'avait jamais couvert.
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

    // un type d'unité : le pont, puis la transition du runtime
    auto const j = Viper::JsonValueEncoder::json_encode(encode(c));
    auto const back = decode<topology::model_a::Colour>(
        Viper::JsonValueDecoder::json_decode(j, type(tag<topology::model_a::Colour>{}), definitions()));
    auto const h = hexdigest(encode(c));
    auto const x = Viper::XmlValueEncoder::to_string(encode(c));

    // et n'importe quelle forme au-dessus, sans qu'aucune unité ait rien déclaré
    std::map<topology::model_a::MaterialKey, topology::model_a::Colour> m;
    auto const jm = Viper::JsonValueEncoder::json_encode(encode(m));
    auto const hm = hexdigest(encode(m));

    (void)back; (void)h; (void)x; (void)jm; (void)hm;
}
