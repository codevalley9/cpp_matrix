#include "gtest/gtest.h"
#include "s21_matrix.h"

TEST(cnstr, create) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetColumns(), 1);
}

TEST(cnstr, indexes) {
  S21Matrix matrix(84, 300);
  EXPECT_EQ(matrix.GetRows(), 84);
  EXPECT_EQ(matrix.GetColumns(), 300);
}

TEST(cnstr, copy) {
  S21Matrix matrix_1(4, 3);
  S21Matrix matrix_2(matrix_1);
  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(cnstr, move) {
  S21Matrix matrix_1(52, 5);
  S21Matrix matrix_2(52, 5);
  S21Matrix move(std::move(matrix_1));

  EXPECT_TRUE(move == matrix_2);
  EXPECT_EQ(matrix_1.GetRows(), 0);
  EXPECT_EQ(matrix_1.GetColumns(), 0);
  EXPECT_THROW(matrix_1(1, 1), std::out_of_range);
}

TEST(set, col) {
  S21Matrix matrix_1(3, 3);
  S21Matrix matrix_2(3, 4);
  matrix_2.SetColumns(3);
  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(operators, value) {
  S21Matrix matrix_1(3, 50);
  S21Matrix matrix_2(54, 5);
  matrix_1 = matrix_2;
  EXPECT_EQ(matrix_1.GetRows(), 54);
  EXPECT_EQ(matrix_1.GetColumns(), 5);
}

TEST(eq_suite, not_eq_1) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(eq_suite, not_eq_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(1, 3);

  EXPECT_FALSE(matrix1 == matrix2);
}



TEST(sum_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1.SumMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 6.0);
  EXPECT_EQ(matrix1(0, 1), 8.0);
  EXPECT_EQ(matrix1(1, 0), 10.0);
  EXPECT_EQ(matrix1(1, 1), 12.0);
}


TEST(sum_suite, exception) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(24, 2);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::out_of_range);
}

TEST(sub_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1.SubMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), -4.0);
  EXPECT_EQ(matrix1(0, 1), -4.0);
  EXPECT_EQ(matrix1(1, 0), -4.0);
  EXPECT_EQ(matrix1(1, 1), -4.0);
}


TEST(sub_suite, exception) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(24, 2);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::out_of_range);
}

TEST(mul_number_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  double num = 2.0;
  matrix1.MulNumber(num);

  EXPECT_EQ(matrix1(0, 0), 2.0);
  EXPECT_EQ(matrix1(0, 1), 4.0);
  EXPECT_EQ(matrix1(1, 0), 6.0);
  EXPECT_EQ(matrix1(1, 1), 8.0);
}

TEST(mul_matrix_suite, basic) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 58.0);
  EXPECT_EQ(matrix1(0, 1), 64.0);
  EXPECT_EQ(matrix1(1, 0), 139.0);
  EXPECT_EQ(matrix1(1, 1), 154.0);
}

TEST(mul_matrix_suite, exception) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(24, 2);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::out_of_range);
}

TEST(transpose_suite, basic) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix result = matrix1.Transpose();

  EXPECT_EQ(result(0, 0), 1.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 0), 2.0);
  EXPECT_EQ(result(1, 1), 5.0);
  EXPECT_EQ(result(2, 0), 3.0);
  EXPECT_EQ(result(2, 1), 6.0);
}

TEST(calc_complements_suite, basic) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  matrix1(2, 0) = 7.0;
  matrix1(2, 1) = 8.0;
  matrix1(2, 2) = 9.0;

  S21Matrix result = matrix1.CalcComplements();

  EXPECT_EQ(result(0, 0), -3.0);
  EXPECT_EQ(result(0, 1), 6.0);
  EXPECT_EQ(result(0, 2), -3.0);
  EXPECT_EQ(result(1, 0), 6.0);
  EXPECT_EQ(result(1, 1), -12.0);
  EXPECT_EQ(result(1, 2), 6.0);
  EXPECT_EQ(result(2, 0), -3.0);
  EXPECT_EQ(result(2, 1), 6.0);
  EXPECT_EQ(result(2, 2), -3.0);
}

TEST(calc_complements_suite, exception) {
  S21Matrix matrix1(3, 2);
  EXPECT_THROW(matrix1.CalcComplements(), std::invalid_argument);
}

TEST(determinant_suite, basic_2_2) {
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix2.Determinant(), -2.0);
}

TEST(determinant_suite, basic_3_3) {
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

TEST(determinant_suite, zero_det) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  matrix1(2, 0) = 7.0;
  matrix1(2, 1) = 8.0;
  matrix1(2, 2) = 9.0;

  EXPECT_EQ(matrix1.Determinant(), 0.0);
}

TEST(determinant_suite, exception) {
  S21Matrix matrix4(2, 3);
  EXPECT_THROW(matrix4.Determinant(), std::invalid_argument);
}

TEST(inverse_matrix_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix result = matrix1.InverseMatrix();

  EXPECT_EQ(result(0, 0), -2);
  EXPECT_EQ(result(0, 1), 1);
  EXPECT_EQ(result(1, 0), 1.5);
  EXPECT_EQ(result(1, 1), -0.5);
}

TEST(overloads, equals) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 1.0;
  matrix3(0, 1) = 2.0;
  matrix3(1, 0) = 4.0;
  matrix3(1, 1) = 5.0;

  EXPECT_TRUE(matrix1 == matrix2);
  EXPECT_FALSE(matrix1 == matrix3);
}

TEST(overloads_assignment, copy_same) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1 = matrix1;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(overloads, plus) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 3.0;
  matrix3(0, 1) = 5.0;
  matrix3(1, 0) = 7.0;
  matrix3(1, 1) = 9.0;

  S21Matrix result = matrix1 + matrix2;
  EXPECT_TRUE(matrix3 == result);
}

TEST(overloads, minus) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = -1.0;
  matrix3(0, 1) = -1.0;
  matrix3(1, 0) = -1.0;
  matrix3(1, 1) = -1.0;

  S21Matrix result = matrix1 - matrix2;
  EXPECT_TRUE(result == matrix3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}