#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  FILE *outputPointer;
  char taskFile[] = "top -n 1 | grep Tasks | cut -d' ' -f3";
  char tasks[5];
  char hostname[25];

  //mendapatkan jumlah tasks dari perintah terminal
  if((outputPointer = popen(taskFile, "r")) == NULL)
    puts("Perintah tidak bisa dijalankan.");
  else{
    fread(tasks, 1, sizeof(tasks)-1, outputPointer);
    pclose(outputPointer);
  }
  gethostname(hostname,25);
  int tasksInt[] = {atoi(tasks)};
  printf("%d\n", tasksInt[0]);
  printf("%s\n", hostname);

  return 0;
}
