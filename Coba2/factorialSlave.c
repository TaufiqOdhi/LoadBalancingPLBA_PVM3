#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "pvm3.h"

int main(int argc, char const *argv[]) {
  int i, upperBound, lowerBound;
  long res = 1;
  lowerBound = atoi(argv[1]);
  upperBound = atoi(argv[2]);
  srand(time(NULL));
  for(i=lowerBound; i<upperBound; i++){
    res *= 2;
  }

  printf("%ld\n", res);

  // //mendapatkan tid dari master
  // int ptid = pvm_parent();
  //
  // //mengirimkan hasil ke master
  // pvm_initsend(PvmDataDefault);
  // pvm_pkint(&res, 1, 1);
  // pvm_send(ptid, 1);
  //
  // pvm_exit();
  return 0;
}
