#include <string.h>

//Untuk mendapatkan rata2 current taskLoad dari PE
double *taskLoadPE(char *hostname){
  int tid, cc;
  double *taskLoad = malloc(3*sizeof(taskLoad));
  cc = pvm_spawn("./updateLoadSlave", (char**) 0, 1, hostname, 1, &tid);
  if(cc == 1){
    cc = pvm_recv(tid, 1);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
    pvm_upkdouble(taskLoad, 3, 1);
  }
  else printf("can't start updateLoadSlave\n");

  return taskLoad;
}

//untuk melakukan perpindahan job ke PE yang lebih ringan loadnya
char *jobMigration(struct Node *OPE, struct Node *LPEList, struct Node *ULPEList, double threshold1){
  struct Node *n;

  //mengecek ke LPEList
  n = LPEList;
  while (n != NULL) {
    double *taskLoad = taskLoadPE(n->hostname);

    //taskLoad[0], update setiap 1 menit sekali
    //taskLoad[1], update setiap 5 menit sekali
    //taskLoad[2], update setiap 15 menit sekali
    //membandingkan dengan TaskLoad update setiap 1 menit sekali
    if((n->PELoad+taskLoad[0]) < (0.5*threshold1)){
      printf("Dengan rata2 taskLoad %.3f, ", taskLoad[0]);
      return n->hostname;
    }
    n = n-> next;
  }

  //mengecek ke ULPELIST
  n = ULPEList;
  while (n != NULL) {
    double *taskLoad = taskLoadPE(n->hostname);
    if((n->PELoad+taskLoad[0]) < (0.5*threshold1)){
      printf("Dengan rata2 taskLoad %.3f, ", taskLoad[0]);
      return n->hostname;
    }
    n = n-> next;
  }

  //jika tidak terjadi perpindahan job
  return OPE->hostname;
}

void addLog(struct Node *OPEList){
  struct Node *n;
  FILE *inputPointer;
  char *logFile = "logOverloadedPE.txt";

  n = OPEList;
  while (n != NULL) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    FILE *outputPointer;
    char buffIp[15];
    char getIp[50];
    strcpy(getIp, "cat /etc/hosts | grep ");
    strcat(getIp, n->hostname);
    if((outputPointer = popen(getIp, "r")) == NULL){
      printf("IP Address %s tidak ditemukan !\n", n->hostname);
    } else{
      fscanf(outputPointer, "%s", buffIp);
      pclose(outputPointer);
    }

    if((inputPointer = fopen(logFile, "a")) == NULL)
      puts("File tidak bisa dibuat.");
    else{
      fprintf(inputPointer,"%d-%02d-%02d %02d:%02d:%02d %s %s %.5f\n",
      tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
      n->hostname, buffIp, n->PELoad);
      fclose(inputPointer);
    }

    n = n->next;
  }
}
