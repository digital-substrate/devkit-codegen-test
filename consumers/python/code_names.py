"""The names Python code uses -- identifiers, attributes, imported modules -- one per line, read by
ast: comments and docstrings, which may point to the other usage, are not code.

    code_names.py FILE...
"""

import ast
import sys

names = set()
for path in sys.argv[1:]:
    for node in ast.walk(ast.parse(open(path).read(), path)):
        if isinstance(node, ast.Name):
            names.add(node.id)
        elif isinstance(node, ast.Attribute):
            names.add(node.attr)
        elif isinstance(node, ast.alias):
            names.update(node.name.split("."))
        elif isinstance(node, ast.ImportFrom) and node.module:
            names.update(node.module.split("."))
print("\n".join(sorted(names)))
