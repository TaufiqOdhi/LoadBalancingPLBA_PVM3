#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const *argv[]){
  int n = atoi(argv[1]);
  int i;
  unsigned long a = atoi(argv[2]);
  unsigned long b = atoi(argv[3]);
  unsigned long *arr = malloc(n*sizeof(unsigned long));

  for (i = 0; i <= n; i++){
     arr[i] = a + b;
     a = b;
     b = arr[i];
  }

  //printf("%lu\n", arr[n-1]);
  for(i=0; i<n; i++){
    printf("%lu ", arr[i]);
  }
  printf("\n");

  return 0;
}
