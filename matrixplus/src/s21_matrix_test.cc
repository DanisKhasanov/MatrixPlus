#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

void FillMatrix(S21Matrix& matrix) {
  for (size_t i = 0; i < (size_t)matrix.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)matrix.GetCols(); ++j) {
      matrix(i, j) = rand() % 20;
    }
  }
}

/*=======================| Конструкторы |==============================*/

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(S21MatrixTest, ParametrizedConstructor) {
  S21Matrix matrix(3, 4);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;

  S21Matrix copy(matrix);
  EXPECT_TRUE(matrix == copy);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;

  S21Matrix original(matrix);
  S21Matrix moved(std::move(matrix));

  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);

  EXPECT_TRUE(original == moved);
}

/*=======================| Методы |==============================*/

/*=======| EqMatrix |=======*/
TEST(EqMatrix, Check) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 5;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 5;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(EqMatrix, EqualMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrix, DifferentMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrix, ZeroMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 0;
  matrix1(0, 1) = 0;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 0;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 0;
  matrix2(0, 1) = 0;
  matrix2(1, 0) = 0;
  matrix2(1, 1) = 0;

  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrix, OneElementDifference) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 5;  // 1 элемент неправильный

  ASSERT_FALSE(matrix1.EqMatrix(matrix2));
}

/*=======| SumMatrix |=======*/
TEST(SumMatrix, DifferentDimensions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);

  ASSERT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(SumMatrix, NullMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2;

  ASSERT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(SumMatrix, SameMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix1.SumMatrix(matrix1);

  ASSERT_EQ(matrix1(0, 0), 2);
  ASSERT_EQ(matrix1(0, 1), 4);
  ASSERT_EQ(matrix1(1, 0), 6);
  ASSERT_EQ(matrix1(1, 1), 8);
}

TEST(SumMatrix, EmptyMatrix) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  ASSERT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

/*=======| SubMatrix |=======*/

TEST(SubMatrix, ValidSubtraction) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 5;
  matrix1(0, 1) = 8;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 9;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  matrix1.SubMatrix(matrix2);

  ASSERT_EQ(matrix1(0, 0), 4);
  ASSERT_EQ(matrix1(0, 1), 6);
  ASSERT_EQ(matrix1(1, 0), -1);
  ASSERT_EQ(matrix1(1, 1), 5);
}

TEST(SubMatrix, DifferentDimensions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(2, 2);

  ASSERT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

TEST(SubMatrix, NullMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2;

  ASSERT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

TEST(SubMatrix, SameMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 5;
  matrix1(0, 1) = 8;
  matrix1(1, 0) = 2;
  matrix1(1, 1) = 9;

  matrix1.SubMatrix(matrix1);

  ASSERT_EQ(matrix1(0, 0), 0);
  ASSERT_EQ(matrix1(0, 1), 0);
  ASSERT_EQ(matrix1(1, 0), 0);
  ASSERT_EQ(matrix1(1, 1), 0);
}

TEST(SubMatrix, EmptyMatrix) {
  S21Matrix matrix1;
  S21Matrix matrix2;

  ASSERT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

/*=======| MulNumber |=======*/

TEST(MulNumber, ValidMultiplication) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  matrix.MulNumber(3);

  ASSERT_EQ(matrix(0, 0), 3);
  ASSERT_EQ(matrix(0, 1), 6);
  ASSERT_EQ(matrix(1, 0), 9);
  ASSERT_EQ(matrix(1, 1), 12);
}

TEST(MulNumber, ZeroMultiplication) {
  S21Matrix matrix(3, 3);
  FillMatrix(matrix);

  matrix.MulNumber(0);

  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      ASSERT_EQ(matrix(i, j), 0);
    }
  }
}

TEST(MulNumber, NegativeMultiplication) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  matrix.MulNumber(-2);

  ASSERT_EQ(matrix(0, 0), -2);
  ASSERT_EQ(matrix(0, 1), -4);
  ASSERT_EQ(matrix(1, 0), -6);
  ASSERT_EQ(matrix(1, 1), -8);
}

TEST(MulNumber, IdentityMatrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(1, 0) = 0;
  matrix(0, 1) = 0;
  matrix(1, 1) = 1;

  matrix.MulNumber(5);

  ASSERT_EQ(matrix(0, 0), 5);
  ASSERT_EQ(matrix(0, 1), 0);
  ASSERT_EQ(matrix(1, 0), 0);
  ASSERT_EQ(matrix(1, 1), 5);
}

