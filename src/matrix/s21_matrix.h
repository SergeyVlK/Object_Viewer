#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

#define EPS 1e-07

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Очистка матриц
void s21_remove_matrix(matrix_t *A);

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Умножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

// Матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_