// The service client, ported to the new templates.
//
// This file is not generated: it is what a developer writes against the pool. The only
// changes from the previous version are names the templates moved: a namespace became a
// module, and both sides of a pool now live in one.
import dsviper from "@digitalsubstrate/dsviper";
import { Vector3, Level } from "../generated/dist/demo/index.js";
// Attachments are deliberately not re-exported by the unit's entry point: two units linked
// by an attachment would become an import cycle.
import { Player } from "../generated/dist/demo/attachments.js";
import { Remote as ToolsRemote } from "../generated/dist/tools/pool.js";
import { Remote as PlayerModelRemote } from "../generated/dist/player_model/pool.js";

const [address, port] = process.argv.length > 3
    ? [process.argv[2], process.argv[3]]
    : ["localhost", "54328"];

const defs = new dsviper.Definitions();
const serviceRemote = dsviper.ServiceRemote.connect(address, port, defs);

const tools = new ToolsRemote(serviceRemote);
if (tools.isAvailable()) {
    console.log(`add(32,10) -> ${tools.add(32n, 10n)}`);

    const v1 = new Vector3({ x: 1, y: 2, z: 3 });
    const v2 = new Vector3({ x: 10, y: 20, z: 30 });
    console.log(`addVector(v1,v2) -> ${tools.addVector(v1, v2)}`);
}

const playerModel = new PlayerModelRemote(serviceRemote);
if (playerModel.isAvailable()) {
    const mutable = new dsviper.CommitMutableState(new dsviper.CommitState(defs.const()));
    const mutating = mutable.attachmentMutating();

    const nickname = "the shadow man";
    console.log(`key is ${playerModel.create(mutating, nickname, Level.BEGINNER)}`);

    const found = playerModel.hasPlayer(mutating, nickname);
    if (!found.isNil()) {
        const document = Player.property.get(mutating, found.unwrap());
        if (!document.isNil()) {
            const player = document.unwrap();
            console.log(`nickname=${player.nickname}, level=${player.level}`);
        }
    }
}
