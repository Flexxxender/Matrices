import pytest
import settings
from src.Matrix import Matrix


def test_rows_setter_greater():
    a = Matrix([[1, 2],
                [3, 4],
                [3, 5]])

    a.rows = 5
    assert a.rows == 5
    assert a.columns == 2
    assert a.matrix == [[1, 2],
                        [3, 4],
                        [3, 5],
                        [0, 0],
                        [0, 0]]


def test_rows_setter_lower():
    a = Matrix([[1, 2],
                [3, 4],
                [3, 5]])

    a.rows = 2
    assert a.rows == 2
    assert a.columns == 2
    assert a.matrix == [[1, 2],
                        [3, 4]]


def test_columns_setter_greater():
    a = Matrix([[1, 2],
                [3, 4],
                [3, 5]])

    a.columns = 4
    assert a.rows == 3
    assert a.columns == 4
    assert a.matrix == [[1, 2, 0, 0],
                        [3, 4, 0, 0],
                        [3, 5, 0, 0]]


def test_columns_setter_lower():
    a = Matrix([[1, 2, 1],
                [3, 4, 4],
                [3, 5, 7]])

    a.columns = 2
    assert a.rows == 3
    assert a.columns == 2
    assert a.matrix == [[1, 2],
                        [3, 4],
                        [3, 5]]


def test_together_setter_lower():
    a = Matrix([[1, 2, 1],
                [3, 4, 4],
                [3, 5, 7]])

    a.columns = 2
    a.rows = 2
    assert a.rows == 2
    assert a.columns == 2
    assert a.matrix == [[1, 2],
                        [3, 4]]


def test_together_setter_greater():
    a = Matrix([[1, 2],
                [3, 4]])

    a.columns = 3
    a.rows = 3
    assert a.rows == 3
    assert a.columns == 3
    assert a.matrix == [[1, 2, 0],
                        [3, 4, 0],
                        [0, 0, 0]]


def test_rows_setter_error():
    with pytest.raises(Exception, match=r".+ greater .+"):
        a = Matrix([[1, 2],
                    [3, 4]])
        a.rows = 0


def test_columns_setter_error():
    with pytest.raises(Exception, match=r".+ greater .+"):
        a = Matrix([[1, 2],
                    [3, 4]])
        a.columns = -2
