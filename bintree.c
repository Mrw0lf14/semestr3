/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

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
    
    insert(&head, 32, 13);
    insert(&head, 31, 14);
    insert(&head, 33, 15);
    insert(&head, 37, 15);
    insert(&head, 36, 15);
    insert(&head, 39, 15);
    
    traverse(head);
    delete(&head, 33);
    traverse(head);
    
    return 0;
}

void insert(struct bin** head, int key, int val){
    
    if(*head == NULL){
        *head = (struct bin*)malloc(sizeof(struct bin));
        if(*head == NULL) return;
        (*head)->key = key;
        (*head)->val = val;
    }
    else if(key < (*head)->key)
        insert(&((*head)->left), key, val);
    else if(key > (*head)->key)
        insert(&((*head)->right), key, val);
        
}

struct bin* find(struct bin* head, int key){
    
    if(head == NULL) return NULL;
    
    if(head->key == key) 
        return head;
    else if(key < head->key)
        return find(head->left, key);
    else if(key > head->key)
        return find(head->right, key);
        
    return NULL;
        
}

void traverse(struct bin* head){
    
    if(head != NULL){
        printf("%d\n", head->key);
        
        if(head->left != NULL)
            printf("left of %d is ", head->key); 
        traverse(head->left);
        
        if(head->right != NULL)
            printf("right of %d is ", head->key); 
        traverse(head->right);
    }
    
}

void delete(struct bin** head, int key){
    
    if(*head == NULL) return;
    
    if(key < (*head)->key)
        delete(&((*head)->left), key);
    else if(key > (*head)->key)
        delete(&((*head)->right), key);
    else if(key == (*head)->key){
        if((*head)->right == NULL && (*head)->left == NULL){
            printf("delete %d\n", (*head)->key);
            struct bin* tp = *head;
            free(tp);
            tp = NULL;
        }
        else if((*head)->right == NULL || (*head)->left == NULL){
            if((*head)->right != NULL){
                
                struct bin* tp = *head;
                (*head) = tp->right;
                free(tp);
                tp = NULL;
            }
            else if((*head)->left != NULL){
                struct bin* tp = *head;
                (*head) = tp->left;
                free(tp);
                tp = NULL;
            }
        }
        
        if((*head)->right != NULL && (*head)->left != NULL){
            if((*head)->right->left == NULL){
                (*head) = (*head)->right;
                delete(&((*head)->right), key);
            }
            else{
                (*head) = (*head)->left;
                delete(&((*head)->left), key);
            }
        }
    }

}
