#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pvm3.h"

void merge(int arr[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int *L=malloc(n1*sizeof(L));
	int *R=malloc(n2*sizeof(R));

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2){
		if (L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}

void mergeSort(int arr[], int l, int r){
	if (l < r){
		int m = l+(r-l)/2;

		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}

int main(int argc, char const *argv[]) {
  int slice, i, j, upperBound, lowerBound,*arr;
  slice = atoi(argv[1]);
  lowerBound = atoi(argv[2]);
  upperBound = atoi(argv[3]);
  arr = (int*) malloc(slice*sizeof(int));
  srand(time(NULL));
  for(i=0; i<slice; i++){
    arr[i] = rand() % (upperBound + 1 - lowerBound) + lowerBound;
  }

  mergeSort(arr, 0, slice-1);

  //mendapatkan tid dari master
  int ptid = pvm_parent();

  //mengirimkan hasil ke master
  pvm_initsend(PvmDataDefault);
  pvm_pkint(arr, slice, 1);
  pvm_send(ptid, 1);

  pvm_exit();
  return 0;
}
