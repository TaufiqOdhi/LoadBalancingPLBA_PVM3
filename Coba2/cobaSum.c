#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  int i, slice, upperBound, lowerBound;
  unsigned long res;
  slice = atoi(argv[1]);
  lowerBound = atoi(argv[2]);
  upperBound = atoi(argv[3]);
  res = 0;
  srand(time(NULL));
  for(i=0; i<slice; i++){
    res += rand() % (upperBound + 1 - lowerBound) + lowerBound;
  }

  printf("%lu\n", res);
  return 0;
}
