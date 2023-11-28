from __future__ import annotations
from typing import List, Union
import copy


class Matrix:
    __matrix: List[List[float]]
    __rows: int
    __columns: int

    def __init__(self, matrix: List[List[float]]) -> None:
        self.__matrix = matrix
        self.__rows = len(matrix)
        self.__columns = len(matrix[0])

    @property
    def rows(self) -> int:
        return self.__rows

    @property
    def columns(self) -> int:
        return self.__columns

    @property
    def matrix(self) -> List[List[float]]:
        return self.__matrix

    def __add__(self, other: Matrix) -> Matrix:
        result = copy.deepcopy(Matrix(self.matrix))
        result.sum_matrix(other)
        return result

    def __iadd__(self, other: Matrix) -> Matrix:
        self.sum_matrix(other)
        return self

    def __sub__(self, other: Matrix) -> Matrix:
        result = copy.deepcopy(Matrix(self.matrix))
        result.sub_matrix(other)
        return result

    def __isub__(self, other: Matrix) -> Matrix:
        self.sub_matrix(other)
        return self

    def __mul__(self, other: Union[Matrix, float]) -> Matrix:
        result = copy.deepcopy(Matrix(self.matrix))
        if isinstance(other, Matrix):
            result.mul_matrix(other)
        else:
            result.mul_number(other)
        return result

    def __imul__(self, other: Union[Matrix, float]) -> Matrix:
        if isinstance(other, Matrix):
            self.mul_matrix(other)
        else:
            self.mul_number(other)
        return self

    def __str__(self) -> str:
        res: str = ''
        for row in self.matrix:
            res += str(row) + '\n'
        return res

    def __eq__(self, other: Matrix) -> bool:
        return self.eq_matrix(other)

    def sum_matrix(self, second_matrix: Matrix) -> None:
        if self.rows != second_matrix.rows or self.columns != second_matrix.columns:
            raise Exception("Matrices can only be added if the dimensions are the same")

        for i in range(self.rows):
            for j in range(self.columns):
                self.matrix[i][j] += second_matrix.matrix[i][j]

    def sub_matrix(self, second_matrix: Matrix) -> None:
        if self.rows != second_matrix.rows or self.columns != second_matrix.columns:
            raise Exception("Matrices can only be subtracted if the dimensions are the same")

        for i in range(self.rows):
            for j in range(self.columns):
                self.matrix[i][j] -= second_matrix.matrix[i][j]

    def eq_matrix(self, second_matrix: Matrix) -> bool:
        if self.rows != second_matrix.rows or self.columns != second_matrix.columns:
            return False

        for i in range(self.rows):
            for j in range(self.columns):
                if abs(self.matrix[i][j] - second_matrix.matrix[i][j]) > 1e-6:
                    return False

        return True

    def mul_matrix(self, second_matrix: Matrix) -> None:
        if self.columns != second_matrix.rows:
            raise Exception("Only (m, k) and (k, n) dimension matrices can be multiplied")

        res_matrix: List[List[float]] = [[0 for _ in range(second_matrix.columns)] for _ in range(self.rows)]

        for i in range(self.rows):
            for j in range(second_matrix.columns):
                for k in range(self.columns):
                    res_matrix[i][j] += self.matrix[i][k] * second_matrix.matrix[k][j]

        self.__init__(res_matrix)

    def mul_number(self, number: float) -> None:
        for i in range(self.rows):
            for j in range(self.columns):
                self.matrix[i][j] *= number

    def transpose(self) -> Matrix:
        res_matrix: List[List[float]] = [[0 for _ in range(self.rows)] for _ in range(self.columns)]

        for i in range(self.columns):
            for j in range(self.rows):
                res_matrix[i][j] = self.matrix[j][i]

        return Matrix(res_matrix)

    def det(self) -> float:
        if self.rows != self.columns:
            raise Exception("The determinant can only be calculated for a square matrix")

        return self.__recursive_det(self)

    def calc_complements(self) -> Matrix:
        if self.rows != self.columns:
            raise Exception("The algebraic complement matrix can only be found for a square matrix")

        res_matrix: List[List[float]] = [[0 for _ in range(self.columns)] for _ in range(self.rows)]

        if self.rows == 1:
            res_matrix[0][0] = 1
        else:
            for i in range(self.rows):
                for j in range(self.columns):
                    matrix_copy = self.__matrix_cut_copy(self, i, j)
                    res_matrix[i][j] = ((-1) ** (i + j)) * self.__recursive_det(matrix_copy)

        return Matrix(res_matrix)

    def inverse_matrix(self) -> Matrix:
        if self.rows != self.columns:
            raise Exception("The inverse matrix can only be found for a square matrix")

        if self.det() == 0:
            raise Exception("The inverse matrix can only be found in the case of a non-zero determinant")

        return (self.calc_complements() * (1 / self.det())).transpose()

    def __recursive_det(self, a: Matrix) -> float:
        if a.rows == 1:
            return a.matrix[0][0]
        if a.rows == 2:
            return a.matrix[0][0] * a.matrix[1][1] - a.matrix[0][1] * a.matrix[1][0]

        res: float = 0
        for i in range(a.rows):
            copy_matrix = self.__matrix_cut_copy(a, 0, i)
            res += ((-1) ** i) * a.matrix[0][i] * self.__recursive_det(copy_matrix)

        return res

    @staticmethod
    def __matrix_cut_copy(a: Matrix, skip_row: int, skip_column: int) -> Matrix:
        res_matrix: List[List[float]] = [[0 for _ in range(a.rows - 1)] for _ in range(a.columns - 1)]

        i_new: int = 0
        for i in range(a.rows):
            if i == skip_row:
                continue
            j_new: int = 0
            for j in range(a.columns):
                if j == skip_column:
                    continue
                res_matrix[i_new][j_new] = a.matrix[i][j]
                j_new += 1
            i_new += 1

        return Matrix(res_matrix)
