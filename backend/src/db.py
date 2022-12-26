# File:        ttb.py
# Created:     02 Oct 2022
# SPDX-License-Identifier: NONE

from os import PathLike
import csv


class Courses:
    """All known courses in the database."""

    def __init__(self, path: PathLike):
        with open(path) as data:
            reader = csv.reader(data)
            self.data = list(reader)

    @property
    def all(self) -> list[str]:
        """Return all the course data"""
        return self.data
