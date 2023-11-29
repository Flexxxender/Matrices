import pytest
import settings
from src.Matrix import Matrix


def test_sum_simple_int():
    a = Matrix([[1, 2],
                [3, 5]])
    b = Matrix([[2, 3],
                [12, 1]])
    a += b
    assert a == Matrix([[3, 5],
                        [15, 6]])


def test_sum_simple_float():
    a = Matrix([[1.324, 2.42],
                [3.435, 5.421]])
    b = Matrix([[2.43, 3.21],
                [12.1, 1.32]])
    assert (a + b) == Matrix([[3.754, 5.63],
                              [15.535, 6.741]])


def test_sum_1x1_int():
    a = Matrix([[1]])
    b = Matrix([[2]])
    assert (a + b) == Matrix([[3]])


def test_sum_1x1_float():
    a = Matrix([[1.324]])
    b = Matrix([[2.43]])
    assert (a + b) == Matrix([[3.754]])


def test_sum_error():
    with pytest.raises(Exception, match=r".+ added .+"):
        a = Matrix([[1, 2]])
        b = Matrix([[2, 3],
                    [12, 1]])
        c = a + b