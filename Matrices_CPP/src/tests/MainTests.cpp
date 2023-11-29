#include <gtest/gtest.h>

#include "../Matrix.h"

TEST(MatrixTest, DefaultConstructor) {
  Matrix matrix;
  ASSERT_EQ(matrix.GetRows(), 1);
  ASSERT_EQ(matrix.GetCols(), 1);
  ASSERT_EQ(matrix(0, 0), 0);
}

TEST(MatrixTest, Constructor) {
  Matrix matrix(3, 4);
  ASSERT_EQ(matrix.GetRows(), 3);
  ASSERT_EQ(matrix.GetCols(), 4);

  for (int i = 0; i < matrix.GetRows(); i++)
    for (int j = 0; j < matrix.GetCols(); j++) ASSERT_EQ(matrix(i, j), 0);

  ASSERT_THROW(Matrix matrix2(0, 4), std::logic_error);
  ASSERT_THROW(Matrix matrix3(3, -1), std::logic_error);
}

TEST(MatrixTest, MoveConstructor) {
  Matrix A(5, 5);
  Matrix B(std::move(A));
  EXPECT_EQ(5, B.GetRows());
  EXPECT_EQ(5, B.GetCols());
  EXPECT_EQ(0, A.GetRows());
  EXPECT_EQ(0, A.GetCols());
}

TEST(MatrixTest, CopyConstructor) {
  Matrix A(3, 4);
  Matrix B(A);
  EXPECT_EQ(3, B.GetRows());
  EXPECT_EQ(4, B.GetCols());
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, CalcComplementsSimple) {
  Matrix A(3, 3);
  A(0, 0) = -1;
  A(0, 1) = 2;
  A(0, 2) = 5;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(1, 2) = 6;
  A(2, 0) = -8;
  A(2, 1) = 2;
  A(2, 2) = 12;

  Matrix B(3, 3);
  B(0, 0) = 36;
  B(0, 1) = -84;
  B(0, 2) = 38;
  B(1, 0) = -14;
  B(1, 1) = 28;
  B(1, 2) = -14;
  B(2, 0) = -8;
  B(2, 1) = 21;
  B(2, 2) = -10;

  EXPECT_EQ(1, A.CalcComplements() == B);
}

TEST(MatrixTest, Complements1x1) {
  Matrix A = Matrix(1, 1);
  A(0, 0) = 4;

  Matrix B = Matrix(1, 1);
  B(0, 0) = 1;
  EXPECT_EQ(1, A.CalcComplements() == B);
}

TEST(MatrixTest, ComplementsError) {
  Matrix A = Matrix(3, 2);
  ASSERT_THROW(A.CalcComplements(), std::logic_error);
}

