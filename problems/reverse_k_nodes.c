#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* next;
} node;

void insert(node **head, int key) {
    node *temp = (node*) malloc(sizeof(node));
    temp -> key = key;
    if (*head == NULL) {
        temp -> next = NULL;
    }
    else {
        temp -> next = *head;
    }
    *head = temp;
}

void reverse_k_nodes(node **head, int k) {
    if (*head == NULL || k == 0) {
        return;
    } 
    node *temp = *head;
    node *temp_node;
    while (--k) {
        *head = (*head) -> next;
    }
    temp_node = *head; //temp_node = (k)th node
    *head = (*head) -> next; // head = (k+1)th node
    temp_node -> next = NULL; // unlink
    while (temp) { //1,2,3...(k)th node
        temp_node = temp;
        temp = temp -> next;
        temp_node -> next = *head;
        *head = temp_node;
    }
}

void display(node *head) {
    if (head != NULL) {
        printf("%d ", head -> key);
        display(head -> next);
    }
    else {
        printf("\n");
    }
}

int main() {
    node *head = NULL;
    insert(&head, 5);
    insert(&head, 4);
    insert(&head, 3);
    insert(&head, 2);
    insert(&head, 1);
    int k = 3;
    display(head);
    reverse_k_nodes(&head, k);
    display(head);
}