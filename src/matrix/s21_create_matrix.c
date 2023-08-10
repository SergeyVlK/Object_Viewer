#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if (rows <= 0 || columns <= 0) {
    status = INCORRECT_MATRIX;
    result->rows = 0;
    result->columns = 0;
  }
  if (!status) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(result->rows, sizeof(double *));
    for (int i = 0; i < result->rows; i++)
      result->matrix[i] = calloc(result->columns, sizeof(double));
  }
  return status;
}