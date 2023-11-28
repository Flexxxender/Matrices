#include <gtest/gtest.h>
#include "../Matrix.h"
#include <cmath>

TEST(S21MatrixTest, DefaultConstructor) {
    S21Matrix matrix;
    ASSERT_EQ(matrix.GetRows(), 1);
    ASSERT_EQ(matrix.GetCols(), 1);
    ASSERT_EQ(matrix(0, 0), 0);
}

TEST(S21MatrixTest, Constructor) {
    S21Matrix matrix(3, 4);
    ASSERT_EQ(matrix.GetRows(), 3);
    ASSERT_EQ(matrix.GetCols(), 4);

    for (int i = 0; i < matrix.GetRows(); i++) 
        for (int j = 0; j < matrix.GetCols(); j++) 
            ASSERT_EQ(matrix(i, j), 0);

    ASSERT_THROW(S21Matrix matrix2(0, 4), std::logic_error);
    ASSERT_THROW(S21Matrix matrix3(3, -1), std::logic_error);
}

TEST(S21MatrixTest, MoveConstructor) {
    S21Matrix A(5, 5);
    S21Matrix B(std::move(A));
    EXPECT_EQ(5, B.GetRows());
    EXPECT_EQ(5, B.GetCols());
    EXPECT_EQ(0, A.GetRows());
    EXPECT_EQ(0, A.GetCols());
}

TEST(S21MatrixTest, CopyConstructor) {
    S21Matrix A(3, 4);
    S21Matrix B(A);
    EXPECT_EQ(3, B.GetRows());
    EXPECT_EQ(4, B.GetCols());
    EXPECT_EQ(1, A == B);
}

