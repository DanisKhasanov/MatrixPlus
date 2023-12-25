
#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ > 0 && cols_ > 0) {
    CreateMatrix();
  } else {
    throw std::out_of_range("Invalid matrix size");
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  if (CheckMatrix(other)) {
    return false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > eps) return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (CheckMatrix(other)) {
    throw std::invalid_argument(
        "Invalid argument! Different matrix dimensions");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (CheckMatrix(other)) {
    throw std::invalid_argument(
        "Invalid argument! Different matrix dimensions");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Invalid argument! Different matrix dimensions");
  } else {
    S21Matrix res(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int m = 0; m < other.rows_; m++) {
          res.matrix_[i][j] += matrix_[i][m] * other.matrix_[m][j];
        }
      }
    }

    *this = res;
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      res.matrix_[i][j] = matrix_[j][i];
    }
  }
  return res;
}

S21Matrix S21Matrix::MinorMatrix(const int x, const int y) {
  if (x < 0 || x >= rows_ || y < 0 || y >= cols_) {
    throw std::invalid_argument(
        "Invalid argument! Different matrix dimensions");
  } else {
    S21Matrix res(rows_ - 1, cols_ - 1);
    for (int i = 0, min_i = 0; min_i < res.rows_; ++min_i) {
      if (x == i) ++i;
      for (int j = 0, min_j = 0; min_j < res.cols_; ++min_j) {
        if (y == j) ++j;
        res.matrix_[min_i][min_j] = matrix_[i][j];
        ++j;
      }
      ++i;
    }
    return res;
  }
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix res(rows_, cols_);
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Invalid argument! Different matrix dimensions");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor = MinorMatrix(i, j);
        res.matrix_[i][j] = pow((-1), i + j) * minor.Determinant();
      }
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Invalid argument! Different matrix dimensions");
  } else {
    double res = 0.0;
    if (rows_ == 1) {
      res = matrix_[0][0];
    } else if (rows_ == 2) {
      res = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else {
      for (int i = 0; i < cols_; i++) {
        S21Matrix minor = MinorMatrix(0, i);
        res += matrix_[0][i] * pow(-1, i) * minor.Determinant();
      }
    }
    return res;
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (fabs(determinant) < eps) {
    throw std::invalid_argument("Matrix determinant is 0");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    S21Matrix tmp = CalcComplements();
    res = tmp.Transpose();
    res.MulNumber(1 / determinant);
  }
  return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix operator*(double num, S21Matrix &other) {
  S21Matrix res(other);
  res.MulNumber(num);
  return res;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix temp_matrix(other);
  std::swap(rows_, temp_matrix.rows_);
  std::swap(cols_, temp_matrix.cols_);
  std::swap(matrix_, temp_matrix.matrix_);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(const int i, const int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::out_of_range("Index outside the matrix");
  return matrix_[i][j];
}

double S21Matrix::operator()(const int i, const int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::out_of_range("Index outside the matrix");
  return matrix_[i][j];
}

void S21Matrix::SetCols(const int cols) {
  if (cols < 0) {
    throw std::out_of_range("Invalid matrix size");
  }
  S21Matrix temp_matrix(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < std::min(cols, cols_); j++) {
      temp_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp_matrix;
}

void S21Matrix::SetRows(const int rows) {
  if (rows < 0) {
    throw std::out_of_range("Invalid matrix size");
  }
  S21Matrix temp_matrix(rows, cols_);
  for (int i = 0; i < std::min(rows, rows_); i++) {
    for (int j = 0; j < cols_; j++) {
      temp_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp_matrix;
}

int S21Matrix::GetCols() { return cols_; }

int S21Matrix::GetRows() { return rows_; }

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

bool S21Matrix::CheckMatrix(const S21Matrix &other) const {
  return (cols_ != other.cols_ || rows_ != other.rows_ || matrix_ == nullptr ||
          other.matrix_ == nullptr)
             ? true
             : false;
}
