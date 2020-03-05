#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pvm3.h"

int main(int argc, char const *argv[]) {
  struct timeval end, start;
  int dataSize, i, sisa, slice, *tid, cc, bound;
  int nhost = atoi(argv[1]);
  unsigned long res, buff;
  char charSlice[6], charLowerBound[7], charUpperBound[7];
  char **args = (char**) malloc(4*sizeof(char*));
  tid = (int*) malloc((nhost+1)*sizeof(int));
  dataSize = 1000000;// jumnlah yang seharusnya
  slice = dataSize/nhost;
  sisa = dataSize%nhost;
  args[3] = NULL;
  bound = 0;
  res = 0;

  gettimeofday(&start, NULL);
  for(i=0; i<nhost; i++){
    sprintf(charSlice,"%d",slice);
    args[0] = charSlice;
    sprintf(charLowerBound, "%d", bound);
    args[1] = charLowerBound;
    sprintf(charUpperBound, "%d", (bound+slice));
    args[2] = charUpperBound;
    bound += slice;
    printf("%s %s\n", charLowerBound, charUpperBound);
    cc = pvm_spawn("./sumSlave", args, 0, "", 1, &tid[i]);
    if(cc != 1){
      printf("can't start sumSlave\n");
      return 0;
    }
  }

  if(sisa != 0){
    sprintf(charSlice,"%d", sisa);
    args[0] = charSlice;
    sprintf(charLowerBound, "%d", (dataSize-sisa));
    args[1] =  charLowerBound;
    sprintf(charUpperBound, "%d", dataSize);
    args[2] =  charUpperBound;
    printf("%s %s\n", charLowerBound, charUpperBound);
    cc = pvm_spawn("./sumSlave", args, 0, "", 1, &tid[nhost]);
    if(cc != 1){
      printf("can't start sumSlave\n");
      return 0;
    } else{
      cc = pvm_recv(tid[nhost], 1);
      pvm_bufinfo(cc, (int*)0, (int*)0, &tid[nhost]);
      pvm_upkulong(&buff, 1, 1);
      res += buff;
    }
  }

  for(i=0; i<nhost; i++){
    cc = pvm_recv(tid[i], 1);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
    pvm_upkulong(&buff, 1, 1);
    res += buff;
    //printf("Nilai Buff ke-%d = %lu\n", i, buff);
  }
  gettimeofday(&end, NULL);
  double time_spent;
  time_spent = (end.tv_sec - start.tv_sec) * 1e6;
  time_spent = (time_spent + (end.tv_usec - start.tv_usec)) * 1e-6;
  time_spent *= 1000;

  printf("\nTotal running time : %.5f ms\n", time_spent);
  printf("Hasil penjumlahan : %lu\n", res);
  return 0;
}
