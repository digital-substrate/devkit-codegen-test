from dsviper import Definitions, ServiceRemote, CommitMutableState, CommitState
from service.data import *
import service.function_pool_remotes as fpr
import service.attachment_function_pool_remotes as afpr
import service.attachments as sea

defs = Definitions()
service_remote = ServiceRemote.connect("localhost", "54328", defs)

TOOLS = fpr.Tools(service_remote)
if TOOLS.is_available():
    r = TOOLS.add(32, 10)
    print(r)

    v1 = Demo_Vector3({"x":1, "y":2, "z": 3})
    v2 = Demo_Vector3({"x":10, "y":20, "z": 30})

    vr = TOOLS.add_vector(v1, v2)
    print(vr)


    PM = afpr.PlayerModel(service_remote)
    if PM.is_available():
        state = CommitState(defs.const())
        mutable_state = CommitMutableState(state)
        mutating = mutable_state.attachment_mutating()
        nickname = "the shadow man"
        key = PM.create(mutating, nickname, Demo_Level.BEGINNER)
        print(f'key is {key}')
        if pk := PM.has_player(mutating, nickname):
            if p := sea.demo_player_property_get(mutating, pk.unwrap()):
                p = p.unwrap()
                print(f'nickname={p.nickname}, level={p.level}')