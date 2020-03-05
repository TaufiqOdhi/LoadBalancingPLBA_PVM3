#include <stdio.h>
#include <stdlib.h>
#include "pvm3.h"

int main (int argc, char const *argv[]){
  int dataSize = atoi(argv[1]);
  int i;
  unsigned long a = 0;
  unsigned long b = 1;
  unsigned long *arr = malloc(dataSize*sizeof(unsigned long));

  for (i = 0; i <= dataSize; i++){
     arr[i] = a + b;
     a = b;
     b = arr[i];
  }

  //mendapatkan tid dari master
  int ptid = pvm_parent();

  //mengirimkan hasil ke master
  pvm_initsend(PvmDataRaw);
  pvm_pkulong(arr, dataSize, 1);
  pvm_send(ptid, 1);

  pvm_exit();
  return 0;
}
