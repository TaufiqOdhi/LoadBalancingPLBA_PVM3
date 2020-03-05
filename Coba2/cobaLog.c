#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char *hostname = "ubuntu1";
  double PELoad = 3.12535;

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  FILE *inputPointer;
  FILE *outputPointer;
  char *logFile = "logOverloadedPE.txt";
  char buffIp[15];
  char getIp[50];
  strcpy(getIp, "cat /etc/hosts | grep ");
  strcat(getIp, hostname);
  if((outputPointer = popen(getIp, "r")) == NULL){
    printf("IP Address %s tidak ditemukan !\n", hostname);
  } else{
    fscanf(outputPointer, "%s", buffIp);
    pclose(outputPointer);
  }

  if((inputPointer = fopen(logFile, "a")) == NULL)
    puts("File tidak bisa dibuat.");
  else{
    fprintf(inputPointer,"%d-%02d-%02d %02d:%02d:%02d %s %s %.5f\n",
    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
    hostname, buffIp, PELoad);
    fclose(inputPointer);
  }

  // printf("%d-%02d-%02d %02d:%02d:%02d %s %s %.5f\n",
  // tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
  // hostname, buffIp, PELoad);
  return 0;
}
