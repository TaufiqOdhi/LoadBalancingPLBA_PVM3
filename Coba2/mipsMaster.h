#include <stdio.h>
#include "pvm3.h"

int mips_master(double *mips, char *hostname){
  int cc, tid, nhost, i;

  //jumlah host yang terhubung
  //nhost = 5;

  //double mips[nhost];
  //char hostname[nhost][25];

  //for(i=0; i<nhost; i++){
    cc = pvm_spawn("./mipsSlave", (char**) 0, 1, hostname, 1, &tid);
    if(cc == 1){
      cc = pvm_recv(tid, 1);
      pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
  		pvm_upkdouble(mips, 1, 1);

      // cc = pvm_recv(tid, 2);
      // pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
  		// pvm_upkstr(hostname[i]);
    }
    else printf("can't start mipsSlave\n");
//  }

  // for(i=0; i<nhost; i++){
  //   printf("%s\n", hostname[i]);
  //   printf("%.2f\n", mips[i]);
  // }

  pvm_exit();
  return 0;
}
