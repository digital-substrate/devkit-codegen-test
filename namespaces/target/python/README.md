# python — la référence, écrite depuis le modèle et depuis Python

Pas depuis le C++. Les décisions qui ont tenu là-bas tenaient *parce que* C++ — l'ADL, les
templates, les namespaces imbriqués — et Python n'a rien de tout cela. Ce qui change n'est
pas l'écriture, c'est la réponse.

```sh
namespaces/target/python/hand/check.py
```

**Et elle tourne.** Le C++ était vérifié par un compilateur contre des stubs recopiés ; ici
`dsviper` est importable, donc la référence s'exécute contre le vrai runtime. Une assertion
qui passe vaut mieux qu'une signature qui compile.

## Ce que Python donne gratuitement

**Un namespace est un paquet.** Le pack met tout dans un module et aplatit en
`Test_StructureS` ; ici `ModelA::Colour` est `topology.modela.Colour` et `ModelB::Colour`
est `topology.modelb.Colour`. Les deux coexistent sans qu'un nom bouge — ce qui a déclenché
tout ce chantier coûte, en Python, une arborescence de fichiers.

**Il n'y a pas de couche codec, et pas parce qu'on l'a factorisée.** En C++, le socle portait
`encode`/`decode` parce qu'une valeur C++ et une `Value` du runtime sont deux objets qu'il
faut faire passer l'un dans l'autre. Ici une valeur générée **est** une `Value` : la classe
lui donne des noms, elle ne la copie pas. Il n'y a pas de passage, donc pas de couche pour
le faire.

**La couche 2 disparaît dans les propriétés.** En C++ il fallait `Fields::Colour::r` pour
nommer un champ et `rPath()` pour l'adresser, deux artefacts en bijection. `colour.r` est
déjà les deux.

**Et il n'y a pas de `tag<T>`.** `type()` est une `classmethod` parce que l'appelant écrit
déjà le nom de la classe. Le tag n'existait en C++ que pour donner à la recherche par
argument un namespace où aller ; sans cette recherche, il n'a pas de raison d'être.

## Ce qui reste, et qui ressemble au C++

Le socle, réduit à `definitions()`. L'identité de l'unité dans le modèle — ses identifiants
d'exécution et ses descripteurs de type — pour la même raison qu'en C++ : plusieurs choses en
ont besoin et ce n'est pas de la sérialisation.

C'est tout. Le reste de la décomposition C++ n'a pas de contrepartie ici, et c'était la
question posée en ouvrant ce dossier.

## Ce qui n'est pas encore écrit

Les attachments, les pools, la base. La question ouverte pour eux est différente de celle du
C++ : là-bas il fallait une portée par attachment parce qu'une fonction ne peut pas être une
valeur. En Python elle peut, donc un attachment sera probablement un **objet** —
`modela.attachments.material.colour.get(...)` — et non une portée. C'est à écrire et à faire
tourner avant de l'affirmer.
