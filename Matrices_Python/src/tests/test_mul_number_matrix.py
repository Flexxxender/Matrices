import pytest
import settings
from src.MatrixClass import Matrix


def test_mul_number_simple():
    a = Matrix([[1, 2],
                [3, 5]])
    assert (a * 2) == Matrix([[2, 4],
                              [6, 10]])


def test_mul_number_1x1():
    a = Matrix([[4]])
    assert (a * 3) == Matrix([[12]])


def test_mul_number_0():
    a = Matrix([[1, 2, 3],
                [5, 6, 7]])
    assert (a * 0) == Matrix([[0, 0, 0],
                              [0, 0, 0]])


def test_mul_number_negative():
    a = Matrix([[1, 2],
                [3, 5]])
    assert (a * (-2)) == Matrix([[-2, -4],
                                 [-6, -10]])


def test_mul_number_float():
    a = Matrix([[1, 2],
                [3, 5]])
    assert (a * (-2.23)) == Matrix([[-2.23, -4.46],
                                    [-6.69, -11.15]])
