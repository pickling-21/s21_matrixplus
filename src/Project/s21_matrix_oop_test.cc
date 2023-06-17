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
  a.FillingMatrix();

  S21Matrix b(a);

  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(constructor, move) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);
  a.FillingMatrix();
  b.FillingMatrix();

  S21Matrix moved = std::move(a);

  EXPECT_TRUE(moved.EqMatrix(b));
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_TRUE(a.IsEmpty());
}

TEST(set_rows_suite, reduce_test) {
  S21Matrix a(3, 3);
  S21Matrix b(4, 3);

  a.FillingMatrix();
  b.FillingMatrix();

  std::cout << "aaa\n";

  a.print_matrix();

  std::cout << "bbb\n";

  b.SetRows(3);

  b.print_matrix();

  EXPECT_TRUE(a == b);
}

TEST(set_rows_suite, decrease_test) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 3);

  a.FillingMatrix();
  b.FillingMatrix();

  for (size_t i = 0; i < (size_t)a.GetCols(); ++i) {
    a(2, i) = 0;
  }

  b.SetRows(3);
  EXPECT_TRUE(a == b);
}

TEST(set_cols_suite, reduce_test) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 4);

  a.FillingMatrix();
  b.FillingMatrix();

  b.SetCols(3);

  EXPECT_TRUE(a == b);
}

TEST(set_cols_suite, decrease_test) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 2);

  a.FillingMatrix();
  b.FillingMatrix();
  for (size_t i = 0; i < (size_t)a.GetRows(); ++i) {
    a(i, 2) = 0;
  }

  b.SetCols(3);

  EXPECT_TRUE(a == b);
}

TEST(eq_suite, basic) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);

  a.FillingMatrix();
  b.FillingMatrix();

  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(eq_suite, not_eq) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);

  a.ZeroingMatrix();
  b.FillingMatrix();

  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(eq_suite, not_eq_1) {
  S21Matrix a(3, 2);
  S21Matrix b(3, 3);

  a.FillingMatrix();
  b.FillingMatrix();

  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(eq_suite, not_eq_2) {
  S21Matrix a(3, 3);
  S21Matrix b(1, 3);

  a.FillingMatrix();
  b.FillingMatrix();

  EXPECT_FALSE(a.EqMatrix(b));
}

TEST(eq_suite, accuracy) {
  S21Matrix a(4, 3);
  S21Matrix b(4, 3);

  a.FillingMatrix();
  b.FillingMatrix();

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

  a.FillingMatrix();
  b.FillingMatrix();

  for (size_t i = 0; i < (size_t)a.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)a.GetCols(); ++j) {
      a(i, j) -= 1e-8;
    }
  }
  EXPECT_TRUE(a.EqMatrix(b));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}