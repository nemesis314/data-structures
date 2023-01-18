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

int from_last_nth(node *head, int n) {
    if (head == NULL) {
        return 0;
    }
    else {
        int pos = 1 + from_last_nth(head -> next, n);
        if (pos == n) {
            printf("\n%d", head -> key);
            //return head -> key;
        }
        return pos;
    }
}

int main() {
    node *head = NULL;
    int arr[] = {5,4,3,2,1,0};
    for (int i = 0; i<6; i++) {
        insert(&head, arr[i]);
    }
    display(head);
    from_last_nth(head, 4);
}