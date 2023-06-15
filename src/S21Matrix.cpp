#include "S21Matrix.h"

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double *[rows_];
  matrix_[0] = new double[rows_ * cols_];
  for (size_t i = 1; i != rows_; ++i) {
    matrix_[i] = matrix_[i - 1] + cols_;
  }
  // Все тоже самое...
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::out_of_range(
        "Incorrect input, matrices should have cols and rows");
  } else {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double *[rows_];
    matrix_[0] = new double[rows_ * cols_];
    for (size_t i = 1; i != rows_; ++i) {
      matrix_[i] = matrix_[i - 1] + cols_;
    }
  }
  // Все тоже самое...
}

// copy
S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  for (size_t i = 0; i != rows_; ++i) {
    for (size_t j = 0; j != cols_; ++j) {
      other.matrix_[i][j] = matrix_[i][j];
    }
  }
}

// Move
/* Компилятор рекомендует использовать слово noexcept для конструктора переноса
 * и оператора переноса. В конструкторе переноса не происходит никаких операций
 * с памятью (выделение памяти, освобождение памяти, запись данных в выделенную
 * область памяти и т.п.), а происходит простое присвоение указателя
 * (указателей).*/
S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  swap(other);
  other.matrix_ = 0;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || col < 1 || row < 1) {
    throw std::out_of_range("Incorrect input, index is out of range ");
  }
  return matrix_[rows_][cols_];
  // Все тоже самое...
}

double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || col < 1 || row < 1) {
    throw std::out_of_range("Incorrect input, index is out of range ");
  }
  return matrix_[rows_][cols_];
  // Все тоже самое...
}

void S21Matrix::swap(S21Matrix &other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}
// Присвоение матрице значений другой матрицы
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    // копирую матрицу other и потом переношу ее значения в this
    S21Matrix(other).swap(*this);
  }
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (size_t i = 0; i != rows_; ++i) {
      for (size_t j = 0; j != cols_; ++j) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          // if (matrix_[i][j] - other.matrix_[i][j] > 1e-7) { ????
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
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j != cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
  // Все тоже самое...
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j != cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  // Все тоже самое...
}

void S21Matrix::MulNumber(const double num) {
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j != cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  S21Matrix result(rows_, other.cols_);
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < other.cols_; ++j) {
      result.matrix_[i][j] = 0;
      for (size_t s = 0; s < cols_; ++s) {
        result.matrix_[i][j] += matrix_[i][s] * other.matrix_[s][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(rows_, cols_);
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j != cols_; ++j) {
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
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j != cols_; ++j) {
      S21Matrix minor = this->minor(i, j);
      result.matrix_[i][j] = pow((-1), i + j) * minor.Determinant();
      delete &minor;
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square");
  }
  double result = 0;
  if (rows_ = 1) {
    result = matrix_[0][0];
  } else if (rows_ = 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (size_t j = 0; j < cols_; ++j) {
      S21Matrix minor = this->minor(0, j);
      result += matrix_[0][j] * pow(-1, j + 2) *
                Determinant();  // this->Determinant()???
      delete &minor;
    }
  }
  return result;
}

S21Matrix S21Matrix::minor(int row, int col) {
  S21Matrix result(rows_, cols_);
  for (size_t i, min_i = 0; min_i < result.rows_; ++min_i) {
    if (row == i) ++i;
    for (size_t j, min_j = 0; min_j < result.cols_; ++min_j) {
      if (col == j) ++j;
      result.matrix_[min_i][min_j] = matrix_[i][j];
      ++j;
    }
    ++i;
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det = 0) {
    throw std::invalid_argument("Matrix determinant is 0");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    S21Matrix tmp = CalcComplements();
    result = tmp.Transpose();
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j != cols_; ++j) {
        result.matrix_[i][j] /= det;
      }
    }
    delete &tmp;
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