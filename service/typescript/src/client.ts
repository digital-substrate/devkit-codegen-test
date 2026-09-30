// Le client du service, porté sur les nouveaux templates.
//
// Ce fichier n'est pas généré : il est ce qu'un développeur écrit en face du pool. Les seuls
// changements par rapport à la version précédente sont les noms que les templates ont
// déplacés sous ses pieds -- un namespace est devenu un module, et les deux bords d'un pool
// tiennent dans un seul.
import dsviper from "@digitalsubstrate/dsviper";
import { Vector3, Level } from "../generated/dist/demo/index.js";
// Les attachments ne sont pas réexportés par le point d'entrée de l'unité, et c'est voulu :
// deux unités liées par un attachment deviendraient un cycle d'import.
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
    if (found !== undefined) {
        const player = Player.property.get(mutating, found);
        if (player !== undefined) {
            console.log(`nickname=${player.nickname}, level=${player.level}`);
        }
    }
}
