# runtime-proposed/dsviper — ce que la liaison Python ne porte pas encore

Le pendant de ce que `runtime-proposed/` contient pour le C++, et pour la même raison : ces
deux fichiers ne nomment aucun type d'un modèle, ne varient d'aucun modèle à l'autre, et
sont copiés dans chaque paquet rendu **parce que `dsviper` ne les porte pas**. Le jour où il
les portera, le code généré les importera au lieu de les recevoir.

| | pourquoi |
|---|---|
| `_proxy.py` | une classe générée enveloppe une `Value` ; l'égalité, le hachage, l'encodage et le passage dans les deux sens n'ont pas à être émis une fois par type. Et il faut un ancêtre : la liaison ne relie pas `ValueStructure` à `Value` à l'exécution, donc `isinstance(v, dsviper.Value)` est faux partout et reconnaître *nos* classes est le seul test qui tienne. |
| `_attachment.py` | `AttachmentProxy` — un attachment est un objet paramétré par trois valeurs — son identifiant, la classe de sa clé, celle de son document. Le pack Python écrit 188 lignes de template pour rendre 2 454 lignes ; il n'y a rien là-dedans qui nomme un type. |

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
sous-module — `dsviper.codegen` — que le code généré importerait sous ce nom.
