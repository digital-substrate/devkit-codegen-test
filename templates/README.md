# templates — the laboratory's own templates

The tests of the generator: every type round-tripped through each codec, every attachment
through a database, every pool through the bridge. They are not part of the template pack, and
no project selects them.

The pack itself is the sibling `kibo-template-viper` checkout (or `KIBO_TEMPLATES`). These
features join its selection through `resolve.py`'s `extra`:

```python
resolve.templates("cpp", ["TestApp", "AttachmentPool"], extra=["templates/features.json"])
```
