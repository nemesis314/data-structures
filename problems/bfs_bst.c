#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

void insert(node **root, int key) {
    if (*root == NULL) {
        *root = (node*) malloc(sizeof(node));
        (*root) -> key = key;
        (*root) -> left = (*root) -> right = NULL;
    }
    else {
        if (key < (*root) -> key) {
            insert(&((*root) -> left), key);
        }
        else {
            insert(&((*root) -> right), key);
        }
    }
}

void bfs_traversal(node *root) {
    if (!root) { return; }
    node *queue[MAX_SIZE];
    queue[0] = root;
    int front = 0,
        rear = 0;
    while (front <= rear) {
        //print
        printf("%d ", queue[front] -> key);
        //enqueue
        if (queue[front] -> left) {
            queue[++rear] = queue[front] -> left;
        }
        if (queue[front] -> right) {
            queue[++rear] = queue[front] -> right;
        }
        //dequeue
        ++front;
    }
}

void inorder(node *root) {
    if (root != NULL) {
        inorder(root -> left);
        printf("%d ", root -> key);
        inorder(root -> right);
    }
}

int main() {
    node *root = NULL;
    node *new_root;
    int key_arr[] = {7, 3, 11, 1, 5, 9, 13};
    for (int i = 0; i<7; i++) {
        insert(&root, key_arr[i]);
    }
    //inorder(root);
    printf("\n");
    bfs_traversal(root);
}