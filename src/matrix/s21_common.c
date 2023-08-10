#include "s21_common.h"

#include "s21_matrix.h"
int is_valid_matrix(matrix_t *M) { return !(M->rows > 0 && M->columns > 0); }

int near_null(double x) { return x > -EPS && x < EPS ? 1 : 0; }

void get_matrix_without_row_and_column(matrix_t *M, int size, int row, int col,
                                       matrix_t *R) {
  int offsetRow = 0;
  int offsetCol = 0;
  for (int i = 0; i < size - 1; i++) {
    if (i == row) {
      offsetRow = 1;
    }
    offsetCol = 0;
    for (int j = 0; j < size - 1; j++) {
      if (j == col) {
        offsetCol = 1;
      }
      R->matrix[i][j] = M->matrix[i + offsetRow][j + offsetCol];
    }
  }
}