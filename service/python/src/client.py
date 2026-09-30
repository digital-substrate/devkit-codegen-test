"""Le client du service, porté sur les nouveaux templates.

Ce fichier n'est pas généré : il est ce qu'un développeur écrit en face du pool. Les seuls
changements par rapport à la version précédente sont les noms que les templates ont déplacés
sous ses pieds -- un namespace est devenu un module, et les deux bords d'un pool tiennent
dans un seul.
"""
import sys

import dsviper

from service import definitions
from service.demo import Vector3, Level, attachments
from service.player_model.pool import Remote as PlayerModelRemote
from service.tools.pool import Remote as ToolsRemote

address, port = (sys.argv[1], sys.argv[2]) if len(sys.argv) > 2 else ("localhost", "54328")

defs = dsviper.Definitions()
service_remote = dsviper.ServiceRemote.connect(address, port, defs)

tools = ToolsRemote(service_remote)
if tools.is_available():
    # LA DOCUMENTATION DU MODÈLE TRAVERSE TOUT. Le serveur C++ l'enregistre avec la fonction,
    # le client la lit à distance, et la méthode générée la porte en docstring -- sur plusieurs
    # lignes et avec des guillemets, ce qu'un littéral C++ non échappé ne compilerait pas.
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

player_model = PlayerModelRemote(service_remote)
if player_model.is_available():
    mutable = dsviper.CommitMutableState(dsviper.CommitState(defs.const()))
    mutating = mutable.attachment_mutating()

    nickname = "the shadow man"
    key = player_model.create(mutating, nickname, Level.BEGINNER)
    print(f"key is {key}")

    if found := player_model.has_player(mutating, nickname):
        if player := attachments.Player.property.get(mutating, found):
            print(f"nickname={player.nickname}, level={player.level}")
