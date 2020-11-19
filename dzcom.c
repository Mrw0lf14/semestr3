#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void push_arr(long int** arr, int size, int max);
void show_arr(long int* arr, int size);

void quick_sort(long int** harr, int left, int right);
void counting_sort(long int** harr, int size, int max);

int main(void)
{
    long int* arr = NULL;
    int size = -1;
    int max = 0;
    clock_t timer;
    int show = 0;
    
    printf("Do you need to show an array?(0 or 1):\n");
    scanf("%d", &show);
    
    printf("put maxvalue:\n");
    scanf("%d", &max);
        
    while(size != 0){
        printf("put size of array or 0 to exit:\n");
        scanf("%d", &size);
        
        if(size <= 0)
            break;
        
        arr = (long int*)malloc(size*sizeof(long int));
        
        //quick_sort
        push_arr(&arr, size, max);
        if(show == 1){
            printf("original:\n");
            show_arr(arr, size);
        }
        timer = clock();
        quick_sort(&arr, 0, size);
        timer = clock() - timer;
        
        if(show == 1){
            printf("sorted:\n");
            show_arr(arr, size);
        }
        printf("time quick_sort: %.5f\n", (double)timer/CLOCKS_PER_SEC);
        
        //counting_sort
        push_arr(&arr, size, max);
        
        timer = clock();
        quick_sort(&arr, 0, size);
	counting_sort(&arr, size, max);
        timer = clock() - timer;
        
        printf("time counting_sort: %.5f\n", (double)timer/CLOCKS_PER_SEC);
    } 
    
    free(arr);
    return 0;
}

void push_arr(long int** arr, int size, int max){
    long int* p = *arr;
    srand(size);
    for(int i = 0; i < size; i++){
        p[i] = rand() % max;
    }
}

void show_arr(long int* arr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void quick_sort(long int** harr, int left, int right)
{
    long int* arr = *harr;
	srand(time(NULL));
	int i = left; 
	int j = right;
	int y = left + rand() % (right - left);
	int p = arr[y];
	
	do 
	{
		while ((arr[i] < p) && (i < right)) 
		    i++;
		while ((arr[j] > p) && (j > left)) 
		    j--;
		
		if (i <= j)
		{
		    int tmp = arr[i];
		    arr[i] = arr[j];
		    arr[j] = tmp;
			i++; j--;
		}
	} while (i <= j);
	
	if (left < j) 
	    quick_sort(harr, left, j);
	if (right > i) 
	    quick_sort(harr, i, right);
}

void counting_sort(long int** harr, int size, int max){
    long int* arr = *harr;
    long int* count = (long int*)calloc(max, sizeof(long int));
    
    for(int i = 0; i < size; i++){
        count[arr[i]]++;
    }
    
    int c = 0;
    for(int i = 0; i < max; i++){
        for(int j = 0; j < count[i]; j++){
            arr[c] = i;
            c++;
        }
    }
    free(count);
}
