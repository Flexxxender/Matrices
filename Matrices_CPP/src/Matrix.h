#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  Matrix MatrixCutCopy(Matrix A, int row, int column);
  double RecursiveDeterminant(Matrix A);

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(int rows, int cols, double** matrix);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);

  ~Matrix();

  double& operator()(int row, int col) const;
  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  Matrix operator*(double other) const;
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(double other);
  Matrix& operator=(const Matrix& other);
  bool operator==(const Matrix& other);

  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  bool EqMatrix(const Matrix& other);
  Matrix Transpose();
  void MulMatrix(const Matrix& other);
  double Determinant();
  Matrix CalcComplements();
  Matrix InverseMatrix();

  void Print();
  void Free();
  void Copy(const Matrix& other);
  int GetRows() const;
  int GetCols() const;
  void SetRows(int newRows);
  void SetCols(int newCols);
};

#endif