TEST(MatrixTest, Determinant2x2) {
  Matrix A = Matrix(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  EXPECT_EQ(-1, A.Determinant());
}

TEST(MatrixTest, Determinant1x1) {
  Matrix A = Matrix(1, 1);
  A(0, 0) = 5;

  EXPECT_EQ(5, A.Determinant());
}

TEST(MatrixTest, DeterminantZero) {
  Matrix A = Matrix(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 3;
  A(1, 1) = 5;
  A(1, 2) = 11;
  A(2, 0) = 3;
  A(2, 1) = 6;
  A(2, 2) = 9;

  EXPECT_EQ(0, A.Determinant());
}

TEST(MatrixTest, DeterminantHard) {
  Matrix A = Matrix(4, 4);
  A(0, 0) = 1.325;
  A(0, 1) = 6.235;
  A(0, 2) = 7.32;
  A(0, 3) = 1.4;

  A(1, 0) = 22;
  A(1, 1) = 12.1;
  A(1, 2) = 6.31;
  A(1, 3) = 13;

  A(2, 0) = 1.23;
  A(2, 1) = 6.7;
  A(2, 2) = 5;
  A(2, 3) = 6.2;

  A(3, 0) = 4.567;
  A(3, 1) = 2.53;
  A(3, 2) = 1;
  A(3, 3) = 9.53;

  EXPECT_EQ(1, abs(A.Determinant() - 2242.663664) < 1e-6);
}

TEST(MatrixTest, DeterminantError) {
  Matrix A = Matrix(3, 2);
  ASSERT_THROW(A.Determinant(), std::logic_error);
}

TEST(MatrixTest, InverseMatrixSimple) {
  Matrix A(3, 3);
  A(0, 0) = -1;
  A(0, 1) = 2;
  A(0, 2) = 5;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(1, 2) = 6;
  A(2, 0) = -8;
  A(2, 1) = 2;
  A(2, 2) = 12;

  Matrix B(3, 3);
  B(0, 0) = -2.571428;
  B(0, 1) = 1;
  B(0, 2) = 0.571429;
  B(1, 0) = 6;
  B(1, 1) = -2;
  B(1, 2) = -1.5;
  B(2, 0) = -2.714286;
  B(2, 1) = 1;
  B(2, 2) = 0.714286;

  EXPECT_EQ(1, A.InverseMatrix() == B);
}

TEST(MatrixTest, InverseMatrix1x1) {
  Matrix A = Matrix(1, 1);
  A(0, 0) = 4;

  Matrix B = Matrix(1, 1);
  B(0, 0) = 0.25;
  EXPECT_EQ(1, A.InverseMatrix() == B);
}

TEST(MatrixTest, InverseMatrixError1) {
  Matrix A = Matrix(3, 2);
  ASSERT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, InverseMatrixError2) {
  Matrix A = Matrix(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 1;
  A(0, 2) = 1;
  A(1, 0) = 2;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 11;
  A(2, 1) = 11;
  A(2, 2) = 11;
  ASSERT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, MulMatrixSquareInt) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 2);
  B(0, 0) = 2;
  B(0, 1) = 3;
  B(1, 0) = 12;
  B(1, 1) = 1;

  Matrix C(2, 2);
  C(0, 0) = 26;
  C(0, 1) = 5;
  C(1, 0) = 66;
  C(1, 1) = 14;

  EXPECT_EQ(1, (A * B) == C);
}

TEST(MatrixTest, MulMatrixSquareFloat) {
  Matrix A(2, 2);
  A(0, 0) = 1.324;
  A(0, 1) = 2.42;
  A(1, 0) = 3.435;
  A(1, 1) = 5.421;

  Matrix B(2, 2);
  B(0, 0) = 2.43;
  B(0, 1) = 3.21;
  B(1, 0) = 12.1;
  B(1, 1) = 1.32;

  Matrix C(2, 2);
  C(0, 0) = 32.49932;
  C(0, 1) = 7.44444;
  C(1, 0) = 73.94115;
  C(1, 1) = 18.18207;

  A *= B;
  EXPECT_EQ(1, A == C);
}

TEST(MatrixTest, MulMatrixNonSquareInt) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 3);
  B(0, 0) = 2;
  B(0, 1) = 3;
  B(0, 2) = 5;
  B(1, 0) = 12;
  B(1, 1) = 1;
  B(1, 2) = 7;

  Matrix C(2, 3);
  C(0, 0) = 26;
  C(0, 1) = 5;
  C(0, 2) = 19;
  C(1, 0) = 66;
  C(1, 1) = 14;
  C(1, 2) = 50;

  EXPECT_EQ(1, (A * B) == C);
}

TEST(MatrixTest, MulMatrixNonSquareFloat) {
  Matrix A(2, 2);
  A(0, 0) = 1.23;
  A(0, 1) = 2.64;
  A(1, 0) = 3.1;
  A(1, 1) = 5.01;

  Matrix B(2, 3);
  B(0, 0) = 2.21;
  B(0, 1) = 3.1;
  B(0, 2) = 45;
  B(1, 0) = 12.33;
  B(1, 1) = 1.1;
  B(1, 2) = 7;

  Matrix C(2, 3);
  C(0, 0) = 35.2695;
  C(0, 1) = 6.717;
  C(0, 2) = 73.83;
  C(1, 0) = 68.6243;
  C(1, 1) = 15.121;
  C(1, 2) = 174.57;

  EXPECT_EQ(1, (A * B) == C);
}

TEST(MatrixTest, MulMatrix1x1) {
  Matrix A = Matrix(1, 1);
  A(0, 0) = 1;

  Matrix B = Matrix(1, 1);
  B(0, 0) = 2;

  Matrix C = Matrix(1, 1);
  C(0, 0) = 2;

  EXPECT_EQ(1, (A * B) == C);
}

