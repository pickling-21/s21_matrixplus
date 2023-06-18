#include "s21_matrix_oop.h"

#include <cmath>
#include <cstring>
#include <iostream>

void S21Matrix::Create(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_]();
  matrix_[0] = new double[rows_ * cols_]();
  for (size_t i = 1; i < (size_t)rows_; ++i) {
    matrix_[i] = matrix_[i - 1] + cols_;
  }
}

/// @brief Базовый конструктор, инициализирующий матрицу некоторой заранее
/// заданной размерностью
S21Matrix::S21Matrix() { Create(1, 1); }

/// @brief Параметризированный конструктор с количеством строк и столбцов
/// @param rows
/// @param cols
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range(
        "Incorrect input, matrices should have cols and rows");
  }
  Create(rows, cols);
}

/// @brief Конструктор копирования (инициализация)
/// Существует четыре случая вызова конструктора копирования:
/// Когда объект является возвращаемым значением
/// Когда объект передается(функции) по значению в качестве аргумента
/// Когда объект конструируется на основе другого объекта (того же класса)
////Когда компилятор генерирует временный объект (как в первом и втором случаях
/// выше; как явное преобразование и т. д.
/// @param other

S21Matrix::S21Matrix(const S21Matrix &other) {
  // не нужно очищать... Потому что это конструктор кописрования
  rows_ = other.rows_;
  cols_ = other.cols_;
  Create(rows_, cols_);
  // выделила память
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
// this -  указатель на текущий объект данного класса
/// @brief Конструктор переноса. Не нужна проверка потому что это конструктор
/// его нельзя вызвать к тому же самому. Вызывается std::move(a); Объект a после
/// этого не будет содержать данные, вся инфа перенесеться.
/// @param other
S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;

  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

/// @brief диструктор. Нужно ли сделать проверку на nullptr/
S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_[0];
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

// assignment operator overload

/// @brief Оператор присваивания (copy). Other не трогаем, поэтому она const.
/// Так как возвращамое значение &  а не указатель, а this - указатель, делаем
/// *.
/// @param other
/// @return
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (&other != this) {
    // &other - адрес other сравниваем с указателем this (адрес
    // текущего объекта), чтобы не копировать по одинаковым адресам.
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      // если разные размеры очищаем и выделяем заново.
      delete[] matrix_[0];
      delete[] matrix_;
      Create(other.rows_, other.cols_);
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    // копируем
    for (size_t i = 0; i < (size_t)rows_; ++i) {
      for (size_t j = 0; j < (size_t)cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

/// @brief Оператор присваивания(move). &&other, так как other может быть
/// rvalue.
/// @param other
/// @return
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (&other != this) {
    // Очищаем то что уже есть в том чему мы хотим присвоить
    delete[] matrix_[0];
    delete[] matrix_;
    // Присваиваем
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    // other не должно указывать на тоже самое. оно нам больше не нужно
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
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
bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (size_t i = 0; i < (size_t)rows_; ++i) {
      for (size_t j = 0; j < (size_t)cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > eps) {
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
  for (size_t i = 0; i < (size_t)rows_; ++i) {
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
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (size_t i = 0; i < (size_t)rows_; ++i) {
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
      // result.matrix_[i][j] = 0;
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
      S21Matrix minor_matrix = Minor(i, j);
      result.matrix_[i][j] = pow((-1), i + j) * minor_matrix.Determinant();
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      S21Matrix minor_matrix = Minor(0, j);
      result += matrix_[0][j] * pow(-1, j) * minor_matrix.Determinant();
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
  if (fabs(det) < eps) {
    throw std::invalid_argument("Matrix determinant is 0");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    S21Matrix tmp = CalcComplements();
    result = tmp.Transpose();
    result.MulNumber(1 / det);
  }
  return result;
}

void S21Matrix::FillingMatrixRandom() {
  srand(time(nullptr));
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] = rand() % 10;
    }
  }
}

void S21Matrix::FillingMatrixNumber(double number) {
  for (size_t i = 0; i < (size_t)rows_; ++i) {
    for (size_t j = 0; j < (size_t)cols_; ++j) {
      matrix_[i][j] = number;
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
      }
    }
  }
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
      }
    }
  }
  *this = result;
}

void S21Matrix::print_matrix() const {
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
