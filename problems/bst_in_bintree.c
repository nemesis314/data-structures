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
/*
int is_bst(node *root) {
    if (!root) {
        return 1;
    }
    if (root -> left && root -> left -> key > root -> key) {
        return 0;
    }
    if (root -> right && root -> right -> key < root -> key) {
        return 0;
    }
    if (root -> left && !is_bst(root -> left)) {
        return 0;
    }
    if (root -> right && !is_bst(root -> right)) {
        return 0;
    }
    return 1;
}
*/

int is_bst(node *root) {
    if (!(root -> left) && !(root -> right)) { //null, null
        return 1;
    }
    else if (root -> left && root -> right) { //avail, avail
        if (root -> left -> key < root -> key && root -> right -> key > root -> key) {
            return is_bst(root -> left) && is_bst(root -> right);
        }
    }
    else if (root -> left && !(root -> right)) { //avail, null
        if (root -> left -> key < root -> key) {
            return is_bst(root -> left);
        }
    }
    else if (root -> right && !(root -> left)) { //null, avail
        if (root -> right -> key > root -> key) {
            return is_bst(root -> right);
        }
    }
    return 0;
}


//preorder
node *bst_node(node* root) {
    if (root != NULL) {
        if ((root -> left || root -> right) && is_bst(root)) {
            return root;
        }
        bst_node(root -> left);
        bst_node(root -> right);
    }
}

int main() {
    node *root = NULL;
    node *bst_root = NULL;
    int key_arr[] = {7, 3, 11, 1, 5, 9, 13, 6, 8};
    for (int i = 0; i<9; i++) {
        insert(&bst_root, key_arr[i]);
    }
    root = create_node(15);
    root -> left = create_node(20);
    root -> right = bst_root;
    
    node *bst_node_found = bst_node(root);
    //printf("%d", bst_node_found -> key);
    //inorder(root);
    //printf("%d", is_bst(root));
    printf("\n");
}