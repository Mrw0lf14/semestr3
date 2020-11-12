#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void push_arr(int** arr, int size, int max);
void show_arr(int* arr, int size);

void quick_sort(int** harr, int left, int right);
void counting_sort(int** harr, int size, int max);

int main()
{
    int* arr = NULL;
    int size = -1;
    int max = 0;
    int timer = 0;
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
        
        arr = (int*)malloc(size*sizeof(int));
        
        //quick_sort
        push_arr(&arr, size, max);
        if(show == 1){
            printf("original:\n");
            show_arr(arr, size);
        }
        timer = time(NULL);
        quick_sort(&arr, 0, size);
        timer = time(NULL) - timer;
        
        if(show == 1){
            printf("sorted:\n");
            show_arr(arr, size);
        }
        printf("time quick_sort: %d\n", timer);
        
        //counting_sort
        push_arr(&arr, size, max);
        
        timer = time(NULL);
        quick_sort(&arr, 0, size);
        timer = time(NULL) - timer;
        
        printf("time counting_sort: %d\n", timer);
    } 
    
    free(arr);
    return 0;
}

void push_arr(int** arr, int size, int max){
    int* p = *arr;
    srand(size);
    for(int i = 0; i < size; i++){
        p[i] = rand() % max;
    }
}

void show_arr(int* arr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void quick_sort(int** harr, int left, int right)
{
    int* arr = *harr;
	
	int i = left; 
	int j = right;
	int y = (right+left) / 2;
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

void counting_sort(int** harr, int size, int max){
    int* arr = *harr;
    int* count = (int*)calloc(max, sizeof(int));
    
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
