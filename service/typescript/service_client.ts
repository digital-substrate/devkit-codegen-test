// Hand-written TypeScript client mirroring service/python/service_client.py.
// Connects to a live service over ServiceRemote and exercises the generated
// remote function pools + an attachment getter. Requires a running service.
import dsviper from "@digitalsubstrate/dsviper";
import {
    Demo_Vector3,
    Demo_Level,
    functionPoolRemotes as fpr,
    attachmentFunctionPoolRemotes as afpr,
    attachments as sea,
} from "./service/dist/index.js";

const defs = new dsviper.Definitions();
const serviceRemote = dsviper.ServiceRemote.connect("localhost", "54328", defs);

const tools = new fpr.Tools(serviceRemote);
if (tools.isAvailable()) {
    const r = tools.add(32n, 10n);
    console.log(r);

    const v1 = new Demo_Vector3({ x: 1, y: 2, z: 3 });
    const v2 = new Demo_Vector3({ x: 10, y: 20, z: 30 });

    const vr = tools.add_vector(v1, v2);
    console.log(vr.toString());

    const pm = new afpr.PlayerModel(serviceRemote);
    if (pm.isAvailable()) {
        const state = new dsviper.CommitState(defs.const());
        const mutableState = new dsviper.CommitMutableState(state);
        const mutating = mutableState.attachmentMutating();
        const nickname = "the shadow man";
        const key = pm.create(mutating, nickname, Demo_Level.BEGINNER);
        console.log(`key is ${key}`);
        const pk = pm.has_player(mutating, nickname);
        if (!pk.isNil()) {
            const property = sea.player_Property.get(mutating, pk.unwrap());
            if (!property.isNil()) {
                const p = property.unwrap();
                console.log(`nickname=${p.nickname}, level=${p.level}`);
            }
        }
    }
}