TEST(S21MatrixTest, CalcComplementsSimple){
    S21Matrix A(3, 3);
    A(0, 0) = -1;
    A(0, 1) = 2;
    A(0, 2) = 5;
    A(1, 0) = 3;
    A(1, 1) = 4;
    A(1, 2) = 6;
    A(2, 0) = -8;
    A(2, 1) = 2;
    A(2, 2) = 12; 
    
    S21Matrix B(3, 3);
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

TEST(S21MatrixTest, Complements1x1){
    S21Matrix A = S21Matrix(1, 1);
    A(0, 0) = 4;

    S21Matrix B = S21Matrix(1, 1);
    B(0, 0) = 1;
    EXPECT_EQ(1, A.CalcComplements() == B);
}

TEST(S21MatrixTest, ComplementsError){
    S21Matrix A = S21Matrix(3, 2);
    ASSERT_THROW(A.CalcComplements(), std::logic_error);
}

TEST(S21MatrixTest, Determinant2x2){
    S21Matrix A = S21Matrix(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    EXPECT_EQ(-1, A.Determinant());
}

TEST(S21MatrixTest, Determinant1x1){
    S21Matrix A = S21Matrix(1, 1);
    A(0, 0) = 5;

    EXPECT_EQ(5, A.Determinant());
}

TEST(S21MatrixTest, DeterminantZero){
    S21Matrix A = S21Matrix(3, 3);
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

TEST(S21MatrixTest, DeterminantHard){
    S21Matrix A = S21Matrix(4, 4);
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

TEST(S21MatrixTest, DeterminantError){
    S21Matrix A = S21Matrix(3, 2);
    ASSERT_THROW(A.Determinant(), std::logic_error);
}

TEST(S21MatrixTest, InverseMatrixSimple){
    S21Matrix A(3, 3);
    A(0, 0) = -1;
    A(0, 1) = 2;
    A(0, 2) = 5;
    A(1, 0) = 3;
    A(1, 1) = 4;
    A(1, 2) = 6;
    A(2, 0) = -8;
    A(2, 1) = 2;
    A(2, 2) = 12; 
    
    S21Matrix B(3, 3);
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

TEST(S21MatrixTest, InverseMatrix1x1){
    S21Matrix A = S21Matrix(1, 1);
    A(0, 0) = 4;

    S21Matrix B = S21Matrix(1, 1);
    B(0, 0) = 0.25;
    EXPECT_EQ(1, A.InverseMatrix() == B);
}

TEST(S21MatrixTest, InverseMatrixError1){
    S21Matrix A = S21Matrix(3, 2);
    ASSERT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(S21MatrixTest, InverseMatrixError2){
    S21Matrix A = S21Matrix(3, 3);
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

TEST(S21MatrixTest, MulMatrixSquareInt){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    S21Matrix B(2, 2);
    B(0, 0) = 2;
    B(0, 1) = 3;
    B(1, 0) = 12;
    B(1, 1) = 1;

    S21Matrix C(2, 2);
    C(0, 0) = 26;
    C(0, 1) = 5;
    C(1, 0) = 66;
    C(1, 1) = 14;
    
    EXPECT_EQ(1, (A * B) == C);
}

TEST(S21MatrixTest, MulMatrixSquareFloat){
    S21Matrix A(2, 2);
    A(0, 0) = 1.324;
    A(0, 1) = 2.42;
    A(1, 0) = 3.435;
    A(1, 1) = 5.421;

    S21Matrix B(2, 2);
    B(0, 0) = 2.43;
    B(0, 1) = 3.21;
    B(1, 0) = 12.1;
    B(1, 1) = 1.32;

    S21Matrix C(2, 2);
    C(0, 0) = 32.49932;
    C(0, 1) = 7.44444;
    C(1, 0) = 73.94115;
    C(1, 1) = 18.18207;

    A *= B;
    EXPECT_EQ(1, A == C);
}

TEST(S21MatrixTest, MulMatrixNonSquareInt){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    S21Matrix B(2, 3);
    B(0, 0) = 2;
    B(0, 1) = 3;
    B(0, 2) = 5;
    B(1, 0) = 12;
    B(1, 1) = 1;
    B(1, 2) = 7;

    S21Matrix C(2, 3);
    C(0, 0) = 26;
    C(0, 1) = 5;
    C(0, 2) = 19;
    C(1, 0) = 66;
    C(1, 1) = 14;
    C(1, 2) = 50;
    
    EXPECT_EQ(1, (A * B) == C);
}

TEST(S21MatrixTest, MulMatrixNonSquareFloat){
    S21Matrix A(2, 2);
    A(0, 0) = 1.23;
    A(0, 1) = 2.64;
    A(1, 0) = 3.1;
    A(1, 1) = 5.01;

    S21Matrix B(2, 3);
    B(0, 0) = 2.21;
    B(0, 1) = 3.1;
    B(0, 2) = 45;
    B(1, 0) = 12.33;
    B(1, 1) = 1.1;
    B(1, 2) = 7;

    S21Matrix C(2, 3);
    C(0, 0) = 35.2695;
    C(0, 1) = 6.717;
    C(0, 2) = 73.83;
    C(1, 0) = 68.6243;
    C(1, 1) = 15.121;
    C(1, 2) = 174.57;

    EXPECT_EQ(1, (A * B) == C);
}

TEST(S21MatrixTest, MulMatrix1x1){
    S21Matrix A = S21Matrix(1, 1);
    A(0, 0) = 1;

    S21Matrix B = S21Matrix(1, 1);
    B(0, 0) = 2;
    
    S21Matrix C = S21Matrix(1, 1);
    C(0, 0) = 2;

    EXPECT_EQ(1, (A * B) == C);
}

TEST(S21MatrixTest, MulMatrixError){
    S21Matrix A(1, 3);
    A(0, 0) = -1;
    A(0, 1) = 2;
    A(0, 2) = 5;
    
    S21Matrix B(2, 2);
    B(0, 0) = 36;
    B(0, 1) = -84;
    B(1, 0) = -14;
    B(1, 1) = 28;

    ASSERT_THROW(A * B, std::logic_error);
}

TEST(S21MatrixTest, MulNumberSimple){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    S21Matrix B(2, 2);
    B(0, 0) = 2;
    B(0, 1) = 4;
    B(1, 0) = 6;
    B(1, 1) = 10;

    A *= 2;
    EXPECT_EQ(1, A == B);
}

TEST(S21MatrixTest, MulNumber1x1){
    S21Matrix A(1, 1);
    A(0, 0) = 4;

    S21Matrix B(1, 1);
    B(0, 0) = 12;

    EXPECT_EQ(1, A * 3 == B);
}

TEST(S21MatrixTest, MulNumberZero){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    S21Matrix B(2, 2);

    EXPECT_EQ(1, A * 0 == B);
}

TEST(S21MatrixTest, MulNumberNegative){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    S21Matrix B(2, 2);
    B(0, 0) = -2;
    B(0, 1) = -4;
    B(1, 0) = -6;
    B(1, 1) = -10;

    EXPECT_EQ(1, A * (-2) == B);
}

TEST(S21MatrixTest, MulNumberFloat){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    S21Matrix B(2, 2);
    B(0, 0) = -2.23;
    B(0, 1) = -4.46;
    B(1, 0) = -6.69;
    B(1, 1) = -11.15;

    EXPECT_EQ(1, (A * (-2.23)) == B);
}

TEST(S21MatrixTest, SubSimpleInt){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    S21Matrix B(2, 2);
    B(0, 0) = 2;
    B(0, 1) = 3;
    B(1, 0) = 12;
    B(1, 1) = 1;

    S21Matrix C(2, 2);
    C(0, 0) = -1;
    C(0, 1) = -1;
    C(1, 0) = -9;
    C(1, 1) = 4;
    
    A -= B;
    EXPECT_EQ(1, A == C);
}

TEST(S21MatrixTest, SubSimpleFloat){
    S21Matrix A(2, 2);
    A(0, 0) = 1.324;
    A(0, 1) = 2.42;
    A(1, 0) = 3.435;
    A(1, 1) = 5.421;

    S21Matrix B(2, 2);
    B(0, 0) = 2.43;
    B(0, 1) = 3.21;
    B(1, 0) = 12.1;
    B(1, 1) = 1.32;

    S21Matrix C(2, 2);
    C(0, 0) = -1.106;
    C(0, 1) = -0.79;
    C(1, 0) = -8.665;
    C(1, 1) = 4.101;
    
    EXPECT_EQ(1, (A - B) == C);
}

TEST(S21MatrixTest, Sub1x1Int){
    S21Matrix A = S21Matrix(1, 1);
    A(0, 0) = 1;

    S21Matrix B = S21Matrix(1, 1);
    B(0, 0) = 2;
    
    S21Matrix C = S21Matrix(1, 1);
    C(0, 0) = -1;

    EXPECT_EQ(1, (A - B) == C);
}

TEST(S21MatrixTest, Sub1x1Float){
    S21Matrix A = S21Matrix(1, 1);
    A(0, 0) = 1.324;

    S21Matrix B = S21Matrix(1, 1);
    B(0, 0) = 2.43;
    
    S21Matrix C = S21Matrix(1, 1);
    C(0, 0) = -1.106;

    EXPECT_EQ(1, (A - B) == C);
}

TEST(S21MatrixTest, SubError){
    S21Matrix A(1, 3);
    A(0, 0) = -1;
    A(0, 1) = 2;
    A(0, 2) = 5;
    
    S21Matrix B(2, 2);
    B(0, 0) = 36;
    B(0, 1) = -84;
    B(1, 0) = -14;
    B(1, 1) = 28;

    ASSERT_THROW(A - B, std::logic_error);
}

TEST(S21MatrixTest, SumSimpleInt){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5;

    S21Matrix B(2, 2);
    B(0, 0) = 2;
    B(0, 1) = 3;
    B(1, 0) = 12;
    B(1, 1) = 1;

    S21Matrix C(2, 2);
    C(0, 0) = 3;
    C(0, 1) = 5;
    C(1, 0) = 15;
    C(1, 1) = 6;
    
    A += B;
    EXPECT_EQ(1, A == C);
}

TEST(S21MatrixTest, SumSimpleFloat){
    S21Matrix A(2, 2);
    A(0, 0) = 1.324;
    A(0, 1) = 2.42;
    A(1, 0) = 3.435;
    A(1, 1) = 5.421;

    S21Matrix B(2, 2);
    B(0, 0) = 2.43;
    B(0, 1) = 3.21;
    B(1, 0) = 12.1;
    B(1, 1) = 1.32;

    S21Matrix C(2, 2);
    C(0, 0) = 3.754;
    C(0, 1) = 5.63;
    C(1, 0) = 15.535;
    C(1, 1) = 6.741;
    
    EXPECT_EQ(1, (A + B) == C);
}

TEST(S21MatrixTest, Sum1x1Int){
    S21Matrix A = S21Matrix(1, 1);
    A(0, 0) = 1;

    S21Matrix B = S21Matrix(1, 1);
    B(0, 0) = 2;
    
    S21Matrix C = S21Matrix(1, 1);
    C(0, 0) = 3;

    EXPECT_EQ(1, (A + B) == C);
}

TEST(S21MatrixTest, Sum1x1Float){
    S21Matrix A = S21Matrix(1, 1);
    A(0, 0) = 1.324;

    S21Matrix B = S21Matrix(1, 1);
    B(0, 0) = 2.43;
    
    S21Matrix C = S21Matrix(1, 1);
    C(0, 0) = 3.754;

    EXPECT_EQ(1, (A + B) == C);
}

TEST(S21MatrixTest, SumError){ 
    S21Matrix A(1, 3);
    A(0, 0) = -1;
    A(0, 1) = 2;
    A(0, 2) = 5;
    
    S21Matrix B(2, 2);
    B(0, 0) = 36;
    B(0, 1) = -84;
    B(1, 0) = -14;
    B(1, 1) = 28;

    ASSERT_THROW(A + B, std::logic_error);
}

TEST(S21MatrixTest, TransposeSimple){
    S21Matrix A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5; 
    
    S21Matrix B(2, 2);
    B(0, 0) = 1;
    B(0, 1) = 3;
    B(1, 0) = 2;
    B(1, 1) = 5;

    EXPECT_EQ(1, A.Transpose() == B);
}

TEST(S21MatrixTest, Transpose1x1){
    S21Matrix A(1, 1);
    A(0, 0) = 2;
    
    S21Matrix B(1, 1);
    B(0, 0) = 2;

    EXPECT_EQ(1, A.Transpose() == B);
}

TEST(S21MatrixTest, TransposeNonSquare){
    S21Matrix A(3, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 5; 
    A(2, 0) = 5;
    A(2, 1) = 6;
    
    S21Matrix B(2, 3);
    B(0, 0) = 1;
    B(0, 1) = 3;
    B(0, 2) = 5;
    B(1, 0) = 2;
    B(1, 1) = 5;
    B(1, 2) = 6;

    EXPECT_EQ(1, A.Transpose() == B);
}

TEST(S21MatrixTest, SetterRowsGreater){
    S21Matrix A = S21Matrix(3, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;
    A(2, 0) = 3;
    A(2, 1) = 5;

    S21Matrix B = S21Matrix(5, 2);
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

TEST(S21MatrixTest, SetterRowsLower){
    S21Matrix A = S21Matrix(3, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;
    A(2, 0) = 3;
    A(2, 1) = 5;

    S21Matrix B = S21Matrix(2, 2);
    B(0, 0) = 1;
    B(0, 1) = 2;
    B(1, 0) = 3;
    B(1, 1) = 4;


    A.SetRows(2);
    EXPECT_EQ(1, A == B);
} 

TEST(S21MatrixTest, SetterColsGreater){
    S21Matrix A = S21Matrix(3, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;
    A(2, 0) = 3;
    A(2, 1) = 5;

    S21Matrix B = S21Matrix(3, 4);
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

TEST(S21MatrixTest, SetterTogetherGreater){
    S21Matrix A = S21Matrix(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;

    S21Matrix B = S21Matrix(3, 3);
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

TEST(S21MatrixTest, SetterTogetherLower){
    S21Matrix A = S21Matrix(3, 3);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(0, 2) = 1;
    A(1, 0) = 3;
    A(1, 1) = 4;
    A(1, 2) = 4;
    A(2, 0) = 3;
    A(2, 1) = 5;
    A(2, 2) = 7;

    S21Matrix B = S21Matrix(2, 2);
    B(0, 0) = 1;
    B(0, 1) = 2;
    B(1, 0) = 3;
    B(1, 1) = 4;

    A.SetCols(2);
    A.SetRows(2);
    EXPECT_EQ(1, A == B);
} 

TEST(S21MatrixTest, SetterRowsError){
    S21Matrix A = S21Matrix(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;

    ASSERT_THROW(A.SetRows(-3), std::logic_error);
} 

TEST(S21MatrixTest, SetterColsError){
    S21Matrix A = S21Matrix(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;

    ASSERT_THROW(A.SetCols(-3), std::logic_error);
} 

int main(int argc, char *argv[]) {

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}