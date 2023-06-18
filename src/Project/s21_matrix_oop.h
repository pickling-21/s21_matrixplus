#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

constexpr double eps = 1e-7;

class S21Matrix {
 public:
  S21Matrix();                            // default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix& other);      // copy constructor
  S21Matrix(S21Matrix&& other) noexcept;  // move constructor
  ~S21Matrix();                           // destructor

  // some operators overloads
  double& operator()(int row, int col);  // index operator overload
  double& operator()(int row, int col) const;

  S21Matrix& operator=(const S21Matrix& other);  // assignment operator overload
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);

  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);

  friend S21Matrix operator*(double, S21Matrix&);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);

  S21Matrix operator*(const double num);
  S21Matrix& operator*=(const double num);

  bool operator==(const S21Matrix& other);

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

  int GetRows();
  void SetRows(const int rows);

  int GetCols();
  void SetCols(const int cols);

 private:
  // attributes
  int rows_, cols_;
  double** matrix_;
  void Create(int rows, int cols);
  S21Matrix Minor(int row, int col);
};

#endif  // S21_MATRIX_OOP_H
