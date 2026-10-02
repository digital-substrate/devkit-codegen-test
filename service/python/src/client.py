"""The service client, ported to the new templates.

This file is not generated: it is what a developer writes against the pool. The only
changes from the previous version are names the templates moved: a namespace became a
module, and both sides of a pool now live in one.
"""
import sys

import dsviper

from service import AnyValue, definitions
from service.demo import Vector3, Level, attachments
from service.player_model.pool import Remote as PlayerModelRemote
from service.tools.pool import Remote as ToolsRemote

address, port = (sys.argv[1], sys.argv[2]) if len(sys.argv) > 2 else ("localhost", "54328")

defs = dsviper.Definitions()
service_remote = dsviper.ServiceRemote.connect(address, port, defs)

tools = ToolsRemote(service_remote)
if tools.is_available():
    # The model's documentation goes end to end: the C++ server registers it with the function,
    # the client reads it remotely, and the generated method carries it as its docstring --
    # multi-line and with quotes, which an unescaped C++ literal would not compile.
    documented = 'Return a random string of "size" letters.\nThe letters are lower case.'
    remote_tools = next(p for p in service_remote.function_pools() if p.name() == "Tools")
    assert remote_tools.documentation() == "This pool provides access to the various utility functions."
    assert remote_tools.query("randomString").documentation() == documented
    assert ToolsRemote.random_string.__doc__ == documented
    print("documentation: registered by the server, read by the client, carried by the method")

    print(f"add(32,10) -> {tools.add(32, 10)}")

    v1 = Vector3({"x": 1, "y": 2, "z": 3})
    v2 = Vector3({"x": 10, "y": 20, "z": 30})
    print(f"add_vector(v1,v2) -> {tools.add_vector(v1, v2)}")
    # `any` crosses the boundary as the generated AnyValue the method is annotated with. The 1.2
    # laboratory's service predates the function, and the cross-version check calls it too.
    if remote_tools.query("isGreater"):
        print(f"is_greater(3,2) -> {tools.is_greater(AnyValue(3), AnyValue(2))}")

player_model = PlayerModelRemote(service_remote)
if player_model.is_available():
    state = dsviper.CommitState(defs.const())
    mutable = dsviper.CommitMutableState(state)
    mutating = mutable.attachment_mutating()

    nickname = "the shadow man"
    key = player_model.create(mutating, nickname, Level.BEGINNER)
    print(f"key is {key}")

    # A function that only reads takes a state that only reads: the commit state the
    # mutable one was built on, which the create above did not touch.
    if not player_model.has_player(state.attachment_getting(), nickname):
        print("read-only state: no player")

    if found := player_model.has_player(mutating, nickname):
        if document := attachments.Player.property.get(mutating, found.unwrap()):
            player = document.unwrap()
            print(f"nickname={player.nickname}, level={player.level}")
