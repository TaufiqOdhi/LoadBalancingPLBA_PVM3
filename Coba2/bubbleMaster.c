#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "pvm3.h"

int main(int argc, char const *argv[]) {
  int dataSize, i, j, sisa, **arr, nhost, slice;
  char **hostname = {"ubuntu1", "ubuntu2", "ubuntu3", "debian", "debian2"};
  nhost = 5;
  int tid[nhost];
  dataSize = atoi(argv[1]);
  slice = dataSize/nhost;
  sisa = dataSize%nhost;//sisa array setelah dibagi dengan jumlah host
  char charSlice[9];
  sprintf(charSlice,"%d",slice);
  char **arg = (char**) malloc(sizeof(charSlice));
  arg[0] = charSlice;
  printf("%s\n", arg[0]);

  srand(time(NULL));
  if(sisa == 0){
    arr = (int**) malloc(nhost*sizeof(int*));
  }else{
    arr = (int**) malloc((nhost+1)*sizeof(int*));
    arr[nhost+1] = (int*) malloc(sisa*sizeof(int));
    for(i=0; i<sisa; i++){
      arr[nhost+1][i] = i+rand()%dataSize;
    }
    for(i=0; i<sisa; i++){
      printf("%d ", arr[nhost+1][i]);
    }
    printf("\n");
  }
  for(i=0; i<nhost; i++){
    cc = pvm_spawn("./bubbleSlave", (char**) 0, 1, hostname[i], 1, &tid[i]);
    if(cc != 1){
      printf("can't start bubbleSlave\n");
      return 0;
    }
  }

  for(i=0; i<nhost; i++){
    arr[i] = (int*) malloc(slice*sizeof(int));
    for(j=0; j<slice; j++){
      arr[i][j] = i+rand()%dataSize;
    }

  }

  for(i=0; i<nhost; i++){
    for(j=0; j<slice; j++){
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }

  return 0;
}
