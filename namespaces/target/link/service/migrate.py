"""Le service existant, porté sur les nouveaux templates — et rien d'autre.

Les quatre fichiers de `service/` sont du code de consommateur : deux ponts que le
développeur écrit, un client et un serveur. Ils ne sont pas générés, donc ils ne changent
pas quand le générateur change -- sauf pour ce que le générateur leur a renommé sous les
pieds. Ce que ce fichier contient est exactement ça : la liste des renommages, et rien
d'autre. Une ligne de plus ici serait une ligne que les nouveaux templates obligent à
réécrire, et c'est précisément ce qu'on mesure.
"""

from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
SOURCE = HERE.parents[3] / "service"

# Chaque entrée est une chose que les nouveaux templates nomment autrement, avec la raison.
RENAMES = [
    # Un pool est une unité, et une unité tient dans un fichier par facette : les deux
    # bords d'un même pool -- ce qu'on appelle en processus et ce qu'on appelle au bout
    # d'un fil -- ne sont plus deux fichiers.
    ('#include "Tools_FunctionPoolBridges.hpp"',                 '#include "Tools_Pool.hpp"'),
    ('#include "Tools_FunctionPoolRemotes.hpp"',                 '#include "Tools_Pool.hpp"'),
    ('#include "PlayerModel_AttachmentFunctionPoolBridges.hpp"', '#include "PlayerModel_Pool.hpp"'),
    ('#include "PlayerModel_AttachmentFunctionPoolRemotes.hpp"', '#include "PlayerModel_Pool.hpp"'),

    # Et un pool se construit lui-même : il n'y a plus d'annuaire au niveau du modèle pour
    # dire quels pools existent, parce que le nom du pool le dit déjà.
    ('#include "Service_FunctionPools.hpp"',                     '#include "Tools_Pool.hpp"'),
    ('#include "Service_AttachmentFunctionPools.hpp"',           '#include "PlayerModel_Pool.hpp"'),
    ('Service::FunctionPools::tools()',                          'Tools::pool()'),
    ('Service::AttachmentFunctionPools::playerModel()',          'PlayerModel::pool()'),

    # Les définitions du modèle vivent avec le codec qui s'en sert, et sous son nom : tout
    # ce qui est du modèle entier et non d'une unité tient dans une seule portée.
    ('#include "Service_Definitions.hpp"',                       '#include "Service_Codec.hpp"'),
    ('Service::definitions()',                                   'Service::Codec::definitions()'),

    # Une unité est un namespace de premier rang, pas un sous-namespace du modèle : le
    # modèle nomme un assemblage, il n'enveloppe pas ce qu'il assemble.
    ('namespace Service::Tools',                                 'namespace Tools'),
    ('namespace Service::PlayerModel',                           'namespace PlayerModel'),
    ('Service::Tools::Remote',                                   'Tools::Remote'),
    ('Service::PlayerModel::Remote',                             'PlayerModel::Remote'),
    ('using namespace Service::Demo;',                           'using namespace Demo;'),

    # Un attachment a une portée à lui, au lieu d'un nom plat où la clé et le document
    # étaient collés pour ne pas se heurter.
    ('Attachments::Player_Property::',                           'Attachments::Player::property::'),
]

FILES = ["Tools_FunctionPoolBridges.cpp", "PlayerModel_AttachmentFunctionPoolBridges.cpp",
         "ServiceClient.cpp", "ServiceServer.cpp"]


def migrate(into: Path) -> dict:
    into.mkdir(parents=True, exist_ok=True)
    counts = {}
    for name in FILES:
        text = (SOURCE / name).read_text()
        touched = 0
        for old, new in RENAMES:
            if old in text:
                touched += text.count(old)
                text = text.replace(old, new)
        (into / name).write_text(text)
        counts[name] = touched
    return counts


if __name__ == "__main__":
    into = Path(sys.argv[1]) if len(sys.argv) > 1 else HERE / "migrated"
    counts = migrate(into)
    for name, n in counts.items():
        print(f"  {name:48} {n:2} substitution(s)")
