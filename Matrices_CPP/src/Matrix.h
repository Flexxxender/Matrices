#ifndef MATRIX_H
#define MATRIX_H

class S21Matrix{
private:
    int rows_, cols_;          
    double **matrix_;         

    S21Matrix MatrixCutCopy(S21Matrix A, int row, int column);
    double RecursiveDeterminant(S21Matrix A);
public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);

    ~S21Matrix();

    double& operator ()(int row, int col) const;
    S21Matrix operator +(const S21Matrix& other) const;
    S21Matrix operator -(const S21Matrix& other) const;
    S21Matrix operator *(const S21Matrix& other) const;
    S21Matrix operator *(double other) const;
    S21Matrix& operator +=(const S21Matrix& other);
    S21Matrix& operator -=(const S21Matrix& other);
    S21Matrix& operator *=(const S21Matrix& other);
    S21Matrix& operator *=(double other);
    S21Matrix& operator =(const S21Matrix& other);
    bool operator ==(const S21Matrix& other);

    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    bool EqMatrix(const S21Matrix& other);
    S21Matrix Transpose();
    void MulMatrix(const S21Matrix& other);
    double Determinant();
    S21Matrix CalcComplements();
    S21Matrix InverseMatrix();
    
    void Print();
    void Free();
    int GetRows() const;
    int GetCols() const;
    void SetRows(int newRows);
    void SetCols(int newCols);
};

#endif 