import pytest
import settings
from src.Matrix import Matrix


def test_sub_simple_int():
    a = Matrix([[1, 2],
                [3, 5]])
    b = Matrix([[2, 3],
                [12, 1]])
    a -= b
    assert a == Matrix([[-1, -1],
                        [-9, 4]])


def test_sub_simple_float():
    a = Matrix([[1.324, 2.42],
                [3.435, 5.421]])
    b = Matrix([[2.43, 3.21],
                [12.1, 1.32]])
    assert (a - b) == Matrix([[-1.106, -0.79],
                              [-8.665, 4.101]])


def test_sub_1x1_int():
    a = Matrix([[1]])
    b = Matrix([[2]])
    assert (a - b) == Matrix([[-1]])


def test_sub_1x1_float():
    a = Matrix([[1.324]])
    b = Matrix([[2.43]])
    assert (a - b) == Matrix([[-1.106]])


def test_sub_error():
    with pytest.raises(Exception, match=r".+ subtracted .+"):
        a = Matrix([[1, 2]])
        b = Matrix([[2, 3],
                    [12, 1]])
        c = a - b
