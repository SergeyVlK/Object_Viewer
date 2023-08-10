#include "s21_common.h"
#include "s21_matrix.h"

double determinant_recursive(matrix_t *M) {
  double result = 0.0;
  if (M->rows == 1)
    result = M->matrix[0][0];
  else if (M->rows == 2)
    result =
        M->matrix[0][0] * M->matrix[1][1] - M->matrix[0][1] * M->matrix[1][0];
  else {
    matrix_t lower_order_matrix;
    double sign = 1.0;
    for (int i = 0; i < M->rows; i++) {
      s21_create_matrix(M->rows - 1, M->rows - 1, &lower_order_matrix);
      get_matrix_without_row_and_column(M, M->rows, 0, i, &lower_order_matrix);
      result +=
          sign * M->matrix[0][i] * determinant_recursive(&lower_order_matrix);
      sign *= -1.0;
      s21_remove_matrix(&lower_order_matrix);
    }
  }
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;
  *result = 0.0;
  if (is_valid_matrix(A))
    status = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    status = CALCULATION_ERROR;
  else {
    *result = determinant_recursive(A);
  }
  return status;
}