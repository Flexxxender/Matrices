import pytest
import settings
from src.Matrix import Matrix


def test_matrix_constructor():
    a = Matrix([[1, 2],
                [3, 4],
                [3, 5]])
    assert a.rows == 3
    assert a.columns == 2
    assert a.matrix == [[1, 2],
                        [3, 4],
                        [3, 5]]


def test_default_constructor():
    a = Matrix()
    assert a.rows == 1
    assert a.columns == 1
    assert a.matrix == [[0]]


def test_rows_cols_constructor():
    a = Matrix(3, 2)
    assert a.rows == 3
    assert a.columns == 2
    assert a.matrix == [[0, 0],
                        [0, 0],
                        [0, 0]]


def test_rows_cols_constructor_error():
    with pytest.raises(Exception, match=r".+ greater .+"):
        a = Matrix(-1, -3)


def test_other_constructor():
    a = Matrix([[1, 2],
                [3, 4],
                [3, 5]])
    b = Matrix(a)
    assert b.rows == 3
    assert b.columns == 2
    assert b.matrix == [[1, 2],
                        [3, 4],
                        [3, 5]]
