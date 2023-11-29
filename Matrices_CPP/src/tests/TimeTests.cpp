#include <gtest/gtest.h>

#include "../Matrix.h"

TEST(MatrixTest, SubTimeComsuming) {
  double** a_matrix = new double*[10000];
  for (int i = 0; i < 10000; i++) {
    a_matrix[i] = new double[10000];

    for (int j = 0; j < 10000; j++) a_matrix[i][j] = j;
  }

  double** b_matrix = new double*[10000];
  for (int i = 0; i < 10000; i++) {
    b_matrix[i] = new double[10000];

    for (int j = 0; j < 10000; j++) b_matrix[i][j] = i - j % 123;
  }

  double** c_matrix = new double*[10000];
  for (int i = 0; i < 10000; i++) {
    c_matrix[i] = new double[10000];

    for (int j = 0; j < 10000; j++)
      c_matrix[i][j] = a_matrix[i][j] - b_matrix[i][j];
  }

  Matrix A = Matrix(10000, 10000, a_matrix);
  Matrix B = Matrix(10000, 10000, b_matrix);
  Matrix C = Matrix(10000, 10000, c_matrix);

  EXPECT_EQ(1, (A - B) == C);
}

TEST(MatrixTest, SumTimeComsuming) {
  double** a_matrix = new double*[10000];
  for (int i = 0; i < 10000; i++) {
    a_matrix[i] = new double[10000];

    for (int j = 0; j < 10000; j++) a_matrix[i][j] = j;
  }

  double** b_matrix = new double*[10000];
  for (int i = 0; i < 10000; i++) {
    b_matrix[i] = new double[10000];

    for (int j = 0; j < 10000; j++) b_matrix[i][j] = j + j % 21;
  }

  double** c_matrix = new double*[10000];
  for (int i = 0; i < 10000; i++) {
    c_matrix[i] = new double[10000];

    for (int j = 0; j < 10000; j++)
      c_matrix[i][j] = a_matrix[i][j] + b_matrix[i][j];
  }

  Matrix A = Matrix(10000, 10000, a_matrix);
  Matrix B = Matrix(10000, 10000, b_matrix);
  Matrix C = Matrix(10000, 10000, c_matrix);

  EXPECT_EQ(1, (A + B) == C);
}

TEST(MatrixTest, MulTimeComsuming) {
  double** a_matrix = new double*[500];
  for (int i = 0; i < 500; i++) {
    a_matrix[i] = new double[500];

    for (int j = 0; j < 500; j++) a_matrix[i][j] = j;
  }

  double** b_matrix = new double*[500];
  for (int i = 0; i < 500; i++) {
    b_matrix[i] = new double[500];

    for (int j = 0; j < 500; j++) b_matrix[i][j] = j + j % 21;
  }

  double** c_matrix = new double*[500];
  for (int i = 0; i < 500; i++) {
    c_matrix[i] = new double[500];
    for (int j = 0; j < 500; j++) {
      c_matrix[i][j] = 0;
      for (int k = 0; k < 500; k++)
        c_matrix[i][j] += a_matrix[i][k] * b_matrix[k][j];
    }
  }

  Matrix A = Matrix(500, 500, a_matrix);
  Matrix B = Matrix(500, 500, b_matrix);
  Matrix C = Matrix(500, 500, c_matrix);

  EXPECT_EQ(1, (A * B) == C);
}

