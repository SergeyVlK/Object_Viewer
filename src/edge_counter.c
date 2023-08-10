#include "model.h"

unsigned long get_count_of_edges(model *m) {
  unsigned long result = 0;
  for (unsigned i = 0; i < m->poligon.count; i++)
    result += m->poligon.poligon_data[i].lenght;
  return result;
}
