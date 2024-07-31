#pragma once
#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void CreateMatrix(int rows, int cols);

 public:
  S21Matrix();  //Базовый конструктор, инициализирующий матрицу некоторой
                //заранее заданной размерностью
  S21Matrix(int rows, int cols);  //Параметризированный конструктор с
                                  //количеством строк и столбцов
  S21Matrix(const S21Matrix& other);  //Конструктор копирования
  S21Matrix(S21Matrix&& other) noexcept;  //Конструктор перемещения (переноса)
  ~S21Matrix();  //Деструктор

  S21Matrix operator+(const S21Matrix& other);  //Сложение двух матриц
  S21Matrix operator-(
      const S21Matrix& other);  //Вычитание одной матрицы из другой
  S21Matrix operator*(
      const double num);  //Умножение матриц и умножение матрицы на число
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(
      const S21Matrix& other);  //Проверка на равенство матриц (EqMatrix)
  S21Matrix& operator=(
      const S21Matrix& other);  //Присвоение матрице значений другой матрицы
  S21Matrix& operator+=(
      const S21Matrix& other);  //Присвоение сложения (SumMatrix)
  S21Matrix& operator-=(
      const S21Matrix& other);  //Присвоение разности (SubMatrix)
  S21Matrix& operator*=(
      const S21Matrix& other);  //Присвоение умножения (MulMatrix/MulNumber)
  double& operator()(
      int row, int col);  //Индексация по элементам матрицы (строка, колонка)

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();  //Вычисляет матрицу алгебраических дополнений
                                //текущей матрицы и возвращает ее
  double Determinant();  //Вычисляет и возвращает определитель текущей матрицы
  S21Matrix InverseMatrix();  //Вычисляет и возвращает обратную матрицу

  S21Matrix Minor(int row, int col);

  int GetRows() { return rows_; };
  int GetColumns() { return cols_; };

  void SetRows(const int rows);
  void SetColumns(const int cols);
};
