#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* next;
};

void show(struct node* head);
void push(struct node** head, int value);
void pop(struct node** head);

int main(void)
{
    
    struct node* head = NULL;
    int arg_menu = 1;
    while(arg_menu != 0){
        printf("Put:\n1 to add\n2 to delete\n3 to show\n0 to exit\n");
        printf("Put mode:\n");
        scanf("%d", &arg_menu);
        if(arg_menu == 1){
            int value;
            printf("Put value:\n");
            scanf("%d", &value);
            push(&head,value);
        }
        if(arg_menu == 2){
          pop(&head);  
        }
        if(arg_menu == 3){
            show(head);
        }
    }
    
    if(head != NULL){
        free(head);
    }
    return 0;
}

void show(struct node* head){
    struct node* tp = head;
    printf("list:\n");
    while(tp != NULL){
        printf("%d ", tp->value);
        tp = tp->next;
    }
    printf("\n");
}
void push(struct node** head, int value){
    struct node* tp = (struct node*)malloc(sizeof(struct node));
    tp->next = NULL;
    tp->value = value;
    if(*head == NULL){
        *head = tp;
    }
    else{
        push(&((*head)->next), value);
    }
}
void pop(struct node** head){
    if(*head != NULL){
        struct node* tp = (*head);
        printf("Deleted: %d\n", tp->value);
        (*head) = (*head)->next;
        free(tp);
    }
}
