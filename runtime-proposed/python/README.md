# runtime-proposed/dsviper_codegen — ce que la liaison Python ne porte pas encore

Le pendant de ce que `runtime-proposed/` contient pour le C++, et pour la même raison : ces
deux fichiers ne nomment aucun type d'un modèle, ne varient d'aucun modèle à l'autre, et
sont copiés dans chaque paquet rendu **parce que `dsviper` ne les porte pas**. Le jour où il
les portera, le code généré les importera au lieu de les recevoir.

| | pourquoi |
|---|---|
| `proxy.py` | une classe générée enveloppe une `Value` ; l'égalité, le hachage, l'encodage et le passage dans les deux sens n'ont pas à être émis une fois par type. Et il faut un ancêtre : la liaison ne relie pas `ValueStructure` à `Value` à l'exécution, donc `isinstance(v, dsviper.Value)` est faux partout et reconnaître *nos* classes est le seul test qui tienne. |
| `attachment.py` | `AttachmentProxy` — un attachment est un objet paramétré par trois valeurs — son identifiant, la classe de sa clé, celle de son document. Le pack Python écrit 188 lignes de template pour rendre 2 454 lignes ; il n'y a rien là-dedans qui nomme un type. |

## Les noms, vérifiés contre ceux de la liaison

Ces fichiers ont vocation à entrer dans `dsviper`, donc chaque nom qu'ils exposent doit être
libre là-bas. Sur dix, un ne l'était pas : `Attachment`. La liaison en a un, et c'est le
*descripteur* — un identifiant, un type de clé, un type de document. Le nôtre est l'accesseur
typé qui le résout, donc `AttachmentProxy`, du même mot que `Proxy` qui est l'accesseur typé
d'une `Value`.

Tant que les deux vivent dans des modules différents la confusion n'est que de lecture ; dans
un même module, deux `Attachment` s'écrasent, et c'est le dernier qui gagne sans un mot.

**Et ils n'iront pas à la racine.** `wrap`, `unwrap`, `register` sont des mots trop généraux
pour le premier niveau d'un paquet qui expose déjà deux cents noms. Leur place est un
sous-paquet — `dsviper.codegen` — que le code généré importerait sous ce nom.

## En attendant, et la forme de l'attente

**`dsviper` n'est pas touché.** Ce paquet est déposé dans chaque paquet rendu sous `_codegen`
par `render-python.py`, et le code généré écrit :

```python
from .._codegen import AttachmentProxy, Mapping, Ordered, Proxy, Sequence
from .._codegen import register, unwrap, wrap
```

Le jour où la liaison le portera, ce sera `from dsviper.codegen import …` — **une ligne dans
chacun des trois templates**, et pas un autre octet. C'est pourquoi l'import est déjà un
paquet et non trois modules séparés : la forme de l'import est celle de la destination, et
seule l'origine changera.

`container.py` complète la liste : les trois vues -- une suite, une correspondance, un
ordonné -- qui remplacent la classe par forme de conteneur que le pack génère.
