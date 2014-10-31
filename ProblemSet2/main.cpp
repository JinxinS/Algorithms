#include <stdlib.h>
#include <stdio.h>
//#define RIGHT_MOST
//#define LEFT_MOST
long noc = 0;
void  quicksort(int* arr, int i,int k);
void  check_order(int* arr,int len);
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
		array[i] = atoi(line);
//		printf("[%d] %d \n",i,array[i]);
		i++;
	}
	
printf("arry length %d -> %d\n",0,num_of_lines-1);
	quicksort(array,0,num_of_lines-1);
	check_order(array,num_of_lines);
	printf("number of comparation is %d \n",noc);
	free(array);
	fclose(fp);
	return EXIT_SUCCESS;
}

#include <algorithm>



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


int partition(int * arr, int l, int r){
	noc +=( r-l);
	int pivotIndex = choose_pivot(arr,l,r);
	int pivotValue = arr[pivotIndex];
	int storeIndex = l+1;
	for(int idx = l+1; idx <= r; ++idx ){
		if (arr[idx] < pivotValue){
		   int tmp = arr[idx];
		   arr[idx] = arr[storeIndex];
		   arr[storeIndex] = tmp; 
		   ++storeIndex;		
		}
	}
	int temp = arr[storeIndex-1];
	arr[storeIndex-1] = pivotValue;
	arr[l] = temp;
	return storeIndex-1;

}

void quicksort(int* arr, int i,int k){

     if( i < k ){
	int p = partition(arr,i,k);
	quicksort(arr,i,p-1);
	quicksort(arr,p+1,k);	
      }
	
}

void check_order(int* a,int n){
	for (int i = 0 ; i< n -1; ++i)
	  if(a[i]> a [i+1]){
		printf("out of order ! a [%d]( %d) > a[%d] (%d) \n",i,a[i],i+1,a[i+1]);
		exit(1);
	  }	



}
