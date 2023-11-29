#include "Matrix.h"

Matrix Matrix::MatrixCutCopy(Matrix A, int row, int column) {
  Matrix result = Matrix(A.rows_ - 1, A.cols_ - 1);

  int i_new = 0;
  int j_new = 0;

  for (int i = 0; i < A.rows_; i++) {
    if (i == row) continue;
    j_new = 0;
    for (int j = 0; j < A.cols_; j++) {
      if (j == column) continue;
      result.matrix_[i_new][j_new++] = A.matrix_[i][j];
    }
    i_new++;
  }
  return result;
}

double Matrix::RecursiveDeterminant(Matrix A) {
  if (A.rows_ == 1) return A.matrix_[0][0];
  if (A.rows_ == 2)
    return A.matrix_[0][0] * A.matrix_[1][1] -
           A.matrix_[0][1] * A.matrix_[1][0];

  double res = 0;
  for (int i = 0; i < A.cols_; i++) {
    Matrix copy = MatrixCutCopy(A, 0, i);
    res += pow(-1, i) * A.matrix_[0][i] * RecursiveDeterminant(copy);
  }
  return res;
}

Matrix::Matrix() {
  this->rows_ = 1;
  this->cols_ = 1;

  this->matrix_ = new double*[1];
  for (int i = 0; i < 1; i++) this->matrix_[i] = new double[1];

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] = 0;
};

Matrix::~Matrix() { this->Free(); }

Matrix::Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) throw std::logic_error("Incorrect matrix");

  this->rows_ = rows;
  this->cols_ = cols;

  this->matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) this->matrix_[i] = new double[cols];

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] = 0;
}

Matrix::Matrix(int rows, int cols, double** matrix) {
  this->rows_ = rows;
  this->cols_ = cols;

  this->matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) this->matrix_[i] = new double[cols];

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) this->matrix_[i][j] = matrix[i][j];
}

Matrix::Matrix(const Matrix& other) { this->Copy(other); }

Matrix::Matrix(Matrix&& other) {
  this->Copy(other);
  other.Free();
}

double& Matrix::operator()(int row, int col) const {
  if (row >= this->rows_ || col >= this->cols_ || row < 0 || col < 0)
    throw std::logic_error("Incorrect input, index is out of range");

  return matrix_[row][col];
}

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix temp = Matrix(*this);
  temp.SumMatrix(other);
  return temp;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix temp = Matrix(*this);
  temp.SubMatrix(other);
  return temp;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix temp = Matrix(*this);
  temp.MulMatrix(other);
  return temp;
}

Matrix Matrix::operator*(double other) const {
  Matrix temp = Matrix(*this);
  temp.MulNumber(other);
  return temp;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(double other) {
  this->MulNumber(other);
  return *this;
}

bool Matrix::operator==(const Matrix& other) { return this->EqMatrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
  *this = Matrix(other);
  return *this;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (this->rows_ != other.GetCols())
    throw std::logic_error(
        "Matrices can only be added if the dimensions are the same");

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] += other(i, j);
}

void Matrix::SubMatrix(const Matrix& other) {
  if (this->rows_ != other.GetCols())
    throw std::logic_error(
        "Matrices can only be subtracted if the dimensions are the same");

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] -= other(i, j);
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] *= num;
}

bool Matrix::EqMatrix(const Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return false;

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      if (abs(this->matrix_[i][j] - other(i, j)) > 1e-6) return false;

  return true;
}

Matrix Matrix::Transpose() {
  Matrix resultMatrix = Matrix(this->cols_, this->rows_);

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      resultMatrix(j, i) = this->matrix_[i][j];

  return resultMatrix;
}

void Matrix::MulMatrix(const Matrix& other) {
  if (this->cols_ != other.rows_)
    throw std::logic_error(
        "Only (m, k) and (k, n) dimension matrices can be multiplied");

  Matrix temp = Matrix(this->rows_, other.GetCols());

  for (int i = 0; i < temp.GetRows(); i++)
    for (int j = 0; j < temp.GetCols(); j++)
      for (int k = 0; k < this->cols_; k++)
        (temp)(i, j) += (*this)(i, k) * other(k, j);

  this->Free();
  this->Copy(temp);

  temp.Free();
}

double Matrix::Determinant() {
  if (this->cols_ != this->rows_)
    throw std::logic_error(
        "The determinant can only be calculated for a square matrix");

  double result = RecursiveDeterminant(*this);
  return result;
}

Matrix Matrix::CalcComplements() {
  if (this->rows_ != this->cols_)
    throw std::logic_error(
        "The algebraic complement matrix can only be found for a square "
        "matrix");

  Matrix result = Matrix(this->rows_, this->cols_);

  if (this->rows_ == 1)
    result.matrix_[0][0] = 1;
  else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        Matrix copy = MatrixCutCopy((*this), i, j);
        result(i, j) = pow(-1, i + j) * RecursiveDeterminant(copy);
      }
    }
  }

  return result;
}

Matrix Matrix::InverseMatrix() {
  if (this->rows_ != this->cols_)
    throw std::logic_error(
        "The inverse matrix can only be found for a square matrix");

  double det = this->Determinant();
  if (det == 0)
    throw std::logic_error(
        "The inverse matrix can only be found in the case of a non-zero "
        "determinant");

  Matrix result = this->CalcComplements().Transpose();
  result *= (1 / det);
  return result;
}

void Matrix::Print() {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      std::cout << this->matrix_[i][j];
      if (j != this->cols_ - 1) std::cout << ", ";
    }
    std::cout << std::endl;
  }
}

void Matrix::Free() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) delete[] this->matrix_[i];

    delete[] this->matrix_;
    this->matrix_ = nullptr;
    this->rows_ = 0;
    this->cols_ = 0;
  }
}

void Matrix::Copy(const Matrix& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->matrix_ = new double*[other.rows_];
  for (int i = 0; i < other.rows_; i++)
    this->matrix_[i] = new double[other.cols_];

  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) this->matrix_[i][j] = other(i, j);
}

int Matrix::GetRows() const { return this->rows_; }

int Matrix::GetCols() const { return this->cols_; }

void Matrix::SetRows(int newRows) {
  if (newRows < 0)
    throw std::logic_error(
        "The number of rows in the matrix must be greater than 0");

  if (newRows != this->rows_) {
    Matrix tmp = Matrix(newRows, this->cols_);
    int min = std::min(this->rows_, newRows);

    for (int i = 0; i < min; i++)
      for (int j = 0; j < this->cols_; j++) tmp(i, j) = (*this)(i, j);

    this->Free();
    this->Copy(tmp);
  }
}

void Matrix::SetCols(int newCols) {
  if (newCols < 0)
    throw std::logic_error(
        "The number of columns in the matrix must be greater than 0");

  if (newCols != this->cols_) {
    Matrix tmp = Matrix(this->rows_, newCols);
    int min = std::min(this->cols_, newCols);

    for (int i = 0; i < this->rows_; ++i)
      for (int j = 0; j < min; ++j) tmp(i, j) = (*this)(i, j);

    this->Free();
    this->Copy(tmp);
  }
}
