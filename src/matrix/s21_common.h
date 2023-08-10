#ifndef SRC_S21_COMMON_H_
#define SRC_S21_COMMON_H_

#include "s21_matrix.h"

// Проверяет, что у матрицы строк > 0 и столбцов > 0
int is_valid_matrix(matrix_t *M);

int near_null(double x);

void get_matrix_without_row_and_column(matrix_t *M, int size, int row, int col,
                                       matrix_t *R);

#endif  // SRC_S21_COMMON_H_