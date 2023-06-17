#include "s21_matrix_oop.h"

#include <cmath>
#include <iostream>

#include "gtest/gtest.h"

TEST(constructor, basic) {
  S21Matrix a;
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_EQ(a.GetRows(), 0);
}

TEST(constructor, two_args) {
  S21Matrix a(2, 3);
  EXPECT_EQ(a.GetCols(), 3);
  EXPECT_EQ(a.GetRows(), 2);
}

TEST(constructor, copy) {
  S21Matrix a(4, 3);
  a.FillingMatrixRandom();

  S21Matrix b(a);

  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(constructor, move) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);
  a.FillingMatrixRandom();
  b.FillingMatrixRandom();

  S21Matrix moved = std::move(a);

  EXPECT_TRUE(moved.EqMatrix(b));
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_TRUE(a.IsEmpty());
}

TEST(set_rows_suite, reduce_test) {
  S21Matrix a(3, 3);
  S21Matrix b(4, 3);

  a.FillingMatrixRandom();
  b.FillingMatrixRandom();

  b.SetRows(3);

  EXPECT_TRUE(a == b);
}

TEST(set_rows_suite, decrease_test) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 3);

  a.FillingMatrixRandom();
  b.FillingMatrixRandom();

  for (size_t i = 0; i < (size_t)a.GetCols(); ++i) {
    a(2, i) = 0;
  }

  b.SetRows(3);
  EXPECT_TRUE(a == b);
}

TEST(set_cols_suite, reduce_test) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 4);

  a.FillingMatrixNumber(1);
  b.FillingMatrixNumber(1);

  b.SetCols(3);

  EXPECT_TRUE(a == b);
}

TEST(set_cols_suite, decrease_test) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 2);

  a.FillingMatrixNumber(3);
  b.FillingMatrixNumber(3);

  for (size_t i = 0; i < (size_t)a.GetRows(); ++i) {
    a(i, 2) = 0;
  }

  b.SetCols(3);

  EXPECT_TRUE(a == b);
}

TEST(eq_suite, basic) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);

  a.FillingMatrixRandom();
  b.FillingMatrixRandom();

  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(eq_suite, not_eq) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);

  a.FillingMatrixNumber(0);
  b.FillingMatrixRandom();

  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(eq_suite, not_eq_1) {
  S21Matrix a(3, 2);
  S21Matrix b(3, 3);

  a.FillingMatrixRandom();
  b.FillingMatrixRandom();

  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(eq_suite, not_eq_2) {
  S21Matrix a(3, 3);
  S21Matrix b(1, 3);

  a.FillingMatrixRandom();
  b.FillingMatrixRandom();

  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(eq_suite, accuracy) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);

  a.FillingMatrixRandom();
  b.FillingMatrixRandom();

  for (size_t i = 0; i < (size_t)a.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)a.GetCols(); ++j) {
      a(i, j) += 1e-8;
    }
  }
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(eq_suite, accuracy_1) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);

  a.FillingMatrixRandom();
  b.FillingMatrixRandom();

  for (size_t i = 0; i < (size_t)a.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)a.GetCols(); ++j) {
      a(i, j) -= 1e-8;
    }
  }
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(sum_suite, basic) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b(2, 2);
  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  a.SumMatrix(b);

  EXPECT_EQ(a(0, 0), 6);
  EXPECT_EQ(a(0, 1), 8);
  EXPECT_EQ(a(1, 0), 10);
  EXPECT_EQ(a(1, 1), 12);
}

TEST(sum_suite, random_number) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(3, 4);

  // Заполнение матриц случайными числами
  matrix1.FillingMatrixRandom();
  matrix2.FillingMatrixRandom();

  S21Matrix expected_result(3, 4);

  // Вычисление ожидаемого результата
  for (size_t i = 0; i < (size_t)expected_result.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)expected_result.GetCols(); ++j) {
      expected_result(i, j) = matrix1(i, j) + matrix2(i, j);
    }
  }

  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(expected_result));
}

// TEST(sum_suite, exception) {
//   S21Matrix a(2, 2);
//   S21Matrix b(24, 2);
//   EXPECT_THROW(a.SumMatrix(b), std::out_of_range);
// }

TEST(sub_suite, basic) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b(2, 2);
  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  a.SubMatrix(b);

  EXPECT_EQ(a(0, 0), -4);
  EXPECT_EQ(a(0, 1), -4);
  EXPECT_EQ(a(1, 0), -4);
  EXPECT_EQ(a(1, 1), -4);
}

TEST(sub_suite, random_number) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(3, 4);

  // Заполнение матриц случайными числами
  matrix1.FillingMatrixRandom();
  matrix2.FillingMatrixRandom();

  S21Matrix expected_result(3, 4);

  // Вычисление ожидаемого результата
  for (size_t i = 0; i < (size_t)expected_result.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)expected_result.GetCols(); ++j) {
      expected_result(i, j) = matrix1(i, j) - matrix2(i, j);
    }
  }

  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(expected_result));
}

