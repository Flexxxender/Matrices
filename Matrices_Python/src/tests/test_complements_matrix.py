import pytest
import settings
from src.MatrixClass import Matrix


def test_complements_simple():
    a = Matrix([[-1, 2, 5],
                [3, 4, 6],
                [-8, 2, 12]])
    assert a.calc_complements() == Matrix([[36, -84, 38],
                                         [-14, 28, -14],
                                         [-8, 21, -10]])

def test_complements_1x1():
    a = Matrix([[4]])
    assert a.calc_complements() == Matrix([[1]])


def test_complements_error():
    with pytest.raises(Exception, match=r".+ square .+"):
        a = Matrix([[2, 3, 1],
                    [12, 1, 7]])
        a.calc_complements()



