#include "algoritma4.h"

//Untuk proses2 yang akan dijalankan, dan penentuan job dikerjakan pada PE mana
void runProses(struct Node **PEList, double threshold1, double threshold2, double alc){
  struct Node *n;
  n = PEList[4];//PEList untuk semua PE yang terhubung

  //diulang sampai proses selesai
  while (n != NULL) {
    char *workHostname;
    if(n->PEType == "OPELIST"){
      workHostname = jobMigration(n, PEList[2], PEList[3], threshold1);
    }else{
      workHostname = n->hostname;
    }
    printf("Yang mengerjakan adalah: %s\n", workHostname);
    n = n->next;
  }

  if(alc >= threshold2){
    //menuliskan log
  }
}
