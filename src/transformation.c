#include "model.h"

void shift(model *object, double xShift, double yShift, double zShift) {
  for (int i = 0; i < object->point.columns; i++) {
    object->point.matrix[0][i] += xShift;
    object->point.matrix[1][i] += yShift;
    object->point.matrix[2][i] += zShift;
  }
}

void scaling(model *object, double scale) {
  for (int i = 0; i < object->point.columns; i++) {
    object->point.matrix[0][i] *= scale;
    object->point.matrix[1][i] *= scale;
    object->point.matrix[2][i] *= scale;
  }
}

void rotationX(model *object, double xTurn) {
  //  координаты центра модели
  double xCentr = object->point.matrix[0][object->point.columns - 4];
  double yCentr = object->point.matrix[1][object->point.columns - 4];
  double zCentr = object->point.matrix[2][object->point.columns - 4];
  shift(object, -xCentr, -yCentr, -zCentr);

  //  ненормированный вектор собственной оси вращения oX (xX, yX, zX)
  double xX = object->point.matrix[0][object->point.columns - 3];
  double yX = object->point.matrix[1][object->point.columns - 3];
  double zX = object->point.matrix[2][object->point.columns - 3];

  //  нормирование
  double sq = pow(xX * xX + yX * yX + zX * zX, 0.5);
  xX /= sq;
  yX /= sq;
  zX /= sq;

  matrix_t rotationMatrix;
  s21_create_matrix(3, 3, &rotationMatrix);

  rotationMatrix.matrix[0][0] = cos(xTurn) + (1 - cos(xTurn)) * xX * xX;
  rotationMatrix.matrix[0][1] = (1 - cos(xTurn)) * xX * yX - sin(xTurn) * zX;
  rotationMatrix.matrix[0][2] = (1 - cos(xTurn)) * xX * zX + sin(xTurn) * yX;

  rotationMatrix.matrix[1][0] = (1 - cos(xTurn)) * xX * yX + sin(xTurn) * zX;
  rotationMatrix.matrix[1][1] = cos(xTurn) + (1 - cos(xTurn)) * yX * yX;
  rotationMatrix.matrix[1][2] = (1 - cos(xTurn)) * zX * yX - sin(xTurn) * xX;

  rotationMatrix.matrix[2][0] = (1 - cos(xTurn)) * xX * zX - sin(xTurn) * yX;
  rotationMatrix.matrix[2][1] = (1 - cos(xTurn)) * zX * yX + sin(xTurn) * xX;
  rotationMatrix.matrix[2][2] = cos(xTurn) + (1 - cos(xTurn)) * zX * zX;

  matrix_t turnedMatrix;
  s21_mult_matrix(&rotationMatrix, &(object->point), &turnedMatrix);
  for (int i = 0; i < object->point.columns; i++) {
    for (int j = 0; j < 3; j++) {
      object->point.matrix[j][i] = turnedMatrix.matrix[j][i];
    }
  }
  s21_remove_matrix(&rotationMatrix);
  s21_remove_matrix(&turnedMatrix);

  shift(object, xCentr, yCentr, zCentr);
}

void rotationY(model *object, double yTurn) {
  double xCentr = object->point.matrix[0][object->point.columns - 4];
  double yCentr = object->point.matrix[1][object->point.columns - 4];
  double zCentr = object->point.matrix[2][object->point.columns - 4];
  shift(object, -xCentr, -yCentr, -zCentr);

  //  ненормированный вектор собственной оси вращения oY (xY, yY, zY)
  double xY = object->point.matrix[0][object->point.columns - 2];
  double yY = object->point.matrix[1][object->point.columns - 2];
  double zY = object->point.matrix[2][object->point.columns - 2];

  //  нормирование
  double sq = pow(xY * xY + yY * yY + zY * zY, 0.5);
  xY /= sq;
  yY /= sq;
  zY /= sq;

  matrix_t rotationMatrix;
  s21_create_matrix(3, 3, &rotationMatrix);

  rotationMatrix.matrix[0][0] = cos(yTurn) + (1 - cos(yTurn)) * xY * xY;
  rotationMatrix.matrix[0][1] = (1 - cos(yTurn)) * xY * yY - sin(yTurn) * zY;
  rotationMatrix.matrix[0][2] = (1 - cos(yTurn)) * xY * zY + sin(yTurn) * yY;

  rotationMatrix.matrix[1][0] = (1 - cos(yTurn)) * xY * yY + sin(yTurn) * zY;
  rotationMatrix.matrix[1][1] = cos(yTurn) + (1 - cos(yTurn)) * yY * yY;
  rotationMatrix.matrix[1][2] = (1 - cos(yTurn)) * zY * yY - sin(yTurn) * xY;

  rotationMatrix.matrix[2][0] = (1 - cos(yTurn)) * xY * zY - sin(yTurn) * yY;
  rotationMatrix.matrix[2][1] = (1 - cos(yTurn)) * zY * yY + sin(yTurn) * xY;
  rotationMatrix.matrix[2][2] = cos(yTurn) + (1 - cos(yTurn)) * zY * zY;

  matrix_t turnedMatrix;
  s21_mult_matrix(&rotationMatrix, &(object->point), &turnedMatrix);
  for (int i = 0; i < object->point.columns; i++) {
    for (int j = 0; j < 3; j++) {
      object->point.matrix[j][i] = turnedMatrix.matrix[j][i];
    }
  }
  s21_remove_matrix(&rotationMatrix);
  s21_remove_matrix(&turnedMatrix);

  shift(object, xCentr, yCentr, zCentr);
}

