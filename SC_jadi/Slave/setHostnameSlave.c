#include <stdio.h>
#include <unistd.h>
#include "pvm3.h"

int main(){
  char hostname[25];
  gethostname(hostname,25);

  //mendapatkan tid dari master
  int ptid = pvm_parent();

  //mengirimkan hostname
  pvm_initsend(PvmDataDefault);
  pvm_pkstr(hostname);
  pvm_send(ptid,2);

  pvm_exit();
  return 0;
}
