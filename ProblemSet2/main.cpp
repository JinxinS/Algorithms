#include <stdlib.h>
#include <stdio.h>

void quicksort(int* arr, int i,int k);

int main(){
	FILE* fp;
	fp = fopen("./QuickSort.txt","r");
	if(fp == NULL) exit(EXIT_FAILURE);
	ssize_t read;
	size_t len = 0;
	char* line= NULL;
	while((read = getline(&line,&len,fp)) != -1){
		printf("%s",line);
	}
	
	int length=32768;
	int *array = (int*)malloc(sizeof(int)*length);

	quicksort(array,1,length);
	free(array);
	return EXIT_SUCCESS;
}


int partition(int * arr, int i, int k){

}

void quicksort(int* arr, int i,int k){
     if( i < k ){
	int p = partition(arr,i,k);
	quicksort(arr,i,p-1);
	quicksort(arr,p+1,k);	
      }	
}