// TEST(sub_suite, exception) {
//   S21Matrix a(2, 2);
//   S21Matrix b(24, 2);
//   EXPECT_THROW(a.SubMatrix(b), std::out_of_range);
// }

TEST(mul_number_suite, basic) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  double num = 2.0;
  a.MulNumber(num);

  EXPECT_EQ(a(0, 0), 2);
  EXPECT_EQ(a(0, 1), 4);
  EXPECT_EQ(a(1, 0), 6);
  EXPECT_EQ(a(1, 1), 8);
}
TEST(mul_matrix_suite, basic) {
  S21Matrix a(2, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;

  S21Matrix b(3, 2);
  b(0, 0) = 7;
  b(0, 1) = 8;
  b(1, 0) = 9;
  b(1, 1) = 10;
  b(2, 0) = 11;
  b(2, 1) = 12;

  a.MulMatrix(b);

  EXPECT_EQ(a(0, 0), 58);
  EXPECT_EQ(a(0, 1), 64);
  EXPECT_EQ(a(1, 0), 139);
  EXPECT_EQ(a(1, 1), 154);
}

TEST(mul_matrix_suite, random_number) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(4, 5);

  // Заполнение матриц случайными числами
  matrix1.FillingMatrixRandom();
  matrix2.FillingMatrixRandom();

  S21Matrix expected_result(3, 5);

  // Вычисление ожидаемого результата
  for (size_t i = 0; i < (size_t)expected_result.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)expected_result.GetCols(); ++j) {
      expected_result(i, j) = 0;
      for (size_t k = 0; k < (size_t)matrix1.GetCols(); ++k) {
        expected_result(i, j) =
            expected_result(i, j) + matrix1(i, k) * matrix2(k, j);
      }
    }
  }

  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(expected_result));
}

// TEST(mul_matrix_suite, exception) {
//   S21Matrix a(2, 2);
//   S21Matrix b(24, 2);
//   EXPECT_THROW(a.MulMatrix(b), std::out_of_range);
// }

TEST(transpose_suite, basic) {
  S21Matrix a(2, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  S21Matrix result = a.Transpose();
  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 5);
  EXPECT_EQ(result(2, 0), 3);
  EXPECT_EQ(result(2, 1), 6);
}

TEST(calc_complements_suite, basic) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  S21Matrix result = a.CalcComplements();

  EXPECT_EQ(result(0, 0), -3);
  EXPECT_EQ(result(0, 1), 6);
  EXPECT_EQ(result(0, 2), -3);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), -12);
  EXPECT_EQ(result(1, 2), 6);
  EXPECT_EQ(result(2, 0), -3);
  EXPECT_EQ(result(2, 1), 6);
  EXPECT_EQ(result(2, 2), -3);
}

// TEST(calc_complements_suite, exception) {
//   S21Matrix a(3, 2);
//   EXPECT_THROW(a.CalcComplements(), std::invalid_argument);
// }

TEST(determinant_suite, square_matrix) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  double result = a.Determinant();

  EXPECT_EQ(result, 0);
}

TEST(determinant_suite, basic_2) {
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;
  EXPECT_DOUBLE_EQ(matrix2.Determinant(), -2.0);
}

TEST(determinant_suite, basic_3) {
  S21Matrix matrix3(3, 3);
  matrix3(0, 0) = 6.0;
  matrix3(0, 1) = 1.0;
  matrix3(0, 2) = 1.0;
  matrix3(1, 0) = 4.0;
  matrix3(1, 1) = -2.0;
  matrix3(1, 2) = 5.0;
  matrix3(2, 0) = 2.0;
  matrix3(2, 1) = 8.0;
  matrix3(2, 2) = 7.0;
  EXPECT_DOUBLE_EQ(matrix3.Determinant(), -306.0);
}

// TEST(determinant_suite, exception) {
//   S21Matrix matrix4(2, 3);
//   EXPECT_THROW(matrix4.Determinant(), std::invalid_argument);
// }

TEST(inverse_matrix_suite, basic) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix result = a.InverseMatrix();

  EXPECT_EQ(result(0, 0), -2);
  EXPECT_EQ(result(0, 1), 1);
  EXPECT_EQ(result(1, 0), 1.5);
  EXPECT_EQ(result(1, 1), -0.5);
}

// TEST(inverse_matrix_suite, exception) {
//   S21Matrix mat(2, 2);
//   mat.FillingMatrixNumber(1);
//   EXPECT_THROW(mat.InverseMatrix(), std::invalid_argument);
// }
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}