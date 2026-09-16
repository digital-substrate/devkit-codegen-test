# cpp — where generated and hand-written sit side by side

    generated/   kibo, and nobody else
    src/         the developer: two pool implementations, a client, a server

A pool generates its declaration and its remote edge; the behaviour is yours.
`ToolsPoolBridges.cpp` and `PlayerModelPoolBridges.cpp` implement what `Tools_Pool.hpp` and
`PlayerModel_Pool.hpp` declare. They were named after `FunctionPoolBridges`, an artefact the
new templates no longer produce, and renamed for what they now implement.

`run_test.sh` builds both programmes, raises the server on a local socket, runs the client
against it, and cleans up.

## The client links more than it should

`service_client` links the two bridge implementations, and should not have to. Both edges of
a pool are in one generated translation unit, so linking the remote edge drags in the local
one and the linker asks for `Tools::add`. See `../README.md`.
