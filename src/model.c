#include "model.h"

int read_count_of_vertex_and_faces(const char *filename, unsigned *cv,
                                   unsigned *cf) {
  int status = 0;
  FILE *file = fopen(filename, "r");

  if (!file) {
    status = 1;  // Не смогли открыть файл
  } else {
    char line[500];  // FIXME
    *cv = 0;
    *cf = 0;
    while (fgets(line, sizeof(line), file)) {
      if (!strncmp(line, "v ", 2))
        (*cv)++;
      else if (!strncmp(line, "f ", 2))
        (*cf)++;
    }
    fclose(file);
  }
  if (status != 1 && (!*cv || !*cf)) status = 2;

  return status;  // если нет вершин и нет полигонов то возвращаем ошибку
}

void calloc_model(model *m, unsigned cv, unsigned cf) {
  s21_create_matrix(3, cv, &m->point);
  m->poligon.count = cf;
  m->poligon.poligon_data = calloc(sizeof(poligon_data), m->poligon.count);
}

int read_model(model *m, const char *filename) {
  int status = 0;
  unsigned count_v = 0, count_f = 0;
  FILE *file = fopen(filename, "r");
  char line[500];  // FIXME
  while (fgets(line, sizeof(line), file)) {
    if (!strncmp(line, "v ", 2)) {
      double px = NAN, py = NAN, pz = NAN;
      char *str = line;
      while (*str != ' ' && *str != '\0') str++;
      if (*(str + 1) != '\0')
        sscanf(str + 1, "%lf", &px);
      else
        return 2;  // не верный формат файла
      str++;
      while (*str != ' ' && *str != '\0') str++;
      if (*(str + 1) != '\0')
        sscanf(str + 1, "%lf", &py);
      else
        return 2;  // не верный формат файла
      str++;
      while (*str != ' ' && *str != '\0') str++;
      if (*(str + 1) != '\0')
        sscanf(str + 1, "%lf", &pz);
      else
        return 2;  // не верный формат файла
      // printf("read - %lf %lf %lf\n", px, py, pz);
      add_point(m, count_v, px, py, pz);
      count_v++;
    }

    else if (!strncmp(line, "f ", 2)) {
      int len = 0;
      char *str = line;
      int *arr = calloc(sizeof(int), len);
      while (*str != '\0' && *str != '\n') {
        while (*str != ' ' && *str != '\0' && *str != '\n') str++;
        int x = 0;
        if (*(str + 1) != '\0') sscanf(++str, "%d", &x);
        if (x) {
          len++;
          arr = (int *)realloc(arr, len * sizeof(int));
          if (arr == 0) return 3;  // проблемы с выделением памяти

          arr[len - 1] = (m->point.columns + x) % (m->point.columns + 1);
        }
        str++;
      }
      if (len) {
        m->poligon.poligon_data[count_f].lenght = len;
        m->poligon.poligon_data[count_f].array =
            calloc(sizeof(int), m->poligon.poligon_data[count_f].lenght);
        for (int i = 0; i < len; i++)
          m->poligon.poligon_data[count_f].array[i] = arr[i];

        count_f++;
      }
      free(arr);
    }
  }
  fclose(file);
  return status;
}

void add_point(model *m, unsigned count_v, double px, double py, double pz) {
  m->point.matrix[0][count_v] = px;
  m->point.matrix[1][count_v] = py;
  m->point.matrix[2][count_v] = pz;
}

void free_model(model *m) {
  s21_remove_matrix(&m->point);
  for (unsigned i = 0; i < m->poligon.count; i++) {
    free(m->poligon.poligon_data[i].array);
  }
  free(m->poligon.poligon_data);
  m->poligon.count = 0;
}
