// The service client, ported to the new templates.
//
// This file is not generated: it is what a developer writes against the pool. The only
// changes from the previous version are names the templates moved: a namespace became a
// module, and both sides of a pool now live in one.
import dsviper from "@digitalsubstrate/dsviper";
import { Vector3, Level } from "../generated/dist/demo/index.js";
import { AnyValue } from "../generated/dist/index.js";
// Attachments are deliberately not re-exported by the unit's entry point: two units linked
// by an attachment would become an import cycle.
import { Player } from "../generated/dist/demo/attachments.js";
// Every pool of the model, from the one entry the Pool feature renders.
import { tools, player_model } from "../generated/dist/pools.js";

const [address, port] = process.argv.length > 3
    ? [process.argv[2], process.argv[3]]
    : ["localhost", "54328"];

const defs = new dsviper.Definitions();
const serviceRemote = dsviper.ServiceRemote.connect(address, port, defs);

const toolsRemote = new tools.Remote(serviceRemote);
if (toolsRemote.isAvailable()) {
    console.log(`add(32,10) -> ${toolsRemote.add(32n, 10n)}`);

    const v1 = new Vector3({ x: 1, y: 2, z: 3 });
    const v2 = new Vector3({ x: 10, y: 20, z: 30 });
    console.log(`addVector(v1,v2) -> ${toolsRemote.addVector(v1, v2)}`);
    // `any` crosses the boundary as the generated AnyValue the method is annotated with. The 1.2
    // laboratory's service predates the function, and the cross-version check calls it too.
    const remoteTools = serviceRemote.functionPools().find((p) => p.name() === "Tools");
    if (remoteTools?.query("isGreater"))
        console.log(`isGreater(3,2) -> ${toolsRemote.isGreater(new AnyValue(3n), new AnyValue(2n))}`);
}

const playerModel = new player_model.Remote(serviceRemote);
if (playerModel.isAvailable()) {
    const state = new dsviper.CommitState(defs.const());
    const mutable = new dsviper.CommitMutableState(state);
    const mutating = mutable.attachmentMutating();

    const nickname = "the shadow man";
    console.log(`key is ${playerModel.create(mutating, nickname, Level.BEGINNER)}`);

    // A function that only reads takes a state that only reads: the commit state the
    // mutable one was built on, which the create above did not touch.
    if (playerModel.hasPlayer(state.attachmentGetting(), nickname).isNil())
        console.log("read-only state: no player");

    const found = playerModel.hasPlayer(mutating, nickname);
    if (!found.isNil()) {
        const document = Player.property.get(mutating, found.unwrap());
        if (!document.isNil()) {
            const player = document.unwrap();
            console.log(`nickname=${player.nickname}, level=${player.level}`);
        }
    }
}
