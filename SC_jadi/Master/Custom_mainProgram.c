#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pvm3.h"
#include "init.h"
#include "algoritma2.h"
#include "threshold1.h"
#include "algoritma3_custom.h"
#include "threshold2.h"
#include "algoritma4.h"
#include "testProgram1.h"
#include "testProgram2.h"
#include "testProgram3.h"
 
int main(int argc, char const *argv[]){
  int nhost, i, *tasks, nproses;
  double avgLoad, alc, std_dvs, threshold1, *mips,*PELoad, threshold2;
  struct timeval end, start;
  char **hostname; //untuk menyimpan nama2 host yang terhubung
  nhost = atoi(argv[1]); //jumlah host yang terhubung
  nproses = atoi(argv[2]);
  char testType = argv[3][0];
  struct Node **PEList;
 
  hostname = gethostname(nhost);
  tasks = getTasks(hostname, nhost);
  avgLoad = avg_load(tasks, nhost);  //untuk mendapatkan rata - rata Load untuk setiap PE
  mips = getMips(hostname, nhost);
  PELoad = getPELoad(tasks, mips, avgLoad, nhost);
 
  //untuk mendapatkan nilai threshold, seharusnya ini ALM, karena keterbatasan
  //pada simulasi maka nilai ALC dapat menggantikan nilai ALM
  alc = ALC(PELoad, nhost);
 
  //seharunya PELoad adalah parameter untuk ALC, dan ALC adalah parameter untuk
  //ALM, karena keterbatasan pada simulasi maka dapat digantikan
  std_dvs = standar_deviasi(PELoad, alc, nhost);
  threshold1 = getThreshold1(alc, std_dvs);
 
  //PELoad seharusnya ALC akan tetapi karena keterbatasan pada simulasi maka
  //hanya ada 1 cluster saja sehingga nilai PELoad dapat menggantikan ALC
  PEList = getPEList(threshold1, PELoad, PELoad, nhost, hostname);
 
  //seharunya PELoad adalah paramaeter dari *alc, dan nhost adalah paramaeter
  //dari nmachine, karena keterbatasan jumlah maka dapat digantikan
  threshold2 = getThreshold2(PELoad, nhost);
 
  //print hasil untuk masing - masing slave
  for(i=0; i<nhost; i++){
    printf("hostname: %s\n", hostname[i]);
    printf("total tasks: %d\n", tasks[i]);
    printf("rating (MIPS): %.5f\n", mips[i]);
    printf("PELoad: %.5f\n\n", PELoad[i]);
  }
  //printf("Average Load = %.5f\n", avgLoad);
  printf("ALC = %.5f\n", alc);
  //printf("Standar Deviasi = %.5f\n", std_dvs);
  printf("nilai threshold = %.5f\n", threshold1);
  printf("nilai threshold2 = %.5f\n", threshold2);
  printf("\nOPEList\n");
  printPEList(PEList[0]);
  printf("\nNPEList\n");
  printPEList(PEList[1]);
  printf("\nLPEList\n");
  printPEList(PEList[2]);
  printf("\nULPEList\n");
  printPEList(PEList[3]);
  //printf("\nAllPEList\n");
  //printPEList(PEList[4]);
 
  gettimeofday(&start, NULL);
  switch (testType) {
    case 'a':{
      for(i=0; i<nproses; i++){
        testMergeSortCustom(PEList, threshold1, nhost);
      }
      break;
    }
    case 'b':{
      for(i=0; i<nproses; i++){
        sumCustom(PEList, threshold1, nhost);
      }
      break;
    }
    case 'c':{
      testFibonacciCustom(PEList, threshold1, nproses);
      break;
    }
    default:{
      printf("Opsi hanya a,b,c\n");
    }
  }
  gettimeofday(&end, NULL);
  double time_spent;
  time_spent = (end.tv_sec - start.tv_sec) * 1e6;
  time_spent = (time_spent + (end.tv_usec - start.tv_usec)) * 1e-6;
  time_spent *= 1000;
  printf("\nTotal running time : %.5f ms\n", time_spent);
 
  if(alc >= threshold2){
    addLog(PEList[0]);//menuliskan log
  }
 
  return 0;
}
