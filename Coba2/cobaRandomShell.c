#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  FILE *outputPointer;
  char buff[9];
  int arr[1000];
  char random[30];
  strcpy(random, "shuf ");
  strcat(random, "-i ");
  strcat(random, argv[1]);
  strcat(random, "-");
  strcat(random, argv[2]);
  strcat(random, " -n 1");

  int i;

  for(i=0; i<10000; i++){
    if((outputPointer = popen(random, "r")) == NULL)
      puts("Perintah tidak bisa dijalankan.");
    else{
      fscanf(outputPointer, "%s", buff);
      pclose(outputPointer);
      arr[i] = atoi(buff);
    }
  }

  for(i=0; i<10000; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}
