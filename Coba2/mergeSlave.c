#include<stdio.h>
#include<stdlib.h>
#include "pvm3.h"
#include<time.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int *L=malloc(n1*sizeof(L));
	int *R=malloc(n2*sizeof(R));

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
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

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2){
		arr[k] = R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r){
	if (l < r){
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l+(r-l)/2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}

/* Driver program to test above functions */
int main(int argC, char **argV){
	int  DATA_SIZE, i, ptid;
  DATA_SIZE = atoi(argV[1]);
  int *arr = malloc(DATA_SIZE*sizeof(arr));
  srand(time(NULL));
  for(i=0; i<DATA_SIZE; i++){
    arr[i] = 1+rand()%DATA_SIZE;
  }

  clock_t begin = clock();
  mergeSort(arr, 0, DATA_SIZE - 1);
  clock_t end = clock();

  //mendapatkan tid dari master
  ptid = pvm_parent();

  //mengirimkan hasil array yang sudah diurutkan dengan merge sort
  pvm_initsend(PvmDataDefault);
  pvm_pkint(arr, DATA_SIZE,1);
  pvm_send(ptid, 1);

  //mengirimkan running time dari proses sorting dengan merge sort
  double time_spent[1];
  time_spent[0] = (double)(end - begin)*1000/(double) CLOCKS_PER_SEC;
  pvm_initsend(PvmDataDefault);
  pvm_pkdouble(time_spent, 1,1);
  pvm_send(ptid, 2);

  pvm_exit();
  return 0;
}
