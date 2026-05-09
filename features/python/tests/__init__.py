"""
Test suite for the Kibo-generated `features` Python package.

These tests validate the generated code from `all.dsm` against the dsviper
runtime. Run them from `features/python/`:

    ./run_test.sh
    # or, single module:
    python3 -m unittest tests.test_database
"""

import sys
import os

features_python_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if features_python_path not in sys.path:
    sys.path.insert(0, features_python_path)

import dsviper
from features import definitions as md


def create_memory_database() -> dsviper.Database:
    """Create an in-memory database with Exp definitions."""
    db = dsviper.Database.create_in_memory()
    db.extend_definitions(md.definitions())
    return db


def create_commit_engine(database: dsviper.Database) -> dsviper.CommitEngine:
    """Create a commit engine for transactional operations."""
    return dsviper.CommitEngine(database)