TEST(MatrixTest, MulMatrixError) {
  Matrix A(1, 3);
  A(0, 0) = -1;
  A(0, 1) = 2;
  A(0, 2) = 5;

  Matrix B(2, 2);
  B(0, 0) = 36;
  B(0, 1) = -84;
  B(1, 0) = -14;
  B(1, 1) = 28;

  ASSERT_THROW(A * B, std::logic_error);
}

TEST(MatrixTest, MulNumberSimple) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 2);
  B(0, 0) = 2;
  B(0, 1) = 4;
  B(1, 0) = 6;
  B(1, 1) = 10;

  A *= 2;
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, MulNumber1x1) {
  Matrix A(1, 1);
  A(0, 0) = 4;

  Matrix B(1, 1);
  B(0, 0) = 12;

  EXPECT_EQ(1, A * 3 == B);
}

TEST(MatrixTest, MulNumberZero) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 2);

  EXPECT_EQ(1, A * 0 == B);
}

TEST(MatrixTest, MulNumberNegative) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 2);
  B(0, 0) = -2;
  B(0, 1) = -4;
  B(1, 0) = -6;
  B(1, 1) = -10;

  EXPECT_EQ(1, A * (-2) == B);
}

TEST(MatrixTest, MulNumberFloat) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 2);
  B(0, 0) = -2.23;
  B(0, 1) = -4.46;
  B(1, 0) = -6.69;
  B(1, 1) = -11.15;

  EXPECT_EQ(1, (A * (-2.23)) == B);
}

TEST(MatrixTest, SubSimpleInt) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 2);
  B(0, 0) = 2;
  B(0, 1) = 3;
  B(1, 0) = 12;
  B(1, 1) = 1;

  Matrix C(2, 2);
  C(0, 0) = -1;
  C(0, 1) = -1;
  C(1, 0) = -9;
  C(1, 1) = 4;

  A -= B;
  EXPECT_EQ(1, A == C);
}

TEST(MatrixTest, SubSimpleFloat) {
  Matrix A(2, 2);
  A(0, 0) = 1.324;
  A(0, 1) = 2.42;
  A(1, 0) = 3.435;
  A(1, 1) = 5.421;

  Matrix B(2, 2);
  B(0, 0) = 2.43;
  B(0, 1) = 3.21;
  B(1, 0) = 12.1;
  B(1, 1) = 1.32;

  Matrix C(2, 2);
  C(0, 0) = -1.106;
  C(0, 1) = -0.79;
  C(1, 0) = -8.665;
  C(1, 1) = 4.101;

  EXPECT_EQ(1, (A - B) == C);
}

TEST(MatrixTest, Sub1x1Int) {
  Matrix A = Matrix(1, 1);
  A(0, 0) = 1;

  Matrix B = Matrix(1, 1);
  B(0, 0) = 2;

  Matrix C = Matrix(1, 1);
  C(0, 0) = -1;

  EXPECT_EQ(1, (A - B) == C);
}

TEST(MatrixTest, Sub1x1Float) {
  Matrix A = Matrix(1, 1);
  A(0, 0) = 1.324;

  Matrix B = Matrix(1, 1);
  B(0, 0) = 2.43;

  Matrix C = Matrix(1, 1);
  C(0, 0) = -1.106;

  EXPECT_EQ(1, (A - B) == C);
}

TEST(MatrixTest, SubError) {
  Matrix A(1, 3);
  A(0, 0) = -1;
  A(0, 1) = 2;
  A(0, 2) = 5;

  Matrix B(2, 2);
  B(0, 0) = 36;
  B(0, 1) = -84;
  B(1, 0) = -14;
  B(1, 1) = 28;

  ASSERT_THROW(A - B, std::logic_error);
}

TEST(MatrixTest, SumSimpleInt) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 2);
  B(0, 0) = 2;
  B(0, 1) = 3;
  B(1, 0) = 12;
  B(1, 1) = 1;

  Matrix C(2, 2);
  C(0, 0) = 3;
  C(0, 1) = 5;
  C(1, 0) = 15;
  C(1, 1) = 6;

  A += B;
  EXPECT_EQ(1, A == C);
}

TEST(MatrixTest, SumSimpleFloat) {
  Matrix A(2, 2);
  A(0, 0) = 1.324;
  A(0, 1) = 2.42;
  A(1, 0) = 3.435;
  A(1, 1) = 5.421;

  Matrix B(2, 2);
  B(0, 0) = 2.43;
  B(0, 1) = 3.21;
  B(1, 0) = 12.1;
  B(1, 1) = 1.32;

  Matrix C(2, 2);
  C(0, 0) = 3.754;
  C(0, 1) = 5.63;
  C(1, 0) = 15.535;
  C(1, 1) = 6.741;

  EXPECT_EQ(1, (A + B) == C);
}