void rotationZ(model *object, double zTurn) {
  double xCentr = object->point.matrix[0][object->point.columns - 4];
  double yCentr = object->point.matrix[1][object->point.columns - 4];
  double zCentr = object->point.matrix[2][object->point.columns - 4];
  shift(object, -xCentr, -yCentr, -zCentr);

  //  ненормированный вектор собственной оси вращения oX (xX, yX, zX)
  double xZ = object->point.matrix[0][object->point.columns - 1];
  double yZ = object->point.matrix[1][object->point.columns - 1];
  double zZ = object->point.matrix[2][object->point.columns - 1];

  //  нормирование
  double sq = pow(xZ * xZ + yZ * yZ + zZ * zZ, 0.5);
  xZ /= sq;
  yZ /= sq;
  zZ /= sq;

  matrix_t rotationMatrix;
  s21_create_matrix(3, 3, &rotationMatrix);

  rotationMatrix.matrix[0][0] = cos(zTurn) + (1 - cos(zTurn)) * xZ * xZ;
  rotationMatrix.matrix[0][1] = (1 - cos(zTurn)) * xZ * yZ - sin(zTurn) * zZ;
  rotationMatrix.matrix[0][2] = (1 - cos(zTurn)) * xZ * zZ + sin(zTurn) * yZ;

  rotationMatrix.matrix[1][0] = (1 - cos(zTurn)) * xZ * yZ + sin(zTurn) * zZ;
  rotationMatrix.matrix[1][1] = cos(zTurn) + (1 - cos(zTurn)) * yZ * yZ;
  rotationMatrix.matrix[1][2] = (1 - cos(zTurn)) * zZ * yZ - sin(zTurn) * xZ;

  rotationMatrix.matrix[2][0] = (1 - cos(zTurn)) * xZ * zZ - sin(zTurn) * yZ;
  rotationMatrix.matrix[2][1] = (1 - cos(zTurn)) * zZ * yZ + sin(zTurn) * xZ;
  rotationMatrix.matrix[2][2] = cos(zTurn) + (1 - cos(zTurn)) * zZ * zZ;

  matrix_t turnedMatrix;
  s21_mult_matrix(&rotationMatrix, &(object->point), &turnedMatrix);
  for (int i = 0; i < object->point.columns; i++) {
    for (int j = 0; j < 3; j++) {
      object->point.matrix[j][i] = turnedMatrix.matrix[j][i];
    }
  }
  s21_remove_matrix(&rotationMatrix);
  s21_remove_matrix(&turnedMatrix);

  shift(object, xCentr, yCentr, zCentr);
}

void rotationXForMouse(model *object, double xTurn) {
  double xCentr = object->point.matrix[0][object->point.columns - 4];
  double yCentr = object->point.matrix[1][object->point.columns - 4];
  double zCentr = object->point.matrix[2][object->point.columns - 4];
  shift(object, -xCentr, -yCentr, -zCentr);

  matrix_t rotationMatrix;
  s21_create_matrix(3, 3, &rotationMatrix);
  rotationMatrix.matrix[0][0] = 1;
  rotationMatrix.matrix[1][1] = cos(xTurn);
  rotationMatrix.matrix[2][2] = cos(xTurn);
  rotationMatrix.matrix[2][1] = sin(xTurn);
  rotationMatrix.matrix[1][2] = -sin(xTurn);

  matrix_t turnedMatrix;
  s21_mult_matrix(&rotationMatrix, &(object->point), &turnedMatrix);
  for (int i = 0; i < object->point.columns; i++) {
    for (int j = 0; j < 3; j++) {
      object->point.matrix[j][i] = turnedMatrix.matrix[j][i];
    }
  }
  s21_remove_matrix(&rotationMatrix);
  s21_remove_matrix(&turnedMatrix);

  shift(object, xCentr, yCentr, zCentr);
}

void rotationYForMouse(model *object, double yTurn) {
  double xCentr = object->point.matrix[0][object->point.columns - 4];
  double yCentr = object->point.matrix[1][object->point.columns - 4];
  double zCentr = object->point.matrix[2][object->point.columns - 4];
  shift(object, -xCentr, -yCentr, -zCentr);

  matrix_t rotationMatrix;
  s21_create_matrix(3, 3, &rotationMatrix);
  rotationMatrix.matrix[0][0] = cos(yTurn);
  rotationMatrix.matrix[0][2] = sin(yTurn);
  rotationMatrix.matrix[1][1] = 1;
  rotationMatrix.matrix[2][0] = -sin(yTurn);
  rotationMatrix.matrix[2][2] = cos(yTurn);

  matrix_t turnedMatrix;
  s21_mult_matrix(&rotationMatrix, &(object->point), &turnedMatrix);
  for (int i = 0; i < object->point.columns; i++) {
    for (int j = 0; j < 3; j++) {
      object->point.matrix[j][i] = turnedMatrix.matrix[j][i];
    }
  }
  s21_remove_matrix(&rotationMatrix);
  s21_remove_matrix(&turnedMatrix);

  shift(object, xCentr, yCentr, zCentr);
}
