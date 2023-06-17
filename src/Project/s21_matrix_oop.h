#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

class S21Matrix {
 private:
  // attributes
  int rows_, cols_;  // rows and columns attributes
  double** matrix_;  // pointer to the memory where the matrix will be allocated
  void Create(int rows, int cols);
  void Swap(S21Matrix& other);
  S21Matrix Minor(int row, int col);

 public:
  S21Matrix();                            // default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix& other);      // copy cnstructor
  S21Matrix(S21Matrix&& other) noexcept;  // move cnstructor
  ~S21Matrix();                           // destructor

  // some operators overloads
  double& operator()(int row, int col);  // index operator overload
  double& operator()(int row, int col) const;

  S21Matrix& operator=(const S21Matrix& other);  // assignment operator overload
  S21Matrix& operator=(S21Matrix&& other);

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

  int GetRows();
  void SetRows(const int rows);

  int GetCols();
  void SetCols(const int cols);
  // DELETE

  bool IsEmpty();
  void FillingMatrixRandom();
  void ZeroingMatrix();
  void FillingMatrixNumber(double number);
  void print_matrix();
};

#endif  // S21_MATRIX_OOP_H
