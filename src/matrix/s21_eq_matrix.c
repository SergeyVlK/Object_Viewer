#include "s21_common.h"
#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if (A->rows <= 0 || A->rows != B->rows || A->columns <= 0 ||
      A->columns != B->columns)
    status = FAILURE;
  if (status) {
    int rows = A->rows;
    int columns = A->columns;
    for (int i = 0; i < rows && status; i++)
      for (int j = 0; j < columns && status; j++)
        if (!near_null(A->matrix[i][j] - B->matrix[i][j])) status = FAILURE;
  }
  return status;
}