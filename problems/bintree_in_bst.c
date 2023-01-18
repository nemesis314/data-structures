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

int is_not_bst(node *root) {
    if (root -> left && root -> left -> key > root -> key) {
        return 1;
    }
    else if (root -> right && root -> right -> key < root -> key) {
        return 1;
    }
    else {
        return 0;
    }
}

//preorder
node *not_bst_node(node* root) {
    if (root != NULL) {
        if (is_not_bst(root)) {
            return root;
        }
        else {
            not_bst_node(root -> left);
            not_bst_node(root -> right);
        }
    }
}

int main() {
    node *root = NULL;
    int key_arr[] = {7, 3};//, 11, 1, 5, 9, 13, 6, 8};
    for (int i = 0; i<2; i++) {
        insert(&root, key_arr[i]);
    }
    
    node *temp = root;
    while (temp -> left != NULL) {
        temp = temp -> left;
    }
    temp -> left = create_node(100);
    
    //inorder(root);
    node *non_bst_node = not_bst_node(root);
    //printf("%d", non_bst_node -> key);
    inorder(non_bst_node);
    //inorder(root);
    //printf("\n");
}