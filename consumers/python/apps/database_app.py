"""The Database application: writes the fixture through its usage, database_attachments, then prints
what the library reads from the database as it is."""

import dsviper

import fixture
from library_describe import describe
from shop import definitions
from shop.store import database_attachments as attachments

database = dsviper.Database.create_in_memory()
database.extend_definitions(definitions())
database.begin_transaction()
for key, value in fixture.products():
    attachments.Product.properties.set(database, key, value)
for key, value in fixture.parts():
    attachments.Part.properties.set(database, key, value)
database.commit()

print(describe(database.attachment_getting()))
