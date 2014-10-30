#include <stdlib.h>
#include <stdio.h>
int noc = 0;
void  quicksort(int* arr, int i,int k);

int main(){
	FILE* fp;
	fp = fopen("./QuickSort.txt","r");
	if(fp == NULL) exit(EXIT_FAILURE);
	ssize_t read;
	size_t len = 0;
	char* line= NULL;
	int num_of_lines = 0;
	while((read = getline(&line,&len,fp)) != -1){
		++num_of_lines;
	}
	
	rewind(fp);

	
	int *array = (int*)malloc(sizeof(int)*num_of_lines);
	int i = 0;	
	while((read = getline(&line,&len,fp)) != -1){
		i++;
		array[i] = atoi(line);
	}
	

	 quicksort(array,0,num_of_lines-1);

//	for(int i = 0; i< num_of_lines; ++i) printf("%d \n",array[i]);
	printf("number of comparation is %d \n",noc);
	free(array);
	fclose(fp);
	return EXIT_SUCCESS;
}

#include <algorithm>

//#define LEFT_MOST
//#define RIGHT_MOST
int choose_pivot(int *a,int i, int k){
#if defined(LEFT_MOST)
	return i;
#elif defined(RIGHT_MOST)
	int temp = a[i];
	a[i]= a[k];
	a[k] = temp;
	return i;
#else
	int pivot;
	int mid = ((k-i)/2)+i;
	int min = std::min(a[i],std::min(a[k],a[mid]));
	int max = std::max(a[i],std::max(a[k],a[mid]));
	if( (a[i] != max) &&(a[i] != min) ) pivot=i;
	else if( (a[k] != max) &&(a[k] != min) ) pivot=k;
	else pivot = mid;

	int temp = a[i];
	a[i] = a[pivot];
	a[pivot] = temp;
	return i;
#endif
}


int partition(int * arr, int i, int k){
	noc += k-i;
	int pivotIndex = choose_pivot(arr,i,k);
	int pivotValue = arr[pivotIndex];
	int storeIndex = i;
	for(int idx = i; idx <= k; ++idx ){
		if (arr[idx] < pivotValue){
		   int tmp = arr[idx];
		   arr[idx] = arr[storeIndex];
		   arr[storeIndex] = tmp; 
		   ++storeIndex;		
		}
	}
	arr[storeIndex] = pivotValue;
	return storeIndex;

}

void quicksort(int* arr, int i,int k){

     if( i < k ){
	int p = partition(arr,i,k);
	quicksort(arr,i,p-1);
	quicksort(arr,p+1,k);	
      }
	
}
