#include "s21_common.h"
#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = OK;
  int rows = A->rows;
  int columns = A->columns;
  s21_create_matrix(columns, rows, result);
  if (is_valid_matrix(A))
    status = INCORRECT_MATRIX;
  else {
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++) result->matrix[j][i] = A->matrix[i][j];
  }
  return status;
}