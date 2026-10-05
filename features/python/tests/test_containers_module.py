# Copyright (c) Digital Substrate 2026, All rights reserved.
"""The containers module exports its declared classes only."""

import typing
import unittest

import features.containers


class TestStarImport(unittest.TestCase):
    """`from pkg.containers import *` brings the declared containers, and nothing that shadows."""

    def test_star_import_keeps_typing(self):
        namespace: dict[str, object] = {}
        exec("from typing import Optional, Mapping\nfrom features.containers import *", namespace)
        self.assertIs(namespace["Optional"], typing.Optional)
        self.assertIs(namespace["Mapping"], typing.Mapping)

    def test_all_lists_the_declared_classes(self):
        exported = features.containers.__all__
        self.assertIn("Map_of_int8_to_string", exported)
        self.assertTrue(all("_of_" in name for name in exported))

    def test_the_runtime_bases_stay_reachable(self):
        self.assertTrue(hasattr(features.containers, "Optional"))


if __name__ == "__main__":
    unittest.main()
