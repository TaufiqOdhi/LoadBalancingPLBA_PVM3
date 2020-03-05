#include <stdio.h>
#include <stdlib.h>
#include "pvm3.h"

int main(int argc, char const *argv[]) {
  int cc, nhost, i;
  nhost = atoi(argv[1]);//jumlah host yang terhubung
  int tid[nhost];
  double mips;

  for(i=0; i<nhost; i++){
    cc = pvm_spawn("./updateMipsSlave", (char**) 0, 0, "", 1, &tid[i]);
    if(cc != 1){
      printf("can't start mipsSlave\n");
    }
  }

  for(i=0; i<nhost; i++){
    cc = pvm_recv(tid[i], 1);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid[i]);
    pvm_upkdouble(&mips, 1, 1);
  }

  printf("Done\n");
  pvm_exit();
  return 0;
}