TEST(MatrixTest, DetTimeComsuming) {
  double a_matrix_temp[10][10] = {
      {-1, 2, 5, 5, 1, 5, 7, 6, 8, 1},     {3, 4, 6, 2, 6, 8, 2, 65, 1, 6},
      {-8, 2, 12, 3, 5, 78, 1, 54, 7, 78}, {5, 2, 8, 0, 4, 22, 42, 62, 6, 5},
      {25, 7, 1, 57, 6, -1, 0, 32, 42, 3}, {-6, 1, -63, 15, -5, 1, 2, 1, 1, 3},
      {3, 7, -1, 73, 21, 6, 2, 12, 4, 11}, {17, 3, 12, 6, 24, 1, 2, 9, 1, 8},
      {7, -1, 54, 7, 2, 67, 0, 9, 1, 4},   {14, 15, 12, 5, 4, -1, 7, 3, 1, 7}};

  double** a_matrix = new double*[10];
  for (int i = 0; i < 10; i++) {
    a_matrix[i] = new double[10];
    for (int j = 0; j < 10; j++) a_matrix[i][j] = a_matrix_temp[i][j];
  }

  Matrix A = Matrix(10, 10, a_matrix);
  EXPECT_EQ(-4775208285117936, A.Determinant());
}

TEST(MatrixTest, InverseTimeComsuming) {
  double a_matrix_temp[10][10] = {
      {-1, 2, 5, 5, 1, 5, 7, 6, 8, 1},     {3, 4, 6, 2, 6, 8, 2, 65, 1, 6},
      {-8, 2, 12, 3, 5, 78, 1, 54, 7, 78}, {5, 2, 8, 0, 4, 22, 42, 62, 6, 5},
      {25, 7, 1, 57, 6, -1, 0, 32, 42, 3}, {-6, 1, -63, 15, -5, 1, 2, 1, 1, 3},
      {3, 7, -1, 73, 21, 6, 2, 12, 4, 11}, {17, 3, 12, 6, 24, 1, 2, 9, 1, 8},
      {7, -1, 54, 7, 2, 67, 0, 9, 1, 4},   {14, 15, 12, 5, 4, -1, 7, 3, 1, 7}};

  double b_matrix_temp[10][10] = {
      {-0.122413, -0.018346, 0.000141, 0.019341, 0.021286, 0.000433, -0.009845,
       0.007278, 0.006077, 0.012198},
      {0.120003, 0.031605, -0.006688, -0.031630, -0.019696, 0.022038, -0.002052,
       -0.004990, 0.005936, 0.057421},
      {-0.002032, -0.001239, 0.000890, 0.001263, 0.000299, -0.018165, 0.004319,
       -0.007683, -0.001135, 0.000831},
      {-0.032311, -0.005611, -0.000182, 0.005973, 0.004511, -0.004915, 0.014667,
       -0.013063, 0.000339, -0.000954},
      {0.093642, 0.012373, -0.004450, -0.016258, -0.016174, 0.011823, 0.000823,
       0.046700, 0.000627, -0.015947},
      {0.019077, 0.002489, -0.001524, -0.004086, -0.003380, 0.016018, -0.004002,
       0.005938, 0.016298, -0.000183},
      {-0.004805, -0.022364, 0.000110, 0.025330, -0.002362, -0.004188, 0.004197,
       -0.002389, -0.005688, 0.002734},
      {-0.009030, 0.015269, -0.000470, 0.001510, 0.001434, -0.001274, -0.000041,
       -0.003609, -0.001043, -0.002919},
      {0.093667, 0.001096, 0.001149, -0.013829, 0.009066, 0.003816, -0.014203,
       0.010976, -0.002900, -0.011336},
      {-0.041249, -0.015950, 0.014907, 0.007370, 0.005110, -0.013719, 0.003013,
       -0.004828, -0.014650, 0.003896}};

  double** a_matrix = new double*[10];
  for (int i = 0; i < 10; i++) {
    a_matrix[i] = new double[10];
    for (int j = 0; j < 10; j++) a_matrix[i][j] = a_matrix_temp[i][j];
  }

  double** b_matrix = new double*[10];
  for (int i = 0; i < 10; i++) {
    b_matrix[i] = new double[10];
    for (int j = 0; j < 10; j++) b_matrix[i][j] = b_matrix_temp[i][j];
  }

  Matrix A = Matrix(10, 10, a_matrix);
  Matrix B = Matrix(10, 10, b_matrix);
  EXPECT_EQ(1, A.InverseMatrix() == B);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}