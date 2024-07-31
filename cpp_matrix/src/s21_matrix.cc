#include "s21_matrix.h"

void S21Matrix::CreateMatrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix() { CreateMatrix(1, 1); }

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range("Please input correct number of rows and columns");
  }
  CreateMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;

  CreateMatrix(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

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
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix operator*(double num, S21Matrix &matrix) {
  S21Matrix result(matrix);
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
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

// Перегрузка оператора присваивания для класса S21Matrix
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (&other != this) {  // Проверка на самоприсваивание: &other != this
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      delete[] matrix_[0];  // Освобождение памяти текущей матрицы, если размеры
                            // различны
      delete[] matrix_;
      CreateMatrix(other.rows_, other.cols_);
    }  // Создание новой матрицы с размерами другой матрицы (other)

    // Присваивание размеров матрицы
    rows_ = other.rows_;
    cols_ = other.cols_;

    // Копирование значений из матрицы other в текущую матрицу
    for (size_t i = 0; i < (size_t)rows_; i++) {
      for (size_t j = 0; j < (size_t)cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;  // Возвращение ссылки на текущий объект
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || col < 0 || row < 0) {
    throw std::out_of_range("Please input correct number of rows and columns");
  }
  return matrix_[row][col];
}  //если индексы корректны, функция возвращает ссылку на элемент матрицы по
   //заданным координатам

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
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
    throw std::out_of_range("Please input the same size for matrices");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Please input the same size for matrices");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
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
    throw std::out_of_range(
        "The number of columns of the first matrix "
        "must be equal to the number of rows of the second matrix");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::invalid_argument("Please use square matrix");
  }  // Вычисляем алгебраические дополнения для каждого элемента матрицы
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j != cols_; j++) {
      S21Matrix minor_matrix =
          Minor(i, j);  // Получаем минор для каждого элемента
      // Вычисляем алгебраическое дополнение и учитываем знак (-1)^(i+j)
      result.matrix_[i][j] = pow((-1), i + j) * minor_matrix.Determinant();
    }
  }
  return result;  // Возвращаем матрицу с алгебраическими дополнениями
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Please use square matrix");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor_matrix =
          Minor(0, j);  // Получаем минор для каждого элемента первой строки
      result +=
          matrix_[0][j] * pow(-1, j) *
          minor_matrix.Determinant();  // Вычисляем сумму по элементам первой
                                       // строки с учетом знака (-1)^j
    }
  }
  return result;
}

S21Matrix S21Matrix::Minor(int row, int col) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  // Заполняем минор значениями, исключая указанную строку и столбец
  for (int i = 0, min_i = 0; min_i < result.rows_; min_i++) {
    if (row == i) i++;  // Пропускаем указанную строку
    for (int j = 0, min_j = 0; min_j < result.cols_; min_j++) {
      if (col == j) j++;  // Пропускаем указанный столбец
      result.matrix_[min_i][min_j] = matrix_[i][j];
      j++;
    }
    i++;
  }
  return result;  // Возвращаем полученный минор
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (fabs(det) <
      1e-7) {  // Проверяем, не является ли определитель слишком близким к нулю
    throw std::invalid_argument(
        "Sorry, inverse matrix is impossible becouse determinant is 0");
  }
  S21Matrix result(rows_,
                   cols_);  // Создаем матрицу для хранения обратной матрицы
  if (rows_ == 1) {  // Обратная матрица для 1x1: result = 1 / matrix_[0][0]
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    S21Matrix tmp = CalcComplements();
    result = tmp.Transpose();  // Получаем алгебраические дополнения и
                               // транспонируем их
    result.MulNumber(
        1 / det);  // Умножаем каждый элемент на обратное значение определителя
  }
  return result;  // Возвращаем полученную обратную матрицу
}

void S21Matrix::SetRows(const int rows) {
  if (rows < 1) {
    throw std::out_of_range(
        "Please input correct number of rows, this is not the case now");
  }
  S21Matrix result(rows, cols_);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i < rows_) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::SetColumns(const int cols) {
  if (cols < 1) {
    throw std::out_of_range(
        "Please input correct number of columns, this is not the case now");
  }
  S21Matrix result(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j < cols_) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}
