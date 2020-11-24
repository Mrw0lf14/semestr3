#include <stdio.h>
#include <stdlib.h>

int** arr = NULL;

void show(int N);
void check(int** visited, int cur);
void create_dot(int** arr, int N);

void show_v(int** arr, int N);
int even_points(int** arr, int N);
int find_ipoints(int** arr, int N);
void delete_ipoints(int*** harr, int N, int k);
int main(void)
{
    int N = 0;
    
    FILE* f = NULL;
    int** arrv = NULL;
    
    if((f = fopen("data.txt", "r")) != NULL){

        fscanf(f, "%d", &N);
        arrv = (int**)malloc(sizeof(int*)*N);
        arr = (int**)calloc(sizeof(int*), N);
        
        for(int i = 0; i < N; i++){
            arr[i] = (int*)malloc(sizeof(int));
            arrv[i] = (int*)malloc(sizeof(int)*N);
            arr[i][0] = -1;
        }
            	   	
        for(int j = 0; j < N; j++){
            for(int i = 0; i < N; i++){
                int tmp = 0;
                fscanf(f, "%d", &tmp);
                arrv[i][j] = tmp;
            }
        }
        
        printf("input\n");	
	show_v(arrv, N);     
	
	
        for(int k = 0; (k = find_ipoints(arrv, N)) != -1;){
        	printf("delete %d\n", k);
    		delete_ipoints(&arrv, N, k);
    		N--; 
    	}
    	
    	printf("after deleting nulls\n");
        show_v(arrv, N);
         	
    	int c = 0;
    	for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
            	if(arrv[j][i] >= 1){
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
    
    fclose(f);
    
    int* visited = (int*)calloc(N, sizeof(int));
    check(&visited, 0);
    printf("visited\n");
    int isConnect = 1;
    for(int i = 0; i < N; i++){
        printf("%d ", visited[i]);
        if(visited[i] == 0)
        	isConnect = 0;
    }
    free(visited);
    
    if(isConnect == 1)
    	printf("\nGraph is connected\n");
    else
    	printf("\nGraph is not connected\n");
    
    int isEven = even_points(arrv, N);
    if(isEven == 1){
    	printf("All points are even\n");
    }
    else{
    	printf("Some points are odd\n");
    }
    
    if(isConnect == 1 && isEven == 1)
    	printf("This is an Eiler's cycle\n");
    else
    	printf("This is Not an Eiler's cycle\n");
    	
    create_dot(arrv, N);
    //show(N);
    system("dot -Tpng out.dot -oout.png");
    
    free(arr);
    free(arrv);
    
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

void check(int** visited, int cur){
    int* vis = *visited;
    if(vis[cur] == 1) 
        return;

    vis[cur] = 1;
    
    for(int i = 0; arr[cur][i] != -1; i++){
        check(&vis, arr[cur][i]);
    }
}

void create_dot(int** arr, int N){
    FILE* f = NULL;

    if((f = fopen("out.dot", "w")) != NULL){
        fprintf(f, "graph abc {\n");
        for(int j = 0; j < N; j++){
            for(int i = j; i < N; i++){
                for(int k = 0; k < arr[i][j]; k++)
                	fprintf(f, "%c -- %c;\n", ('a'+i), ('a'+j));
            }
        }
        fprintf(f, "}");
        fclose(f);
    }
    else
        printf("dot cannpt be open\n");
}

int even_points(int** arr, int N){
	int k = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(i == j)
				continue;
			k += arr[i][j];
		}
		if(k % 2 == 1)
			return 0;
		k = 0;
	}
	return 1;
}

int find_ipoints(int** arr, int N){
	int find = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(i != j)
				find += arr[i][j];		
		}
		if(find == 0)
			return i;
		find = 0;
	}
	return -1;
}

void delete_ipoints(int*** harr, int N, int k){
	int** arr = *harr;
	for(int i = 0; i < N; i++){
		arr[k][i] = arr[(N-1)][i];
		arr[i][k] = arr[(N-1)][i];
	}
}

void show_v(int** arr, int N){
	for(int j = 0; j < N; j++){
		for(int i = 0; i < N; i++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
}
