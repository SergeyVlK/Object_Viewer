#include "settings.h"

int loadOptions(const char* filename, widgetOptions* wo) {
  int status = 0;
  FILE* file = fopen(filename, "r");
  char line[64];
  if (!file) status = 1;
  if (!status && fgets(line, sizeof(line), file))
    sscanf(line, "%d", &wo->pointType);
  else
    status = 1;
  if (!status && fgets(line, sizeof(line), file))
    sscanf(line, "%d", &wo->pointSize);
  else
    status = 1;
  if (!status && fgets(line, sizeof(line), file))
    sscanf(line, "%d", &wo->edgeType);
  else
    status = 1;
  if (!status && fgets(line, sizeof(line), file))
    sscanf(line, "%d", &wo->edgeSize);
  else
    status = 1;
  if (!status && fgets(line, sizeof(line), file))
    sscanf(line, "%d", &wo->projectionType);
  else
    status = 1;
  for (int i = 0; i < 3 && !status; i++)
    if (!status && fgets(line, sizeof(line), file))
      sscanf(line, "%f", &wo->pointColor[i]);
    else
      status = 1;
  for (int i = 0; i < 3 && !status; i++)
    if (!status && fgets(line, sizeof(line), file))
      sscanf(line, "%f", &wo->edgeColor[i]);
    else
      status = 1;
  for (int i = 0; i < 3 && !status; i++)
    if (!status && fgets(line, sizeof(line), file))
      sscanf(line, "%f", &wo->backColor[i]);
    else
      status = 1;
  if (file) fclose(file);
  return status;
}

int saveOptions(const char* filename, widgetOptions wo) {
  FILE* file = fopen(filename, "w");
  char line[64];
  sprintf(line, "%d\n%d\n%d\n%d\n%d\n", wo.pointType, wo.pointSize, wo.edgeType,
          wo.edgeSize, wo.projectionType);
  fputs(line, file);
  sprintf(line, "%f\n%f\n%f\n", wo.pointColor[0], wo.pointColor[1],
          wo.pointColor[2]);
  fputs(line, file);
  sprintf(line, "%f\n%f\n%f\n", wo.edgeColor[0], wo.edgeColor[1],
          wo.edgeColor[2]);
  fputs(line, file);
  sprintf(line, "%f\n%f\n%f\n", wo.backColor[0], wo.backColor[1],
          wo.backColor[2]);
  fputs(line, file);
  fclose(file);
  return 0;
}
