"""Tools — un pool, et une unité à part entière.

UN POOL SE CONSOMME, IL NE SE SERT PAS. En C++ un pool a deux bords : les fonctions que le
développeur écrit, et les `Viper::Function` qui les exposent au monde dynamique. Ici
`dsviper` expose de quoi interroger un pool et l'appeler, mais rien pour en construire un.
Donc il n'y a qu'un bord à écrire, et c'est le bord client — la moitié qui manque n'est pas
une omission du pack, c'est une absence du runtime.

ET LE POOL EST UNE UNITÉ, donc un module. Le pack met tous les pools d'un modèle dans un
`function_pools.py` unique et les distingue par le nom de la classe ; ici le nom du module
est déjà le nom du pool.
"""

from __future__ import annotations

import dsviper


class Pool:
    """Le pool, tenu en main — un `dsviper.FunctionPool` déjà obtenu.

    LES MÉTHODES SONT ÉCRITES, PAS DÉDUITES. `pool.funcs["add"]` marche sans qu'on génère
    quoi que ce soit, et c'est exactement pourquoi il faut les écrire : sans elles, le nom
    d'une fonction du modèle n'est qu'une chaîne, une faute de frappe n'est vue qu'à
    l'exécution, et rien ne dit ce que l'appel prend ni ce qu'il rend.
    """

    __slots__ = ("_funcs",)

    NAME = "Tools"
    UUID = dsviper.ValueUUId.create("17e63428-03e1-41d7-ad9d-60c5665bbd66")

    def __init__(self, pool: dsviper.FunctionPool):
        self._funcs = pool.funcs

    def reset(self) -> None:
        self._funcs["reset"]()

    def add(self, a: int, b: int) -> int:
        return self._funcs["add"](a, b)


class Remote:
    """Le même pool, vu d'un client.

    LE SEUL ÉCART AVEC `Pool` EST L'OBTENTION DES FONCTIONS, et il tient en une ligne :
    d'un côté un pool qu'on a en main, de l'autre un service qu'on interroge par son nom.
    Les corps sont identiques — ce qui traverse le fil, c'est le format, pas l'appel.
    """

    __slots__ = ("_funcs",)

    def __init__(self, service: dsviper.ServiceRemote):
        self._funcs = service.function_pool_funcs(Pool.NAME)

    def is_available(self) -> bool:
        return self._funcs is not None

    def reset(self) -> None:
        self._funcs["reset"]()

    def add(self, a: int, b: int) -> int:
        return self._funcs["add"](a, b)
