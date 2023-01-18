#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

node *create_node(int key) {
    node *temp = (node*) malloc(sizeof(node));
    temp -> key = key;
    temp -> left = temp -> right = NULL;
}

void insert(node **root, int key) {
    if (*root == NULL) {
        *root = create_node(key);
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

void inorder(node *root) {
    if (root != NULL) {
        inorder(root -> left);
        printf("%d ", root -> key);
        inorder(root -> right);
    }
}

int ancestors(node *root, int key) {
    if (root == NULL) {
        return 0;
    }
    else if (key < root -> key) {
        if (ancestors(root -> left, key)) {
            printf("%d ", root -> key);
        }
    }
    else if (key > root -> key) {
        if (ancestors(root -> right, key)) {
            printf("%d ", root -> key);
        }
        
    }
    else {
        return 1;
    }
}

int main() {
    node *root = NULL;
    int key_arr[] = {7, 3, 11, 1, 5, 9, 13, 6, 8};
    for (int i = 0; i<9; i++) {
        insert(&root, key_arr[i]);
    }
    ancestors(root, 8);
    
}