#include "s21_common.h"
#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  result->columns = 0;
  result->rows = 0;
  int status = OK;
  if (is_valid_matrix(A))
    status = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    status = CALCULATION_ERROR;
  else {
    double det;
    s21_determinant(A, &det);
    if (near_null(det))
      status = CALCULATION_ERROR;
    else {
      matrix_t complements;
      matrix_t transpose_complements;
      s21_calc_complements(A, &complements);
      s21_transpose(&complements, &transpose_complements);
      s21_mult_number(&transpose_complements, 1.0 / det, result);
      s21_remove_matrix(&transpose_complements);
      s21_remove_matrix(&complements);
    }
  }
  return status;
}