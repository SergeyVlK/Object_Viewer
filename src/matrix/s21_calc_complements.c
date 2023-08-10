#include "s21_common.h"
#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  result->columns = 0;
  result->rows = 0;
  int status = OK;
  int rows = A->rows;
  int columns = A->columns;
  if (is_valid_matrix(A))
    status = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    status = CALCULATION_ERROR;
  else {
    if (rows > 1) {
      s21_create_matrix(rows, columns, result);
      double sign = 0.0;
      for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
          matrix_t minor;
          s21_create_matrix(rows - 1, columns - 1, &minor);
          get_matrix_without_row_and_column(A, rows, i, j, &minor);
          double det = 0.0;
          s21_determinant(&minor, &det);
          sign = (i + j) % 2 == 0 ? 1.0 : -1.0;
          result->matrix[i][j] = det * sign;
          s21_remove_matrix(&minor);
        }
    } else {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1;
    }
  }
  return status;
}