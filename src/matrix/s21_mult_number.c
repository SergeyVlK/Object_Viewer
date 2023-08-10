#include "s21_common.h"
#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;
  int rows = A->rows;
  int columns = A->columns;
  if (is_valid_matrix(A))
    status = INCORRECT_MATRIX;
  else {
    s21_create_matrix(rows, columns, result);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
  }
  return status;
}