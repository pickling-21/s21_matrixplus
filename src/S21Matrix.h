#ifndef S21MATRIX_H
#define S21MATRIX_H

#include <cmath>
#include <iostream>
class S21Matrix {
 private:
  // attributes
  int rows_, cols_;  // rows and columns attributes
  double** matrix_;  // pointer to the memory where the matrix will be allocated

 public:
  S21Matrix();                            // default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix& other);      // copy cnstructor
  S21Matrix(S21Matrix&& other) noexcept;  // move cnstructor
  ~S21Matrix();                           // destructor

  void swap(S21Matrix& other);
  S21Matrix minor(int row, int col);
  // some operators overloads
  double& operator()(int row, int col);  // index operator overload
  double& operator()(int row, int col) const;

  S21Matrix& operator=(const S21Matrix& other);  // assignment operator overload
  bool operator==(const S21Matrix& other);

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);

  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);

  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);

  S21Matrix operator*(const double num);
  S21Matrix& operator*=(const double num);

  // some public methods
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
};

#endif
