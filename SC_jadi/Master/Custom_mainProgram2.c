#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pvm3.h"
#include "initTxt.h"
#include "algoritma2.h"
#include "threshold1Mod.h"
#include "algoritma3_customMod.h"
#include "threshold2.h"
#include "algoritma4.h"
#include "testProgram1Mod.h"
#include "testProgram2Mod.h"
#include "testProgram3Mod.h"

//argument: nhost A, nhost B, nhost C, nhost D, nproses, testType(jenis program yang akan ditest)
int main(int argc, char const *argv[]){
  int nhost[4], i, j, *tasks[4], nproses, ntotal;
  double avgLoad[4], alc[4], std_dvs1[2];
  double alm[2], std_dvs2, threshold1[2], *mips[4],*PELoad[4], threshold2;
  struct timeval end, start;
  char ***hostname = malloc(4*sizeof(hostname));
  nhost[0] = atoi(argv[1]);
  nhost[1] = atoi(argv[2]);
  nhost[2] = atoi(argv[3]);
  nhost[3] = atoi(argv[4]);
  nproses = atoi(argv[5]);
  ntotal = nhost[0]+nhost[1]+nhost[2]+nhost[3];
  char testType = argv[6][0];
  struct Node **PEList;

  hostname[0] = getHostnameTxt("A.txt", nhost[0]);
  hostname[1] = getHostnameTxt("B.txt", nhost[1]);
  hostname[2] = getHostnameTxt("C.txt", nhost[2]);
  hostname[3] = getHostnameTxt("D.txt", nhost[3]);

  //untuk menghitung ALC tiap kelompok
  for(i=0; i<4; i++){
    tasks[i] = getTasks(hostname[i], nhost[i]);
    avgLoad[i] = avg_load(tasks[i], nhost[i]);  //untuk mendapatkan rata - rata Load untuk setiap PE
    mips[i] = getMips(hostname[i], nhost[i]);
    PELoad[i] = getPELoad(tasks[i], mips[i], avgLoad[i], nhost[i]);
    alc[i] = ALC(PELoad[i], nhost[i]);
  }

  //untuk menghitung alm tiap group besar(AB, CD)
  alm[0] = ALM(alc, 2, 2);
  alm[1] = ALM(alc, 2, 4);

  //untuk menghitung standar deviasi pada threshold1
  std_dvs1[0] = standar_deviasi(alc, alm[0], 2, 2);
  std_dvs1[1] = standar_deviasi(alc, alm[1], 2, 4);

  //untuk menghitung threshold1 pada tiap group besar(AB, CD)
  threshold1[0] = getThreshold1(alm[0], std_dvs1[0]);
  threshold1[1] = getThreshold1(alm[1], std_dvs1[1]);

  //PELoad seharusnya ALC akan tetapi karena keterbatasan pada simulasi maka
  //hanya ada 1 cluster saja sehingga nilai PELoad dapat menggantikan ALC
  PEList = getPEList(threshold1, PELoad, alc, nhost, hostname, ntotal);

  //seharunya PELoad adalah paramaeter dari *alc, dan nhost adalah paramaeter
  //dari nmachine, karena keterbatasan jumlah maka dapat digantikan
  threshold2 = getThreshold2(alm, 2);

  //print hasil untuk masing - masing slave
  for(i=0; i<4; i++){
    for(j=0; j<nhost[i]; j++){
      printf("hostname: %s\n", hostname[i][j]);
      printf("total tasks: %d\n", tasks[i][j]);
      printf("rating (MIPS): %.5f\n", mips[i][j]);
      printf("PELoad: %.5f\n\n", PELoad[i][j]);
    }
    printf("\n");
  }

  //printf("Average Load = %.5f\n", avgLoad);
  printf("ALC  A = %.5f\n", alc[0]);
  printf("ALC  B = %.5f\n", alc[1]);
  printf("ALC  C = %.5f\n", alc[2]);
  printf("ALC  D = %.5f\n", alc[3]);
  printf("Standar Deviasi threshold1 AB = %.5f\n", std_dvs1[0]);
  printf("Standar Deviasi threshold1 CD = %.5f\n", std_dvs1[1]);
  printf("nilai threshold1 AB = %.5f\n", threshold1[0]);
  printf("nilai threshold1 CD = %.5f\n", threshold1[1]);
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
        testMergeSortCustom(PEList, ntotal);
      }
      break;
    }
    case 'b':{
      for(i=0; i<nproses; i++){
        sumCustom(PEList, ntotal);
      }
      break;
    }
    case 'c':{
      testFibonacciCustom(PEList, nproses);
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

  for(i=0; i<4; i++){
    if(alc[i] >= threshold2){
      addLog(PEList[0]);//menuliskan log
      break;
    }
  }

  return 0;
}
