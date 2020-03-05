#include <stdio.h>
#include <stdlib.h>

int main (){
  FILE *filePointer;
  char string[4];
  char loadFile[] = "load.txt";
  float load;

  //-f1(5 menit) bisa diganti dengan -f2(10 menit),-f3(15 menit)
  system("cat /proc/loadavg | cut -d' ' -f1 > load.txt");
  if((filePointer = fopen(loadFile, "r")) == NULL)
    puts("File tidak ditemukan.");
  else{
    printf("Load File: ");
    while(1){
      fscanf(filePointer, "%s", string);
      if(feof(filePointer))
        break;
      printf("%s", string);
    }
    fclose(filePointer);
  }

  load = atof(string);
  printf("\n%.2f\n", load);
  return 0;
}
