#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  int dataSize, i, j;
  dataSize = atoi(argv[1]);
  int *arr = malloc(dataSize*sizeof(int));
  srand(time(NULL));
  for(i=0; i<dataSize; i++){
    arr[i] = i+rand()%dataSize;
  }

  for(i=0; i<dataSize; i++){
    for(j=0; j<dataSize; j++){
      if(arr[i] > arr[j]){
        int swap = arr[i];
        arr[i] = arr[j];
        arr[j] = swap;
      }
    }
  }

  //split array menjadi 2
  // int *split = arr+(dataSize/2);
  // int *split2 = split-(dataSize/2)+(dataSize/4);
  //
  // for(i=0; i<dataSize; i++){
  //   printf("%d ", arr[i]);
  // }
  // printf("\n");
  //
  // for(i=0; i<dataSize/2; i++){
  //   printf("%d ", split[i]);
  // }
  // printf("\n");
  //
  // for(i=0; i<dataSize/2; i++){
  //   printf("%d ", split2[i]);
  // }
  // printf("\n");

  return 0;
}
