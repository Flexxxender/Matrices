import pytest
import settings
from src.Matrix import Matrix


def test_transpose_simple():
    a = Matrix([[1, 2],
                [3, 5]])
    assert a.transpose() == Matrix([[1, 3],
                                    [2, 5]])


def test_transpose_1x1():
    a = Matrix([[1]])
    assert a.transpose() == Matrix([[1]])


def test_transpose_non_square():
    a = Matrix([[1, 2],
                [3, 5],
                [5, 6]])
    assert a.transpose() == Matrix([[1, 3, 5],
                                    [2, 5, 6]])
