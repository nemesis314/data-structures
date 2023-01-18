#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int rflag;
    struct node *left;
    struct node *right;
} node;

node *cnode(int key) {
    node *temp = (node*) malloc(sizeof(node));
    temp -> key = key;
    temp -> left = temp -> right = NULL;
    temp -> rflag = 0;
    return temp;
}

node *inorder_succesor(node *root, int key) {
    node *succ = NULL;
    while (root) {
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

void inorder(node *root) {
    if (root) {
        inorder(root -> left);
        printf("%d ", root -> key);
        inorder(root -> right);
    }
}

/*
void thread(node *root, node *cons) {
    if (root) {
        if (root -> right == NULL) {
            root -> right = inorder_succesor(cons, root -> key);
            root -> rflag = 1;
        }
        if (!(root -> rflag)) {
            thread(root -> right, cons);
        }
        thread(root -> left, cons);
    }
}
*/

node *leftmost(node *root) {
    if (root) {
        while (root -> left) {
            root = root -> left;
        }
    }
    return root;
}

int count_nodes(node *root) {
    root = leftmost(root);
    int count = 0;
    while (root) {
        count++;
        if (root -> rflag) {
            root = root -> right;
        }
        else {
            root = leftmost(root -> right);
        }
    }
    return count;
}

int main() {
    node *rt = cnode(6);
    rt -> left = cnode(3);
    rt -> left -> left = cnode(1);
    rt -> left -> right = cnode(5);
    rt -> right = cnode(8);
    rt -> right -> right = cnode(11);
    rt -> right -> right -> right = cnode(13);
    rt -> right -> left = cnode(7);
    rt -> right -> right -> left = cnode(9);
    rt -> left -> left -> right = inorder_succesor(rt, 1); //
    rt -> left -> left -> rflag = 1;
    rt -> left -> right -> right = inorder_succesor(rt, 5); //
    rt -> left -> right -> rflag = 1;
    rt -> right -> left -> right = inorder_succesor(rt, 7); //
    rt -> right -> left -> rflag = 1;
    rt -> right -> right -> left -> right = inorder_succesor(rt, 9); //
    rt -> right -> right -> left -> rflag = 1;
    
    //inorder(rt);
    //thread(rt, rt);
    printf("%d", count_nodes(rt));
}