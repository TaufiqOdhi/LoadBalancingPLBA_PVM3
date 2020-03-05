#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pvm3.h"
#include "init.h"
#include "algoritma2.h"
#include "threshold1.h"
#include "algoritma3.h"
#include "algoritma4.h"

int main(){//bagian ini juga perlu disesuaikan (harus hanya gat task saja) atau filename ganti
  int nhost, i;
  double avgLoad, alc, std_dvs, threshold1,*PELoad;
  nhost = 5; //jumlah host yang terhubung
  struct Node **PEList;

  char **hostname = gethostname(nhost);
  //tasks = getTasks(hostname, nhost);

  //char *hostname[] = {"ubuntu1", "ubuntu2", "ubuntu3", "ubuntu4", "ubuntu5"};
  int tasks[] = {100, 500, 1000, 750, 50};
  //double mips[] = {324.77233, 287.19754, 280.71397, 329.58877, 330.62573};

  avgLoad = avg_load(tasks, nhost);  //untuk mendapatkan rata - rata Load untuk setiap PE
  double *mips = getMips(hostname, nhost);
  PELoad = getPELoad(tasks, mips, avgLoad, nhost);
  alc = ALC(PELoad, nhost);   //untuk mendapatkan nilai threshold
  std_dvs = standar_deviasi(PELoad, alc, nhost);
  threshold1 = getThreshold1(alc, std_dvs);
  PEList = getPEList(threshold1, PELoad,PELoad, nhost, hostname);

  //print hasil untuk masing - masing slave
  for(i=0; i<nhost; i++){
    printf("hostname: %s\n", hostname[i]);
    printf("total tasks: %d\n", tasks[i]);
    printf("rating (MIPS): %.5f\n", mips[i]);
    printf("PELoad: %.5f\n\n", PELoad[i]);
  }
  printf("Average Load = %.5f\n", avgLoad);
  printf("ALC = %.5f\n", alc);
  printf("Standar Deviasi = %.5f\n", std_dvs);
  printf("nilai threshold = %.5f\n", threshold1);
  printf("\nOPEList\n");
  printPEList(PEList[0]);
  printf("\nNPEList\n");
  printPEList(PEList[1]);
  printf("\nLPEList\n");
  printPEList(PEList[2]);
  printf("\nULPEList\n");
  printPEList(PEList[3]);

  runProses(PEList, threshold1);
  //pvm_exit();
  return 0;
}
