
#include "s21_common.h"
#include "s21_matrix.h"
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  int rows = A->rows;
  int columns = A->columns;
  if (is_valid_matrix(A) && is_valid_matrix(B))
    status = INCORRECT_MATRIX;
  else if (rows != B->rows || columns != B->columns)
    status = CALCULATION_ERROR;
  if (!status) {
    s21_create_matrix(rows, columns, result);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }

  return status;
}