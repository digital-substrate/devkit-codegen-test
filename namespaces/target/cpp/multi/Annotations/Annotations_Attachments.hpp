// THE ATTACHMENT-BORNE EDGE, visible in a signature -- and the naming rule it forces.
//
// This unit declares two attachments, both named `note`, on two same-named concepts
// it does not own. Every accessor takes a key from another unit, so the includes are
// not a courtesy: the unit does not compile without them. This is the edge that
// carried no dependency at all before kibo 9328acd.
//
// PROPOSED RULE, a change from today: qualify the scope with the concept's unit
// whenever the concept is not this unit's own -- always, not only when two attachments
// would otherwise collide.
//
// Today the generator qualifies on demand, and correctly: it counts attachments in
// the namespace sharing a name and a key-concept name, and prefixes only when more
// than one exists. It never collides. But the name is then a function of the whole
// namespace's attachment set: with only the ModelA one present the scope is
// `Material_Note`, and adding the ModelB one renames it to `ModelA_Material_Note`.
// A source-compatible model change moves a generated symbol.
//
// Always qualifying costs a longer name in the common case and buys a name that does
// not move. It also reads the same way as the signature, which already says
// ModelA::MaterialKey, and as the rest of the design: unqualified inside a unit,
// qualified at every composition site.

#ifndef Annotations_Attachments_hpp
#define Annotations_Attachments_hpp

#include "Annotations_Data.hpp"     // its own, empty -- see the note there
#include "ModelA_Data.hpp"          // computed from the dependency set, not composed
#include "ModelB_Data.hpp"
#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"

namespace Annotations::Attachments::ModelA_Material_Note {

std::set<ModelA::MaterialKey> keys(std::shared_ptr<Viper::AttachmentGetting> const &);
std::optional<std::string> get(std::shared_ptr<Viper::AttachmentGetting> const &, ModelA::MaterialKey const &);
void set(std::shared_ptr<Viper::AttachmentMutating> const &, ModelA::MaterialKey const &, std::string const &);
// ... unchanged ...

} // ns

namespace Annotations::Attachments::ModelB_Material_Note {
// ... the same, on ModelB::MaterialKey ...
} // ns

#endif
