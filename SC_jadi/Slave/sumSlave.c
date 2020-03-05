#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pvm3.h"

int main(int argc, char const *argv[]) {
  int i;
  unsigned long res, slice, upperBound, lowerBound;
  slice = atoi(argv[1]);
  lowerBound = atoi(argv[2]);
  upperBound = atoi(argv[3]);
  res = 0;
  srand(time(NULL));
  for(i=0; i<slice; i++){
    res += rand() % (upperBound + 1 - lowerBound) + lowerBound;
  }

  //mendapatkan tid dari master
  int ptid = pvm_parent();

  //mengirimkan hasil ke master
  pvm_initsend(PvmDataRaw);
  pvm_pkulong(&res, 1, 1);
  pvm_send(ptid, 1);

  pvm_exit();
  return 0;
}
