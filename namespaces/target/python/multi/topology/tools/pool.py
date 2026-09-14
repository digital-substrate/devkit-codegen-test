# A POOL IS A UNIT, and this one imports nothing: Tools names no namespaced type.
# `topology.tools.Tools`, not `topology.function_pools.Tools`.

import dsviper


class Tools:
    def __init__(self, pool: dsviper.FunctionPool): ...
    def reset(self) -> None: ...
    def add(self, a: int, b: int) -> int: ...
