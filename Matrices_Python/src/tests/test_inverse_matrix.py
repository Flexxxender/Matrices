import pytest
import settings
from src.MatrixClass import Matrix


def test_inverse_simple():
    a = Matrix([[-1, 2, 5],
                [3, 4, 6],
                [-8, 2, 12]])
    assert a.inverse_matrix() == Matrix([[-2.571428, 1, 0.571429],
                                         [6, -2, -1.5],
                                         [-2.714286, 1, 0.714286]])


def test_inverse_1x1():
    a = Matrix([[4]])
    assert a.inverse_matrix() == Matrix([[0.25]])


def test_inverse_error1():
    with pytest.raises(Exception, match=r".+ square .+"):
        a = Matrix([[2, 3, 1],
                    [12, 1, 7]])
        a.inverse_matrix()


def test_inverse_error2():
    with pytest.raises(Exception, match=r".+ non-zero .+"):
        a = Matrix([[1, 1, 1],
                    [2, 3, 4],
                    [11, 11, 11]])
        a.inverse_matrix()
