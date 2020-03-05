#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pvm3.h"

int countDigit(int n){
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}

int main(){
	int DATA_SIZE, cc, tid;
  printf("masukkan jumlah angka: ");
  scanf("%d", &DATA_SIZE);
  char size[countDigit(DATA_SIZE)];
  sprintf(size, "%d", DATA_SIZE);
  int *arr = malloc(DATA_SIZE*sizeof(arr));
  char **argv = malloc(sizeof(char*));
  argv[0] = size;

  //spawn task to slave bernama ubuntu1 dengan argument jumlah angka yang digenerate
	cc = pvm_spawn("./mergeSlave", argv, 1, "ubuntu1", 1, &tid);

	if (cc == 1) {
		cc = pvm_recv(tid, 1);

    //mendapatkan array yang sudah diurutkan
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
		pvm_upkint(arr, DATA_SIZE, 1);
    int i;
    for (i=0; i < DATA_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");

    //mendapatkan hasil running time dari proses merge sort pada slave
    double time_spent[1];
    cc = pvm_recv(tid, 2);
    pvm_bufinfo(cc, (int*)0, (int*)0, &tid);
    pvm_upkdouble(time_spent, 1, 1);
    printf("Total running time : %.3f ms\n", time_spent[0]);
	} else
		printf("can't start mergeSlave\n");

	pvm_exit();
	return 0;
}
