#include <stdio.h>
#include <stdlib.h>

int** arr = NULL;

void show(int N);
void check(int* viseted, int cur, int find, int* bol);
void create_dot(int N);

int main(void)
{
    int N = 0;
    
    FILE* f = NULL;
    
    if((f = fopen("data.txt", "r")) != NULL){

        fscanf(f, "%d", &N);

        arr = (int**)calloc(sizeof(int*), N);
        for(int i = 0; i < N; i++){
            arr[i] = (int*)malloc(sizeof(int));
            arr[i][0] = -1;
        }
        
        int c = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                int tmp = 0;
                fscanf(f, "%d", &tmp);
                if(tmp == 1){
                    arr[i][c] = j;
                    c++;
                    arr[i] = (int*)realloc(arr[i], sizeof(int)*(c+1));
                }
            }
            arr[i][c] = -1;
            c = 0;
        }
    }
    else
        printf("File data.txt did not open :(\n");
    
    int bol = 0;
    
    for(int i = 0; i < N; i++){
        int* visited = (int*)calloc(N, sizeof(int));
        check(visited, 0, i, &bol);
        if(bol == 0)
            printf("graph is bad\n");
        bol = 0; 
        free(visited);
    }
    
        
    create_dot(N);
    show(N);
    free(arr);
    getchar();  
    
    return 0;
}

void show(int N){
    for (int i = 0; i < N; i++){
        for(int j = 0; arr[i][j] != -1; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void check(int* viseted, int cur, int find, int* bol){
    if(viseted[cur] == 1) 
        return;

    viseted[cur] = 1;

    if(cur == find){
        *bol = 1;
    }
    else{
        for(int i = 0; arr[cur][i] != -1; i++){
            check(viseted, arr[cur][i], find, bol);
        }
    }
}

void create_dot(int N){
    FILE* f = NULL;

    if((f = fopen("out.dot", "w")) != NULL){
        fprintf(f, "digraph graph {\n");
        for(int i = 0; i < N; i++){
            fprintf(f, "%c ", ('a'+i));
            for(int j = 0; arr[i][j] != -1; j++){
                fprintf(f, "-- %c", ('a'+arr[i][j]));
            }
            fprintf(f, ";\n");
        }
        fprintf(f, "}");
        fclose(f);
    }
    else
        printf("dot cannpt be open\n");
}
