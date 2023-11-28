#include "./Matrix.h"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm> 
#include <utility>

S21Matrix S21Matrix::MatrixCutCopy(S21Matrix A, int row, int column) {
    S21Matrix result = S21Matrix(A.rows_ - 1, A.cols_ - 1);

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

double S21Matrix::RecursiveDeterminant(S21Matrix A) {
    if (A.rows_ == 1) return A.matrix_[0][0];
    if (A.rows_ == 2)
        return A.matrix_[0][0] * A.matrix_[1][1] - A.matrix_[0][1] * A.matrix_[1][0];

    double res = 0;
    for (int i = 0; i < A.cols_; i++) {
        S21Matrix copy = MatrixCutCopy(A, 0, i);
        res += pow(-1, i) * A.matrix_[0][i] * RecursiveDeterminant(copy);
    }
    return res; 
}

S21Matrix::S21Matrix(){
    this->rows_ = 1;
    this->cols_ = 1;

    this->matrix_ = new double*[1];
    for(int i = 0; i < 1; i++)
        this->matrix_[i] = new double[1];

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            this->matrix_[i][j] = 0;
};            

S21Matrix::~S21Matrix(){
    this->Free();
}   

S21Matrix::S21Matrix(int rows, int cols){
    if (rows <= 0 || cols <= 0)
        throw std::logic_error("Incorrect matrix");

    this->rows_ = rows;
    this->cols_ = cols;

    this->matrix_ = new double*[rows];
    for(int i = 0; i < rows; i++)
        this->matrix_[i] = new double[cols];

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            this->matrix_[i][j] = 0;
}

S21Matrix::S21Matrix(const S21Matrix& other){
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    
    this->matrix_ = new double*[other.rows_];
    for(int i = 0; i < other.rows_; i++)
        this->matrix_[i] = new double[other.cols_];

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            this->matrix_[i][j] = other(i, j);
}

// TODO: ЧТО почему нгельзя вызвать конструктор
S21Matrix::S21Matrix(S21Matrix&& other){
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    
    this->matrix_ = new double*[other.rows_];
    for(int i = 0; i < other.rows_; i++)
        this->matrix_[i] = new double[other.cols_];

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            this->matrix_[i][j] = other(i, j);

    other.Free();
}

double& S21Matrix::operator ()(int row, int col) const{
    if (row >= this->rows_ || col >= this->cols_ || row < 0 || col < 0)
        throw std::logic_error("Incorrect input, index is out of range");

    return matrix_[row][col];
}

S21Matrix S21Matrix::operator +(const S21Matrix& other) const{
    S21Matrix temp = S21Matrix(*this);
    temp.SumMatrix(other);
    return temp;
}

S21Matrix S21Matrix::operator -(const S21Matrix& other) const{
    S21Matrix temp = S21Matrix(*this);
    temp.SubMatrix(other);
    return temp;
}

S21Matrix S21Matrix::operator *(const S21Matrix& other) const{
    S21Matrix temp = S21Matrix(*this);
    temp.MulMatrix(other);
    return temp;
}

S21Matrix S21Matrix::operator *(double other) const{
    S21Matrix temp = S21Matrix(*this);
    temp.MulNumber(other);
    return temp;
}

S21Matrix& S21Matrix::operator +=(const S21Matrix& other){
    this->SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator -=(const S21Matrix& other){
    this->SubMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator *=(const S21Matrix& other){
    this->MulMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator *=(double other){
    this->MulNumber(other);
    return *this;
}

bool S21Matrix::operator ==(const S21Matrix& other){
    return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator =(const S21Matrix& other){
    *this = S21Matrix(other);
    return *this;
}

void S21Matrix::SumMatrix(const S21Matrix& other){
    if (this->rows_ != other.GetCols())
        throw std::logic_error("Matrices can only be added if the dimensions are the same");

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            this->matrix_[i][j] += other(i, j);
}

void S21Matrix::SubMatrix(const S21Matrix& other){
    if (this->rows_ != other.GetCols())
        throw std::logic_error("Matrices can only be subtracted if the dimensions are the same");

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            this->matrix_[i][j] -= other(i, j);
}

void S21Matrix::MulNumber(const double num){
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            this->matrix_[i][j] *= num;
}

bool S21Matrix::EqMatrix(const S21Matrix& other){
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
        return false;
    
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            if (abs(this->matrix_[i][j] - other(i, j)) > 1e-6)
                return false;

    return true;
}

S21Matrix S21Matrix::Transpose(){
    S21Matrix resultMatrix = S21Matrix(this->cols_, this->rows_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->cols_; j++)
            resultMatrix(j, i) = this->matrix_[i][j];
    
    return resultMatrix;
}

void S21Matrix::MulMatrix(const S21Matrix& other){
    if (this->cols_ != other.rows_)
        throw std::logic_error("Only (m, k) and (k, n) dimension matrices can be multiplied");

    S21Matrix temp = S21Matrix(this->rows_, other.GetCols()); 

    for (int i = 0; i < temp.GetRows(); i++)
        for (int j = 0; j < temp.GetCols(); j++)
            for (int k = 0; k < this->cols_; k++)
                (temp)(i, j) += (*this)(i, k) * other(k, j);

    this->cols_ = temp.GetCols();
    this->rows_ = temp.GetRows();
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < other.cols_; j++)
            this->matrix_[i][j] = (temp)(i, j);
}

double S21Matrix::Determinant(){
    if (this->cols_ != this->rows_) 
        throw std::logic_error("The determinant can only be calculated for a square matrix");

    double result = RecursiveDeterminant(*this);
    return result;
}

S21Matrix S21Matrix::CalcComplements(){
    if (this->rows_ != this->cols_)
        throw std::logic_error("The algebraic complement matrix can only be found for a square matrix");

    S21Matrix result = S21Matrix(this->rows_, this->cols_);

    if (this->rows_ == 1)
        result.matrix_[0][0] = 1;
    else{
        for (int i = 0; i < this->rows_; i++){
            for (int j = 0; j < this->cols_; j++) {
                S21Matrix copy = MatrixCutCopy((*this), i, j);
                result(i, j) = pow(-1, i + j) * RecursiveDeterminant(copy);
            }
        }
    }

    return result;
}

S21Matrix S21Matrix::InverseMatrix(){
    if (this->rows_ != this->cols_)
        throw std::logic_error("The inverse matrix can only be found for a square matrix");

    double det = this->Determinant();
    if (det == 0) 
        throw std::logic_error("The inverse matrix can only be found in the case of a non-zero determinant");

    S21Matrix result = this->CalcComplements().Transpose();
    result *= (1 / det);
    return result;
}

void S21Matrix::Print(){
    for (int i = 0; i < this->rows_; i++){
        for (int j = 0; j < this->cols_; j++){
            std::cout << this->matrix_[i][j];
            if (j != this->cols_ - 1)
                std::cout << ", ";
        }   
        std::cout << std::endl;
    }
}

void S21Matrix::Free(){
    if (this->matrix_ != nullptr){
        for(int i = 0; i < this->rows_; i++)
            delete[] this->matrix_[i];
        
        delete[] this->matrix_;
        this->matrix_ = nullptr;  
        this->rows_ = 0;
        this->cols_ = 0;
    }
}

int S21Matrix::GetRows() const {
    return this->rows_;
}

int S21Matrix::GetCols() const {
    return this->cols_;
}

//TODO: ЧТО СУКА С КОНСТРУКТОРОМ
void S21Matrix::SetRows(int newRows) {
    if (newRows < 0) 
        throw std::logic_error("The number of rows in the matrix must be greater than 0");

    if (newRows != this->rows_) {
        S21Matrix tmp = S21Matrix(newRows, this->cols_);
        int min = std::min(this->rows_, newRows);

        for (int i = 0; i < min; i++) 
            for (int j = 0; j < this->cols_; j++) 
                tmp(i, j) = (*this)(i, j);

        this->Free();

        this->rows_ = tmp.rows_;
        this->cols_ = tmp.cols_;
        
        this->matrix_ = new double*[tmp.rows_];
        for(int i = 0; i < tmp.rows_; i++)
            this->matrix_[i] = new double[tmp.cols_];
 
        for (int i = 0; i < this->rows_; i++)
            for (int j = 0; j < this->cols_; j++)
                this->matrix_[i][j] = tmp(i, j);

        // *this = S21Matrix(tmp);
    }
}

void S21Matrix::SetCols(int newCols) {
    if (newCols < 0) 
        throw std::logic_error("The number of columns in the matrix must be greater than 0");

    if (newCols != this->cols_) {
        S21Matrix tmp = S21Matrix(this->rows_, newCols);
        int min = std::min(this->cols_, newCols);

        for (int i = 0; i < this->rows_; ++i) 
            for (int j = 0; j < min; ++j) 
                tmp(i, j) = (*this)(i, j);

        this->Free();

        this->rows_ = tmp.rows_;
        this->cols_ = tmp.cols_;
        
        this->matrix_ = new double*[tmp.rows_];
        for(int i = 0; i < tmp.rows_; i++)
            this->matrix_[i] = new double[tmp.cols_];
 
        for (int i = 0; i < this->rows_; i++)
            for (int j = 0; j < this->cols_; j++)
                this->matrix_[i][j] = tmp(i, j);        

        // *this = S21Matrix(tmp);
    }
}

