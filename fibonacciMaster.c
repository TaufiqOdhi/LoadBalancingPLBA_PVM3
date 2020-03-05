#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pvm3.h"

int main(int argc, char const *argv[]) {
  int dataSize, i, *tid, cc;
  int nproses = atoi(argv[1]);
  char charDataSize[9];
  char **args = (char**) malloc(2*sizeof(char*));
  tid = (int*) malloc((nproses)*sizeof(int));
  dataSize = 10000;
  args[1] = NULL;
  unsigned long *arrBuff = malloc(dataSize*sizeof(unsigned long));

  //job assignment
  for(i=0; i<nproses; i++){
    sprintf(charDataSize,"%d", dataSize);
    args[0] = charDataSize;
    cc = pvm_spawn("./fibonacciSlave", args, 0, "", 1, &tid[i]);
    if(cc != 1){
      printf("can't start fibonacciSlave\n");
      return 0;
    }
  }

  for(i=0; i<nproses; i++){
    cc = pvm_recv(tid[i], 1);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
    pvm_upkulong(arrBuff, dataSize, 1);
  }

  // for(i=0; i<dataSize; i++){
  //   printf("%lu ", arrBuff[i]);
  // }
  // printf("\n");

  return 0;
}
