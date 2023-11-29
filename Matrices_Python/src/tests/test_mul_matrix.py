import pytest
import settings
from src.Matrix import Matrix


def test_mul_square_int():
    a = Matrix([[1, 2],
                [3, 5]])
    b = Matrix([[2, 3],
                [12, 1]])
    a *= b
    assert a == Matrix([[26, 5],
                        [66, 14]])


def test_mul_square_float():
    a = Matrix([[1.324, 2.42],
                [3.435, 5.421]])
    b = Matrix([[2.43, 3.21],
                [12.1, 1.32]])
    assert (a * b) == Matrix([[32.49932, 7.44444],
                              [73.94115, 18.18207]])


def test_mul_non_square_int():
    a = Matrix([[1, 2],
                [3, 5]])
    b = Matrix([[2, 3, 5],
                [12, 1, 7]])
    c = (a * b).eq_matrix(Matrix([[26, 5, 19], [66, 14, 50]]))
    assert c == True


def test_mul_non_square_float():
    a = Matrix([[1.23, 2.64],
                [3.1, 5.01]])
    b = Matrix([[2.21, 3.1, 45],
                [12.33, 1.1, 7]])
    c = (a * b).eq_matrix(Matrix([[35.2695, 6.717, 73.83],
                                  [68.6243, 15.121, 174.57]]))
    assert c == True


def test_mul_1x1_int():
    a = Matrix([[1]])
    b = Matrix([[2]])
    assert (a * b) == Matrix([[2]])


def test_mul_error():
    with pytest.raises(Exception, match=r".+ can be multiplied"):
        a = Matrix([[1.324, 2.42, 43.12]])
        b = Matrix([[2.43, 3.21],
                    [12.1, 1.32]])
        c = a * b