/*=======| MulMatrix |=======*/

TEST(MulMatrix, ValidMultiplication) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  matrix1.MulMatrix(matrix2);
  ASSERT_EQ(matrix1(0, 0), 7);
  ASSERT_EQ(matrix1(0, 1), 10);
  ASSERT_EQ(matrix1(1, 0), 15);
  ASSERT_EQ(matrix1(1, 1), 22);
}

TEST(MulMatrix, DifferentDimensions) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(4, 3);

  FillMatrix(matrix1);
  FillMatrix(matrix2);

  ASSERT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

TEST(MulMatrix, ZeroMatrix) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(2, 3);
  matrix1.MulMatrix(matrix2);
  for (int i = 0; i < matrix1.GetRows(); i++) {
    for (int j = 0; j < matrix1.GetCols(); j++) {
      EXPECT_EQ(matrix1(i, j), 0);
    }
  }
}

TEST(MulMatrix, IdentityMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7;
  matrix2(0, 1) = 8;
  matrix2(1, 0) = 9;
  matrix2(1, 1) = 10;
  matrix2(2, 0) = 11;
  matrix2(2, 1) = 12;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 58);
  EXPECT_EQ(matrix1(0, 1), 64);
  EXPECT_EQ(matrix1(1, 0), 139);
  EXPECT_EQ(matrix1(1, 1), 154);
}

TEST(MulMatrix, EmptyMatrix) {
  S21Matrix matrix1;
  S21Matrix matrix2(3, 4);

  ASSERT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

/*=======| Transpose |=======*/

TEST(Transpose, SquareMatrix) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;

  S21Matrix transposed = matrix.Transpose();

  ASSERT_EQ(transposed(0, 0), 1);
  ASSERT_EQ(transposed(0, 1), 4);
  ASSERT_EQ(transposed(0, 2), 7);
  ASSERT_EQ(transposed(1, 0), 2);
  ASSERT_EQ(transposed(1, 1), 5);
  ASSERT_EQ(transposed(1, 2), 8);
  ASSERT_EQ(transposed(2, 0), 3);
  ASSERT_EQ(transposed(2, 1), 6);
  ASSERT_EQ(transposed(2, 2), 9);
}

TEST(Transpose, RectangularMatrix) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_EQ(transposed(0, 0), 1);
  EXPECT_EQ(transposed(0, 1), 4);
  EXPECT_EQ(transposed(1, 0), 2);
  EXPECT_EQ(transposed(1, 1), 5);
  EXPECT_EQ(transposed(2, 0), 3);
  EXPECT_EQ(transposed(2, 1), 6);
}

TEST(Transpose, SingleElementMatrix) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 42;

  S21Matrix transposed = matrix.Transpose();

  ASSERT_EQ(transposed(0, 0), 42);
}

/*=======| CalcComplements |=======*/

