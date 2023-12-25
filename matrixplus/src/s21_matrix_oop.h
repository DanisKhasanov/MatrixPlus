#ifndef CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_S21_MATRIX_OOP_H_

#include <math.h>

#include <iostream>

const double eps = 1e-07;

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other) const noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  friend S21Matrix operator*(double num, S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(const int i, const int j);
  double operator()(int i, int j) const;

  void SetRows(const int rows);
  void SetCols(const int cols);
  int GetRows();
  int GetCols();

 private:
  int rows_, cols_;
  double **matrix_;
  void CreateMatrix();
  bool CheckMatrix(const S21Matrix &other) const;
  S21Matrix MinorMatrix(const int x, const int y);
};

#endif  // CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_S21_MATRIX_OOP_H_