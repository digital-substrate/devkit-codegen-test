"""The models this repository carries, and what each is for.

One place so that a driver, a harness and a reader all agree on the same list.
"""

# A model is mono- or multi-namespace, and that decides how its diff is read:
# a mono model guards against regression (any difference is one), while a multi
# model shows an intended effect and its diff is read rather than asserted.
MODELS = {
    "features": dict(
        shape="mono", definitions="features/all.dsm", namespace="Features", package="features",
        about="the type system: every type shape, one namespace",
        cpp=["TestApp", "AttachmentPool"],
    ),
    "service": dict(
        shape="mono", definitions="service/definitions/Service", namespace="Service", package="service",
        about="pools and the remote, one namespace",
        cpp=["Pool", "AttachmentPool", "Test"],
    ),
    "crossing": dict(
        shape="multi", definitions="crossing/definitions", namespace="Crossing", package="crossing",
        about="the type system crossing namespaces: every composite shape with elements from two suppliers",
        cpp=["TestApp", "AttachmentPool"],
    ),
    "namespaces": dict(
        shape="multi", definitions="namespaces/definitions", namespace="Topology", package="topology",
        about="namespace topology and nothing else: five namespaces, every edge kind",
        cpp=["TestApp", "AttachmentPool"],
    ),
}
