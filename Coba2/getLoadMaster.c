#include <stdio.h>
#include "pvm3.h"

int main(){
  int cc, tid, nhost, i;

  //jumlah host yang terhubung
  nhost = 5;

  float load[nhost][3];
  char hostname[nhost][25];

  //mengirimkan perintah ke slave untuk mendapatkan current load masing - masing
  for(i=0; i<nhost; i++){
    cc = pvm_spawn("./updateLoadSlave", (char**) 0, 0, "", 1, &tid);
    if (cc == 1) {
  		cc = pvm_recv(tid, 1);
      pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
  		pvm_upkfloat(load[i], 3, 1);

      cc = pvm_recv(tid, 2);
      pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
  		pvm_upkstr(hostname[i]);
    }
    else printf("can't start updateLoadSlave\n");
  }

  //print hasil current load yang didapatkan
  for(i=0; i<nhost; i++){
    printf("%s\n", hostname[i]);
    printf("%.2f\n", load[i][0]);
    printf("%.2f\n", load[i][1]);
    printf("%.2f\n", load[i][2]);
  }

  pvm_exit();
  return 0;
}