TEST(CalcComplements, ValidCalcComplements) {
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

TEST(CalcComplements, DifferentDimensions) {
  S21Matrix matrix1(3, 2);
  EXPECT_THROW(matrix1.CalcComplements(), std::invalid_argument);
}

/*=======| Determinant |=======*/

TEST(Determinant, ValidDeterminant) {
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

TEST(Determinant, ZeroDeterminant) {
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

/*=======| InverseMatrix |=======*/

TEST(InverseMatrix, ValidInverseMatrix) {
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

TEST(InverseMatrix, DiffInverseMatrix) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 1;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = 1;
  EXPECT_THROW(matrix1.InverseMatrix(), std::invalid_argument);
}

/*==========================| Операторы |============================*/

/*=======| Operator + |=======*/
TEST(OperatorPlus, PositiveValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  S21Matrix result = matrix1 + matrix2;

  ASSERT_EQ(result(0, 0), 6);
  ASSERT_EQ(result(0, 1), 8);
  ASSERT_EQ(result(1, 0), 10);
  ASSERT_EQ(result(1, 1), 12);
}

TEST(OperatorPlus, NegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = -1;
  matrix1(0, 1) = -2;
  matrix1(1, 0) = -3;
  matrix1(1, 1) = -4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = -5;
  matrix2(0, 1) = -6;
  matrix2(1, 0) = -7;
  matrix2(1, 1) = -8;

  S21Matrix result = matrix1 + matrix2;

  ASSERT_EQ(result(0, 0), -6);
  ASSERT_EQ(result(0, 1), -8);
  ASSERT_EQ(result(1, 0), -10);
  ASSERT_EQ(result(1, 1), -12);
}

/*=======| Operator - |=======*/

TEST(OperatorMinus, PositiveValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 5;
  matrix1(0, 1) = 8;
  matrix1(1, 0) = 12;
  matrix1(1, 1) = 16;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  S21Matrix result = matrix1 - matrix2;

  ASSERT_EQ(result(0, 0), 4);
  ASSERT_EQ(result(0, 1), 6);
  ASSERT_EQ(result(1, 0), 9);
  ASSERT_EQ(result(1, 1), 12);
}

TEST(OperatorMinus, NegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = -1;
  matrix1(0, 1) = -2;
  matrix1(1, 0) = -3;
  matrix1(1, 1) = -4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = -5;
  matrix2(0, 1) = -6;
  matrix2(1, 0) = -7;
  matrix2(1, 1) = -8;

  S21Matrix result = matrix1 - matrix2;

  ASSERT_EQ(result(0, 0), 4);
  ASSERT_EQ(result(0, 1), 4);
  ASSERT_EQ(result(1, 0), 4);
  ASSERT_EQ(result(1, 1), 4);
}
/*=======| Operator * (num) |=======*/

TEST(OperatorMultNumber, PositiveValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  double num = 2;

  S21Matrix result = matrix1 * num;
  S21Matrix result2 = matrix1 * num;

  ASSERT_EQ(result(0, 0), 2);
  ASSERT_EQ(result(0, 1), 4);
  ASSERT_EQ(result(1, 0), 6);
  ASSERT_EQ(result(1, 1), 8);

  ASSERT_EQ(result2(0, 0), 2);
  ASSERT_EQ(result2(0, 1), 4);
  ASSERT_EQ(result2(1, 0), 6);
  ASSERT_EQ(result2(1, 1), 8);
}

TEST(OperatorMultNumber, NegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  double num = -2;

  S21Matrix result = matrix1 * num;

  ASSERT_EQ(result(0, 0), -2);
  ASSERT_EQ(result(0, 1), -4);
  ASSERT_EQ(result(1, 0), -6);
  ASSERT_EQ(result(1, 1), -8);
}
/*=======| Operator * (matrix) |=======*/

TEST(OperatorMultMatr, ValidMultiplication) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  S21Matrix result = matrix1 * matrix2;
  ASSERT_EQ(result(0, 0), 0);
  ASSERT_EQ(result(0, 1), 0);
  ASSERT_EQ(result(1, 0), 0);
  ASSERT_EQ(result(1, 1), 0);
}

TEST(OperatorMultMatr, DifferentSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  S21Matrix result = matrix1 * matrix2;
  ASSERT_EQ(result(0, 0), 0);
  ASSERT_EQ(result(0, 1), 0);
  ASSERT_EQ(result(1, 0), 0);
  ASSERT_EQ(result(1, 1), 0);
}

/*=======| Operator = |=======*/

TEST(OperatorAssignment, ValidAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2 = matrix1;

  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(OperatorAssignment, EmptyMatrix) {
  S21Matrix matrix1;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  matrix1 = matrix2;

  ASSERT_TRUE(matrix1 == matrix2);
}

/*=======| Operator == |=======*/

TEST(OperatorEquality, EqualMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  ASSERT_TRUE(matrix1 == matrix2);
}

TEST(OperatorEquality, DifferentMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  ASSERT_FALSE(matrix1 == matrix2);
}

/*=======| Operator += |=======*/

TEST(OperatorPlusEqual, PositiveValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  matrix1 += matrix2;

  ASSERT_EQ(matrix1(0, 0), 6);
  ASSERT_EQ(matrix1(0, 1), 8);
  ASSERT_EQ(matrix1(1, 0), 10);
  ASSERT_EQ(matrix1(1, 1), 12);
}

TEST(OperatorPlusEqual, NegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = -1;
  matrix1(0, 1) = -2;
  matrix1(1, 0) = -3;
  matrix1(1, 1) = -4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = -5;
  matrix2(0, 1) = -6;
  matrix2(1, 0) = -7;
  matrix2(1, 1) = -8;

  matrix1 += matrix2;

  ASSERT_EQ(matrix1(0, 0), -6);
  ASSERT_EQ(matrix1(0, 1), -8);
  ASSERT_EQ(matrix1(1, 0), -10);
  ASSERT_EQ(matrix1(1, 1), -12);
}

/*=======| Operator -= |=======*/

TEST(OperatorMinusEqual, PositiveValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 5;
  matrix1(0, 1) = 8;
  matrix1(1, 0) = 12;
  matrix1(1, 1) = 16;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  matrix1 -= matrix2;

  ASSERT_EQ(matrix1(0, 0), 4);
  ASSERT_EQ(matrix1(0, 1), 6);
  ASSERT_EQ(matrix1(1, 0), 9);
  ASSERT_EQ(matrix1(1, 1), 12);
}

TEST(OperatorMinusEqual, NegativeValues) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = -1;
  matrix1(0, 1) = -2;
  matrix1(1, 0) = -3;
  matrix1(1, 1) = -4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = -5;
  matrix2(0, 1) = -6;
  matrix2(1, 0) = -7;
  matrix2(1, 1) = -8;

  matrix1 -= matrix2;

  ASSERT_EQ(matrix1(0, 0), 4);
  ASSERT_EQ(matrix1(0, 1), 4);
  ASSERT_EQ(matrix1(1, 0), 4);
  ASSERT_EQ(matrix1(1, 1), 4);
}

/*=======| Operator *=(num) |=======*/

TEST(OperatorMulEqualNum, PositiveValue) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 2;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;

  double num = 2;

  matrix1 *= num;

  ASSERT_EQ(matrix1(0, 0), 4);
  ASSERT_EQ(matrix1(0, 1), 6);
  ASSERT_EQ(matrix1(1, 0), 8);
  ASSERT_EQ(matrix1(1, 1), 10);
}

TEST(OperatorMulEqualNum, NegativeValue) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 2;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;

  double num = -2;

  matrix1 *= num;

  ASSERT_EQ(matrix1(0, 0), -4);
  ASSERT_EQ(matrix1(0, 1), -6);
  ASSERT_EQ(matrix1(1, 0), -8);
  ASSERT_EQ(matrix1(1, 1), -10);
}

