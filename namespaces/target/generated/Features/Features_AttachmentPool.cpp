// La construction du pool, par parcours du modèle.
//
// TROIS FAMILLES, ET AUCUNE NE CONNAÎT UN TYPE DU MODÈLE :
//
//   sur l'attachment      keys, has, get          -- lecture
//                         set, diff               -- écriture du document entier
//   sur un champ          set<Champ>              -- écriture partielle, par un chemin
//   sur un champ agrégé   union, subtract, update -- même forme, autre appel du runtime
//
// La dernière famille n'est pas écrite ici : elle se distingue des précédentes par le
// `TypeCode` du champ et par la méthode appelée, rien d'autre. Ce qui est écrit suffit à
// montrer ce qui était en question -- que la génération n'apporte rien.

#include "Features_AttachmentPool.hpp"

#include "Features_Codec.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Types.hpp"
#include "Viper_Values.hpp"

namespace Features {

namespace {

using Attachment = std::shared_ptr<Viper::Attachment>;
using ValuePtr = std::shared_ptr<Viper::Value>;
using Args = std::vector<ValuePtr>;

/// Une fonction de lecture, définie par ce qu'elle fait et non par ce sur quoi elle agit.
class Getting final : public Viper::AttachmentGettingFunction {
public:
    using Body = std::function<ValuePtr(
        std::shared_ptr<Viper::AttachmentGetting> const &, Attachment const &, Args const &)>;

    Getting(std::shared_ptr<Viper::FunctionPrototype> prototype, std::string documentation,
            Attachment attachment, Body body)
    : Viper::AttachmentGettingFunction{std::move(prototype), std::move(documentation)}
    , _attachment{std::move(attachment)}, _body{std::move(body)} {}

    std::string representation() const override { return _attachment->identifier(); }

    ValuePtr checkedCall(
        std::shared_ptr<Viper::AttachmentGetting> const & getting, Args const & args) const {
        return _body(getting, _attachment, args);
    }

private:
    Attachment _attachment;
    Body _body;
};

class Mutating final : public Viper::AttachmentMutatingFunction {
public:
    using Body = std::function<ValuePtr(
        std::shared_ptr<Viper::AttachmentMutating> const &, Attachment const &, Args const &)>;

    Mutating(std::shared_ptr<Viper::FunctionPrototype> prototype, std::string documentation,
             Attachment attachment, Body body)
    : Viper::AttachmentMutatingFunction{std::move(prototype), std::move(documentation)}
    , _attachment{std::move(attachment)}, _body{std::move(body)} {}

    std::string representation() const override { return _attachment->identifier(); }

    ValuePtr checkedCall(
        std::shared_ptr<Viper::AttachmentMutating> const & mutating, Args const & args) const {
        return _body(mutating, _attachment, args);
    }

private:
    Attachment _attachment;
    Body _body;
};

/// Le nom d'une fonction : celui de l'attachment, et l'opération. Le pack le compose à la
/// génération ; il se compose aussi bien ici, depuis le descripteur.
std::string named(Attachment const & a, std::string const & operation) {
    return a->identifier() + "_" + operation;
}

void addReading(std::shared_ptr<Viper::AttachmentFunctionPool> const & pool, Attachment const & a) {
    using P = Viper::FunctionPrototype;

    pool->add(std::make_shared<Getting>(
        P::make(named(a, "keys"), {}, Viper::TypeSet::make(a->keyType)),
        "return the set of keys.", a,
        [](auto const & g, auto const & at, auto const &) -> ValuePtr {
            return g->keys(at);
        }));

    pool->add(std::make_shared<Getting>(
        P::make(named(a, "has"), {{"key", a->keyType}}, type(Viper::Codec::tag<bool>{})),
        "return true if a document is present.", a,
        [](auto const & g, auto const & at, auto const & args) -> ValuePtr {
            return Viper::ValueBool::from(g->has(at, Viper::ValueKey::cast(args.at(0))));
        }));

    pool->add(std::make_shared<Getting>(
        P::make(named(a, "get"), {{"key", a->keyType}}, Viper::TypeOptional::make(a->documentType)),
        "return an optional document.", a,
        [](auto const & g, auto const & at, auto const & args) -> ValuePtr {
            return g->get(at, Viper::ValueKey::cast(args.at(0)));
        }));
}

void addWriting(std::shared_ptr<Viper::AttachmentFunctionPool> const & pool, Attachment const & a) {
    using P = Viper::FunctionPrototype;

    pool->add(std::make_shared<Mutating>(
        P::make(named(a, "set"), {{"key", a->keyType}, {"value", a->documentType}},
                Viper::TypeVoid::Instance()),
        "set the document.", a,
        [](auto const & m, auto const & at, auto const & args) -> ValuePtr {
            m->set(at, Viper::ValueKey::cast(args.at(0)), args.at(1));
            return Viper::ValueVoid::Instance();
        }));
}

/// L'écriture partielle, un champ à la fois.
///
/// LE CHEMIN SE FABRIQUE ICI, ET C'EST LE POINT. Le pack appelle `Path::Colour::r()`, une
/// fonction générée -- mais ce qu'elle rend est `Viper::Path::makeField("r")`, et le nom du
/// champ est dans le descripteur de la structure. La couche 2 sert le développeur ; le pont
/// dynamique n'en a pas besoin.
void addFields(std::shared_ptr<Viper::AttachmentFunctionPool> const & pool, Attachment const & a) {
    auto const structure = Viper::TypeStructure::cast(a->documentType);
    if (!structure)
        return;

    for (auto const & field : structure->fields()) {
        auto const path = Viper::Path::makeField(field->name);
        pool->add(std::make_shared<Mutating>(
            Viper::FunctionPrototype::make(named(a, "set_" + field->name),
                                           {{"key", a->keyType}, {"value", field->type}},
                                           Viper::TypeVoid::Instance()),
            "set the property of the document.", a,
            [path](auto const & m, auto const & at, auto const & args) -> ValuePtr {
                m->update(at, Viper::ValueKey::cast(args.at(0)), path, args.at(1));
                return Viper::ValueVoid::Instance();
            }));
    }
}

} // namespace

std::shared_ptr<Viper::AttachmentFunctionPool> attachments() {
    static auto const instance = [] {
        auto const pool = Viper::AttachmentFunctionPool::make(
            Viper::UUId::parse("00000000-0000-0000-0000-000000000000"), "Attachments");

        for (auto const & a : Codec::definitions()->attachments()) {
            addReading(pool, a);
            addWriting(pool, a);
            addFields(pool, a);
        }
        return pool;
    }();
    return instance;
}

} // namespace Features
