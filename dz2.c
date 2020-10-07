#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void show(int arr[], int N);
void createDot(int arr[], int N);
void init_points(int arr[], int N);
void show_points(int N);

int** points = NULL;

int main(void)
{
    int N = 0;
    int* arr = NULL;
    FILE* f = NULL;
    
    if((f = fopen("data.txt", "r")) != NULL){

        fscanf(f, "%d", &N);
        points = (int**)malloc(N*sizeof(int*));
        arr = (int*)calloc(sizeof(int), N*N);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                int tmp = 0;
                fscanf(f, "%d", &tmp);
                arr[i+j*N] = tmp;
            }
        }
    }
    else
        printf("File data.txt did not open :(\n");
    
    init_points(arr, N);
    show_points(N);
    show(arr,N);
    fclose(f);
    createDot(arr, N);
    scanf("%d", &N);
    
    
    return 0;
}

void show(int arr[], int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", arr[i+j*N]);
        }
        printf("\n");
    }
}

void createDot(int arr[], int N){
    
    FILE* f = NULL;
    if((f = fopen("out.dot", "w")) != NULL){
        fprintf(f, "digraph graph {\n");
        for(int j = 0; j < N; j++){
            for(int i = 0; i < N; i++){
                if(i == j)
                    fprintf(f, "%c ", (char)('a'+i));
                else if(arr[i+j*N] == 1 && i > j){
                    fprintf(f, "-- %c", (char)('a'+i));
                }
            }
            fprintf(f, ";\n");
        }
        fprintf(f, "}");
    }
    else
        printf("file out.dot did not open :(");
    fclose(f);
}

void init_points(int arr[], int N){
    
    int c = 1;
    
    for(int j = 0; j < N; j++){

        int* tp = (int*)malloc(sizeof(int));

        for(int i = 0; i < N; i++){
            if(arr[i+j*N] == 1 && i != j){
                tp = (int*)realloc(tp, c+1);
                tp[c-1] = i;
                c++;
            }
        }
        tp = (int*)realloc(tp, c+1);
        tp[c] = -1;
        c = 0;
        *(points+j) = tp;
    }
}

void show_points(int N){
    int* tp = NULL;
    for(int i = 0; i < N; i++){
        printf("%d:", i);
        tp = *(points+i);
        for(int j = 0; tp[j] != -1; j++){
            printf(" %d", tp[j]);
        }
        printf("\n");
    }
}