TEST(MatrixTest, Sum1x1Int) {
  Matrix A = Matrix(1, 1);
  A(0, 0) = 1;

  Matrix B = Matrix(1, 1);
  B(0, 0) = 2;

  Matrix C = Matrix(1, 1);
  C(0, 0) = 3;

  EXPECT_EQ(1, (A + B) == C);
}

TEST(MatrixTest, Sum1x1Float) {
  Matrix A = Matrix(1, 1);
  A(0, 0) = 1.324;

  Matrix B = Matrix(1, 1);
  B(0, 0) = 2.43;

  Matrix C = Matrix(1, 1);
  C(0, 0) = 3.754;

  EXPECT_EQ(1, (A + B) == C);
}

TEST(MatrixTest, SumError) {
  Matrix A(1, 3);
  A(0, 0) = -1;
  A(0, 1) = 2;
  A(0, 2) = 5;

  Matrix B(2, 2);
  B(0, 0) = 36;
  B(0, 1) = -84;
  B(1, 0) = -14;
  B(1, 1) = 28;

  ASSERT_THROW(A + B, std::logic_error);
}

TEST(MatrixTest, TransposeSimple) {
  Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;

  Matrix B(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 3;
  B(1, 0) = 2;
  B(1, 1) = 5;

  EXPECT_EQ(1, A.Transpose() == B);
}

TEST(MatrixTest, Transpose1x1) {
  Matrix A(1, 1);
  A(0, 0) = 2;

  Matrix B(1, 1);
  B(0, 0) = 2;

  EXPECT_EQ(1, A.Transpose() == B);
}

TEST(MatrixTest, TransposeNonSquare) {
  Matrix A(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 5;
  A(2, 0) = 5;
  A(2, 1) = 6;

  Matrix B(2, 3);
  B(0, 0) = 1;
  B(0, 1) = 3;
  B(0, 2) = 5;
  B(1, 0) = 2;
  B(1, 1) = 5;
  B(1, 2) = 6;

  EXPECT_EQ(1, A.Transpose() == B);
}

TEST(MatrixTest, SetterRowsGreater) {
  Matrix A = Matrix(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 3;
  A(2, 1) = 5;

  Matrix B = Matrix(5, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  B(2, 0) = 3;
  B(2, 1) = 5;
  B(3, 0) = 0;
  B(3, 1) = 0;
  B(4, 0) = 0;
  B(4, 1) = 0;

  A.SetRows(5);
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, SetterRowsLower) {
  Matrix A = Matrix(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 3;
  A(2, 1) = 5;

  Matrix B = Matrix(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  A.SetRows(2);
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, SetterColsGreater) {
  Matrix A = Matrix(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 3;
  A(2, 1) = 5;

  Matrix B = Matrix(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 0;
  B(0, 3) = 0;
  B(1, 0) = 3;
  B(1, 1) = 4;
  B(1, 2) = 0;
  B(1, 3) = 0;
  B(2, 0) = 3;
  B(2, 1) = 5;
  B(2, 2) = 0;
  B(2, 3) = 0;

  A.SetCols(4);
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, SetterTogetherGreater) {
  Matrix A = Matrix(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  Matrix B = Matrix(3, 3);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 0;
  B(1, 0) = 3;
  B(1, 1) = 4;
  B(1, 2) = 0;
  B(2, 0) = 0;
  B(2, 1) = 0;
  B(2, 2) = 0;

  A.SetCols(3);
  A.SetRows(3);
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, SetterTogetherLower) {
  Matrix A = Matrix(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 1;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(1, 2) = 4;
  A(2, 0) = 3;
  A(2, 1) = 5;
  A(2, 2) = 7;

  Matrix B = Matrix(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  A.SetCols(2);
  A.SetRows(2);
  EXPECT_EQ(1, A == B);
}

TEST(MatrixTest, SetterRowsError) {
  Matrix A = Matrix(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  ASSERT_THROW(A.SetRows(-3), std::logic_error);
}

TEST(MatrixTest, SetterColsError) {
  Matrix A = Matrix(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  ASSERT_THROW(A.SetCols(-3), std::logic_error);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}