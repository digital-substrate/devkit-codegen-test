"""The Commit application: writes the fixture through its usage, commit_attachments, commits it, then
prints what the library reads from the committed state."""

import dsviper

import fixture
from library_describe import describe
from shop import definitions
from shop.store import commit_attachments as attachments

database = dsviper.CommitDatabase.create_in_memory()
database.extend_definitions(definitions())
state = dsviper.CommitMutableState(dsviper.CommitStateBuilder.initial_state(database))
mutating = state.attachment_mutating()
for key, value in fixture.products():
    attachments.Product.properties.set(mutating, key, value)
for key, value in fixture.parts():
    attachments.Part.properties.set(mutating, key, value)
commit_id = database.commit_mutations("fixture", state)

print(describe(dsviper.CommitStateBuilder.state(database, commit_id).attachment_getting()))
