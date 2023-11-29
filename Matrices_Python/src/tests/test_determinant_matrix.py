import pytest
import settings
from src.Matrix import Matrix


def test_determinant_simple_2x2():
    a = Matrix([[1, 2],
                [3, 5]])
    assert a.det() == -1


def test_determinant_simple_1x1():
    a = Matrix([[5]])
    assert a.det() == 5


def test_determinant_zero():
    a = Matrix([[1, 2, 3],
                [3, 5, 11],
                [3, 6, 9]])
    assert a.det() == 0


def test_determinant_hard():
    a = Matrix([[1.325, 6.235, 7.32, 1.4],
                [22, 12.1, 6.31, 13],
                [1.23, 6.7, 5, 6.2],
                [4.567, 2.53, 1, 9.53]])
    assert (abs(a.det() - 2242.663664) < 1e-6) is True


def test_determinant_error():
    with pytest.raises(Exception, match=r".+ determinant .+"):
        a = Matrix([[2, 3, 1],
                    [12, 1, 7]])
        a.det()
