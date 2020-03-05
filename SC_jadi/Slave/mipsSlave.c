#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"pvm3.h"
#define SIZE 1000000

int main(){
  FILE *filePointer;
  int a,i,j,n;
  double mips;
  char mipsFile[] = "mips.txt";
  n = 1000;

  if ((filePointer = fopen(mipsFile, "r")) == NULL) {
    if((filePointer = fopen(mipsFile, "w")) == NULL)
      puts("File tidak bisa dibuat");
    else{
      clock_t begin = clock();
      for(i=1; i<=n; i++){
        for(j=1; j<=SIZE; j++){
          a++;
        }
      }
      clock_t end = clock();

      mips = ((double)(end - begin)/(double) CLOCKS_PER_SEC)/n;
      mips = 1/mips;
      fprintf(filePointer, "%.5f", mips);
    }
  } else{
    char buff[15];
    fscanf(filePointer, "%s", buff);
    mips = atof(buff);
    fclose(filePointer);
  }

  //mendapatkan tid dari master
  int ptid = pvm_parent();

  //mengirimkan mips ke master
  pvm_initsend(PvmDataDefault);
  pvm_pkdouble(&mips, 1,1);
  pvm_send(ptid, 1);

  pvm_exit();
  return 0;
}
