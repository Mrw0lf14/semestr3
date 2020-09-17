#include <stdio.h>
#include <stdlib.h>
struct bin{
    int key;
    int val;
    struct bin* left;
    struct bin* right;
};

void insert(struct bin** head, int key, int val);
void delete(struct bin** head, int key);
struct bin* find(struct bin* head, int key);
void traverse(struct bin* head);

int main()
{
    struct bin* head = NULL;
    
    insert(*head, key, val);
    
    if
    return 0;
}

void insert(struct bin** head, int key, int val){
    if(*head == NULL){
        *head = (struct bin*)malloc(sizeof(struct bin));
        if(*head == NULL) return;
    }
    else if(key < (*head)->key)
        insert(&((*head)->left), key, val);
    else if(key < (*head)->key)
        insert(&((*head)->left), key, val);
}