/*=======| Operator *=(matrix) |=======*/

TEST(OperatorMulEqualMatr, MultiplyMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 2;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  matrix1 *= matrix2;
  ASSERT_EQ(matrix1(0, 0), 11);
  ASSERT_EQ(matrix1(0, 1), 16);
  ASSERT_EQ(matrix1(1, 0), 19);
  ASSERT_EQ(matrix1(1, 1), 28);
}

TEST(OperatorMulEqualMatr, MulMatDiffSizes) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 2;
  matrix1(0, 1) = 3;
  matrix1(0, 2) = 4;
  matrix1(1, 0) = 5;
  matrix1(1, 1) = 6;
  matrix1(1, 2) = 7;
  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  matrix2(2, 0) = 5;
  matrix2(2, 1) = 6;
  matrix1 *= matrix2;
  ASSERT_EQ(matrix1(0, 0), 31);
  ASSERT_EQ(matrix1(0, 1), 40);
  ASSERT_EQ(matrix1(1, 0), 58);
  ASSERT_EQ(matrix1(1, 1), 76);
}

/*==========================| Сеттеры и геттеры |============================*/

/*=======| SetRows |=======*/
TEST(SetRows, PositiveValue) {
  S21Matrix matrix(2, 2);
  matrix.SetRows(3);

  ASSERT_EQ(matrix.GetRows(), 3);
}

TEST(SetRows, NegativeValue) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix.SetRows(-1), std::out_of_range);
}

TEST(SetRows, ZeroValue) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix.SetRows(0), std::out_of_range);
}

/*=======| SetCols |=======*/

TEST(SetCols, PositiveValue) {
  S21Matrix matrix(2, 2);
  matrix.SetCols(3);
  ASSERT_EQ(matrix.GetCols(), 3);
}

TEST(SetCols, NegativeValue) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix.SetCols(-1), std::out_of_range);
}

TEST(SetCols, ZeroValue) {
  S21Matrix matrix(2, 2);
  ASSERT_THROW(matrix.SetCols(0), std::out_of_range);
}

/*=======| GetRows |=======*/

TEST(S21MatrixTest, GetRows) {
  S21Matrix matrix(3, 2);
  ASSERT_EQ(matrix.GetRows(), 3);
}

/*=======| GetCols |=======*/

TEST(S21MatrixTest, GetCols) {
  S21Matrix matrix(2, 3);

  ASSERT_EQ(matrix.GetCols(), 3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
