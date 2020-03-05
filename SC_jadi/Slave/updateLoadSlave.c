#include <stdio.h>
#include <stdlib.h>
#include "pvm3.h"

int main (int c, char** a){
  FILE *filePointer;
  char hostname[25];
  char string[4];
  char loadFile[] = "/proc/loadavg";
  double load[3];

  //mendapatkan rata - rata load dengan mengakses file tersebut
  if((filePointer = fopen(loadFile, "r")) == NULL)
    puts("File tidak ditemukan.");
  else{
    fscanf(filePointer, "%s", string);
    load[0] = atof(string); //untuk rata-rata interval 1 menit
    fscanf(filePointer, "%s", string);
    load[1] = atof(string); //untuk rata-rata interval 5 menit
    fscanf(filePointer, "%s", string);
    load[2] = atof(string); // untuk rata-rata interval 15 menit
    fclose(filePointer);
  }

  //mendapatkan tid dari master
  int ptid = pvm_parent();

  //mengirimkan load ke master
  pvm_initsend(PvmDataDefault);
  pvm_pkdouble(load, 3,1);
  pvm_send(ptid, 1);

  pvm_exit();
  return 0;
}
