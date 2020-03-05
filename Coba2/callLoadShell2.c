#include <stdio.h>
#include <stdlib.h>

int main (int c, char** a){
  FILE *filePointer;
  char string[4];
  char loadFile[] = "/proc/loadavg";
  float load[3];

  if((filePointer = fopen(loadFile, "r")) == NULL)
    puts("File tidak ditemukan.");
  else{
    fscanf(filePointer, "%s", string);
    load[0] = atof(string);
    fscanf(filePointer, "%s", string);
    load[1] = atof(string);
    fscanf(filePointer, "%s", string);
    load[2] = atof(string);
    fclose(filePointer);
  }

  printf("load interval 1 menit : %.2f\n", load[0]);
  printf("load interval 5 menit : %.2f\n", load[1]);
  printf("load interval 15 menit : %.2f\n", load[2]);
  return 0;
}
