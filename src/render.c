#include "model.h"
#define SIZE 0.55

void MinMax(model *object, double *edges) {
  double minX = object->point.matrix[0][0];
  double minY = object->point.matrix[1][0];
  double minZ = object->point.matrix[2][0];
  double maxX = minX;
  double maxY = minY;
  double maxZ = minZ;

  for (int i = 0; i < object->point.columns - 4; i++) {
    minX =
        (minX < object->point.matrix[0][i] ? minX : object->point.matrix[0][i]);
    minY =
        (minY < object->point.matrix[1][i] ? minY : object->point.matrix[1][i]);
    minZ =
        (minZ < object->point.matrix[2][i] ? minZ : object->point.matrix[2][i]);

    maxX =
        (maxX > object->point.matrix[0][i] ? maxX : object->point.matrix[0][i]);
    maxY =
        (maxY > object->point.matrix[1][i] ? maxY : object->point.matrix[1][i]);
    maxZ =
        (maxZ > object->point.matrix[2][i] ? maxZ : object->point.matrix[2][i]);
  }

  edges[0] = minX;
  edges[1] = maxX;
  edges[2] = minY;
  edges[3] = maxY;
  edges[4] = minZ;
  edges[5] = maxZ;
}

void calibration(model *object) {
  double edges[6] = {0};
  MinMax(object, edges);
  double maxSizeX = edges[1] - edges[0];
  double maxSizeY = edges[3] - edges[2];
  double maxSizeZ = edges[5] - edges[4];

  double maxSize = (maxSizeX > maxSizeY ? maxSizeX : maxSizeY);
  maxSize = (maxSize > maxSizeZ ? maxSize : maxSizeZ);

  double shiftX = -(edges[0] + edges[1]) / 2.0;
  double shiftY = -(edges[2] + edges[3]) / 2.0;
  double shiftZ = -(edges[4] + edges[5]) / 2.0;
  double scale = 1;
  if (maxSize) scale = 2 * SIZE / maxSize;

  shift(object, shiftX, shiftY, shiftZ);
  if (scale != 1) scaling(object, scale);
  add_point(object, object->point.columns - 4, 0, 0, 0);  //  центр фигуры
  add_point(object, object->point.columns - 3, 1.0, 0, 0);  //  ось oX фигуры
  add_point(object, object->point.columns - 2, 0, 1.0, 0);  //  ось oY фигуры
  add_point(object, object->point.columns - 1, 0, 0, 1.0);  //  ось oZ фигуры
}
