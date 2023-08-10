#include "s21_common.h"
#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  s21_create_matrix(A->rows, B->columns, result);
  if (is_valid_matrix(A) || is_valid_matrix(B))
    status = INCORRECT_MATRIX;
  else if (A->columns != B->rows)
    status = CALCULATION_ERROR;
  else {
    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++)
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
  }

  return status;
}