"""The sites this repository carries, and what each is for.

What a site generates -- its definitions, infrastructure and features per target -- is its
`kibo.toml`. This says what no project file does: the shape of the site's model, which decides
how a change to its output is judged, and why the site exists. One place, so that `check.py`
and the tools agree on the same list.
"""

SITES = {
    "features": dict(
        shape="mono",
        about="the type system: every type shape, one namespace",
    ),
    "service": dict(
        shape="mono",
        about="pools and the remote, one namespace",
    ),
    "namespaces": dict(
        shape="multi",
        about="namespace topology and nothing else: five namespaces, every edge kind",
    ),
    "crossing": dict(
        shape="multi",
        about="the type system crossing namespaces: every composite shape with elements from two suppliers",
    ),
    "compat-1.2": dict(
        shape="mono",
        about="a database written by the 1.2 runtime, read back by what is generated now; the model is frozen",
    ),
}
