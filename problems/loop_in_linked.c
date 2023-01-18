#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
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

void display(node *head) {
    if (head != NULL) {
        printf("%d ", head -> key);
        display(head -> next);
    } 
}

void fix_loop(node **head){
    node *curr = *head;
    while(curr){
        node* temp = *head;
        if (curr -> next == curr) { //node pointing itself
            curr -> next = NULL;
            break;
        }
        while(temp != curr) { 
            if(curr -> next == temp) {
                curr -> next = NULL;
                break;
            }
            temp = temp -> next;
        }
        curr = curr -> next;
    }
}

int main() {
    node *head = NULL;
    node *pts[6];
    int arr[] = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i<6; i++) {
        insert(&head, arr[i]);
        pts[i] = head;
    }
    pts[0] -> next = pts[3];
    fix_loop(&head);
    display(head);
}