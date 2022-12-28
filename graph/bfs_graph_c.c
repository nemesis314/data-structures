#include <stdio.h>
#include <stdlib.h>

//queue structures
typedef struct qnode {
    int key;
    struct qnode *next;
} qnode;

typedef struct queue {
    struct qnode *front;
    struct qnode *rear;
} queue;

//graph structures
typedef struct graph {
    int N;
    struct node *arr;
} graph;

typedef struct node {
    int status;
    struct edge *head; 
} node;

typedef struct edge {
    int dest;
    struct edge *next;
} edge;

//queue functions
queue *create_queue() {
    queue *temp = (queue*) malloc(sizeof(queue));
    temp -> front = temp -> rear = NULL;
    return temp;
}

void enqueue(queue *q, int key) {
    qnode *temp = (qnode*) malloc(sizeof(qnode));
    temp -> key = key;
    temp -> next = NULL;
    if (q -> front == NULL && q -> rear == NULL) {
        q -> front = q -> rear = temp;
    }
    else {
        q -> rear -> next = temp;
        q -> rear = temp;
    }
}

int dequeue(queue *q) {
    if (q -> front == NULL) {
        return -1;
    }
    qnode *temp = q -> front;
    int key = temp -> key;
    q -> front = q -> front -> next;
    if (q -> front == NULL) {
        q -> rear = NULL;
    }
    free(temp);
    return key;
}

int isempty(queue *q) {
    if (q -> front == NULL && q -> rear == NULL) {
        return 1;
    }
    return 0;
}

//graph functions
graph *create_graph(int vertices) {
    graph *temp = (graph*) malloc(sizeof(graph));
    temp -> N = vertices;
    temp -> arr = (node*) malloc(sizeof(node) * vertices);
    for (int i = 0; i<vertices; i++) {
        temp -> arr[i].head = NULL;
        temp -> arr[i].status = 0;
    }
    return temp;
}


//adds a edge from src to dest (directed)
void add_edge(graph *g, int src, int dest) {
    edge *temp = (edge*) malloc(sizeof(edge));
    temp -> dest = dest;
    if (g -> arr[src].head) {
        temp -> next = g -> arr[src].head;
    }
    else {
        temp -> next = NULL;
    }
    g -> arr[src].head = temp;
}

//adds edge from src to dest (undirected)
void add_edge_u(graph *g, int src, int dest) {
    add_edge(g, src, dest);
    add_edge(g, dest, src);
}

void print_graph(graph *g) {
    int N = g -> N;
    for (int i = 0; i<N; i++) {
        edge *temp = g -> arr[i].head;
        printf("%d", i);
        while (temp) {
            printf(" --> %d", temp -> dest);
            temp = temp -> next;
        }
        printf(" --> NULL\n");
    }
}

void bfs_traversal(graph *g, int src) {
    int new_src;
    edge *temp;
    queue *queue = create_queue();
    enqueue(queue, src);
    g -> arr[src].status = 1;
    while (!isempty(queue)) {
        new_src = dequeue(queue);
        printf("--> %d ", new_src);
        temp = g -> arr[new_src].head;
        while (temp) {
            if (g -> arr[temp -> dest].status == 0) {
                enqueue(queue, temp -> dest);
                g -> arr[temp -> dest].status = 1;
            }
            temp = temp -> next;
        }
    }
}

int main() {
    graph* graph = create_graph(7);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 1);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 4);
    add_edge(graph, 3, 5);
    add_edge(graph, 4, 2);
    add_edge(graph, 4, 5);
    add_edge(graph, 5, 6);
    print_graph(graph);
    printf("BFS :\n");
    bfs_traversal(graph, 0);
}
