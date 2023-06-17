#include "s21_matrix_oop.h"

#include <cmath>
#include <iostream>

S21Matrix::S21Matrix() { Create(0, 0); }

void S21Matrix::Create(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  matrix_[0] = new double[rows_ * cols_];
  for (size_t i = 1; i < (size_t)rows_; ++i) {
    matrix_[i] = matrix_[i - 1] + cols_;
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::out_of_range(
        "Incorrect input, matrices should have cols and rows");
  } else {
    Create(rows, cols);
  }
}

// copy constructor
S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {  // создаю
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
// Copy assignment operator.
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    // копирую матрицу other и потом переношу ее значения в this
    S21Matrix tmp(other);
    *this = std::move(tmp);
  }
  return *this;
}
void S21Matrix::Swap(S21Matrix &other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}
// Move
/* Компилятор рекомендует использовать слово noexcept для конструктора переноса
 * и оператора переноса. В конструкторе переноса не происходит никаких операций
 * с памятью (выделение памяти, освобождение памяти, запись данных в выделенную
 * область памяти и т.п.), а происходит простое присвоение указателя
 * (указателей).*/
S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  Swap(other);
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}
// конструктор перемещения, который вызывается при создании нового объекта
// класса S21Matrix на основе существующего объекта. Он переносит ресурсы из
// объекта other в новый объект, а затем устанавливает other в нулевое
// состояние.

// !!!!конструктор перемещения используется для создания новых объектов, а
// оператор перемещения используется для изменения существующих объектов.
S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    delete[] matrix_[0];
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
    Swap(other);
  }
  return *this;
}

// оператор перемещения, который вызывается при присваивании существующего
// объекта other объекту this. Он удаляет ресурсы текущего объекта, затем
// переносит ресурсы из объекта other в текущий объект, а затем устанавливает
// other в нулевое состояни

//  диструктор
S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_[0];
    delete[] matrix_;
  }
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

// индексация
double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || col < 0 || row < 0) {
    throw std::out_of_range("Incorrect input, index is out of range ");
  }
  return matrix_[row][col];
}

double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || col < 0 || row < 0) {
    throw std::out_of_range("Incorrect input, index is out of range ");
  }
  return matrix_[row][col];
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (size_t i = 0; i < (size_t)rows_; ++i) {
      for (size_t j = 0; j < (size_t)cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          result = false;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (size_t i = 0; i < (size_t)rows_; i++) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (size_t i = 0; i < (size_t)rows_; i++) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (size_t i = 0; i < (size_t)rows_; i++) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "The number of columns of the first matrix is not SetColsual to the "
        "number "
        "of rows of the second matrix");
  }
  S21Matrix result(rows_, other.cols_);
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j < (size_t)other.cols_; ++j) {
      result.matrix_[i][j] = 0;
      for (size_t s = 0; s < (size_t)other.rows_; ++s) {
        result.matrix_[i][j] += matrix_[i][s] * other.matrix_[s][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (size_t i = 0; i < (size_t)cols_; ++i) {
    for (size_t j = 0; j < (size_t)rows_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square");
  }
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j != (size_t)cols_; ++j) {
      S21Matrix Minor = this->Minor(i, j);
      result.matrix_[i][j] = pow((-1), i + j) * Minor.Determinant();
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square");
  }
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      S21Matrix Minor = this->Minor(0, j);
      result += matrix_[0][j] * pow(-1, j) * Minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::Minor(int row, int col) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (size_t i = 0, min_i = 0; min_i < (size_t)result.rows_; ++min_i) {
    if ((size_t)row == i) ++i;
    for (size_t j = 0, min_j = 0; min_j < (size_t)result.cols_; ++min_j) {
      if ((size_t)col == j) ++j;
      result.matrix_[min_i][min_j] = matrix_[i][j];
      ++j;
    }
    ++i;
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) {
    throw std::invalid_argument("Matrix determinant is 0");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    S21Matrix tmp = CalcComplements();
    result = tmp.Transpose();
    for (size_t i = 0; i < (size_t)rows_; ++i) {
      for (size_t j = 0; j != (size_t)cols_; ++j) {
        result.matrix_[i][j] /= det;
      }
    }
  }
  return result;
}

// assignment operator overload
bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result.SumMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result.MulMatrix(other);
  return result;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(rows_, cols_);
  result.MulNumber(num);
  return result;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

// DELETE

void S21Matrix::FillingMatrix() {
  for (size_t i = 0; i < (size_t)rows_; i++) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] = i * 2 + j + 1;
    }
  }
}

void S21Matrix::ZeroingMatrix() {
  for (size_t i = 0; i < (size_t)rows_; i++) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::OneMatrix() {
  for (size_t i = 0; i < (size_t)rows_; i++) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] = 1;
    }
  }
}

int S21Matrix::GetRows() { return rows_; }
int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(const int rows) {
  if (rows < 1) {
    throw std::out_of_range(
        "Incorrect input, matrices should have cols and rowsSET");
  }
  S21Matrix result(rows, cols_);
  for (size_t i = 0; i < (size_t)rows; ++i) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      if (i < (size_t)rows_) {
        result.matrix_[i][j] = matrix_[i][j];
      } else {
        result.matrix_[i][j] = 0;
      }
    }
  }
  result.print_matrix();
  *this = result;
}

void S21Matrix::SetCols(const int cols) {
  if (cols <= 0) {
    throw std::out_of_range(
        "Incorrect input, matrices should have cols and rowsSET");
  }
  S21Matrix result(rows_, cols);
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j < (size_t)cols; ++j) {
      if (j < (size_t)cols_) {
        result.matrix_[i][j] = matrix_[i][j];
      } else {
        result.matrix_[i][j] = 0;
      }
    }
  }
  *this = result;
}

void S21Matrix::print_matrix() {
  std::cout << "\nSTART\n";
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      std::cout << matrix_[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "\nEND\n";
}

bool S21Matrix::IsEmpty() {
  return rows_ == 0 && cols_ == 0 && matrix_ == nullptr ? true : false;
}