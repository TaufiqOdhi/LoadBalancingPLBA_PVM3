#include <stdio.h>
#include <stdlib.h>
#include "pvm3.h"

int main(){
  FILE *outputPointer;
  char buff[5];

  //bisa -f3 atau -f2
  char taskFile[] = "top -n 1 -b | grep Tasks | cut -d' ' -f3";

  //mendapatkan jumlah tasks dari perintah terminal
  if((outputPointer = popen(taskFile, "r")) == NULL)
    puts("Perintah tidak bisa dijalankan.");
  else{
    fscanf(outputPointer, "%s", buff);
    pclose(outputPointer);
  }

  //mendapatkan tid dari master
  int ptid = pvm_parent();

  //mengirimkan jumlah tasks ke master
  pvm_initsend(PvmDataDefault);
  pvm_pkstr(buff);
  pvm_send(ptid,5);

  pvm_exit();
  return 0;
}
