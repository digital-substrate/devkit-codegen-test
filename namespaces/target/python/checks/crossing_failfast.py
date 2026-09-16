#!/usr/bin/env python3
"""Le fail-fast, éprouvé sur le rendu.

UN PROXY NE DÉTIENT RIEN : c'est une boîte vide devant une `Value`. Toute écriture atteint
donc le runtime, qui lève son exception typée -- le fail-fast est hérité, pas implémenté. Ce
qu'il faut vérifier n'est pas qu'on l'a écrit, mais que rien dans la couche générée ne
l'intercepte ni ne le contourne.

ET LES DEUX SORTES D'ERREUR COMPTENT. `ViperError` vient du runtime, quand une valeur du
mauvais type l'atteint. `TypeError` vient du code généré, quand un constructeur refuse une
`Value` qui n'est pas la sienne -- avant même qu'une écriture ait lieu. Le pack pin la seconde
dans `test_fail_fast.py` : ce sont des `raise` et non des `assert`, donc le contrat tient
aussi sous `python -O`, où les assertions disparaissent.
"""
import sys
from pathlib import Path

package = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else Path.cwd()
sys.path.insert(0, str(package))

import dsviper                                                      # noqa: E402

from crossing import core, parts, definitions                       # noqa: E402
from crossing.core import attachments as a                          # noqa: E402
from crossing._codegen import proxy, wrap                           # noqa: E402

ok = True
mutating = dsviper.CommitMutableState(dsviper.CommitState(definitions())).attachment_mutating()


def refuses(label, fn):
    global ok
    try:
        fn()
        print(f"  ÉCHEC {label} -- passe sans erreur")
        ok = False
    except (dsviper.ViperError, TypeError):
        print(f"  ok   {label}")


refuses("un champ refuse une chaîne là où un nombre est attendu",
        lambda: setattr(core.Colour(), "r", "rouge"))
refuses("un champ refuse la Colour d'une autre unité",
        lambda: setattr(core.Defaults(), "f_colour", parts.Colour()))
refuses("un conteneur refuse un élément du mauvais type",
        lambda: setattr(core.Bag(), "tints", [parts.Colour()]))
refuses("une clé refuse l'identifiant d'un autre concept",
        lambda: core.ThingKey(core.OtherKey.create().value))
refuses("un attachment refuse une clé d'un autre concept",
        lambda: a.Thing.colour.set(mutating, core.OtherKey.create(), core.Colour()))
refuses("un attachment refuse un document du mauvais type",
        lambda: a.Thing.colour.set(mutating, core.ThingKey.create(), parts.Colour()))

# ET LE SEUL REPLI QUE J'AVAIS INTRODUIT. `wrap` rendait la valeur nue quand un type n'avait
# pas de classe enregistrée -- un mensonge contre l'annotation, que le typage ne peut pas
# rattraper et qui se découvre bien plus loin, sur un attribut absent.
saved = proxy._CLASSES.pop(core.data.COLOUR.encoded())
refuses("wrap échoue si une unité n'est pas importée, au lieu de rendre la valeur nue",
        lambda: wrap(core.Colour(r=1, g=2, b=3).value))
proxy._CLASSES[core.data.COLOUR.encoded()] = saved

raise SystemExit(0 if ok else 1)
