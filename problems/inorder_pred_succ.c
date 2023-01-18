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

node *inorder_successor(node *root, int key) {
    node* succ = NULL;
    while (root != NULL) {
        if (key >= root -> key) {
            root = root -> right;
        }
        else {
            succ = root;
            root = root -> left;
        }
    }
    return succ;
}

node *inorder_predecessor(node *root, int key) {
    node* pred = NULL;
    while (root != NULL) {
        if (key > root -> key) {
            pred = root;
            root = root -> right;
        }
        else {
            root = root -> left;
        }
    }
    return pred;
}


int main() {
    node *root = NULL;
    int key_arr[] = {7, 3, 11, 1, 5, 9, 13, 6, 8};
    for (int i = 0; i<9; i++) {
        insert(&root, key_arr[i]);
    }
    inorder(root);
    //printf("\n%d", inorder_successor(root, 2) -> key);
    printf("\n%d", inorder_predecessor(root, 2) -> key);
}