#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int N;
    struct node *arr;
} graph;

typedef struct node {
    int visited;
    struct edge *head;
} node;

typedef struct edge {
    int dest;
    struct edge *next;
} edge;

graph *create_graph(int vertices) {
    graph *temp = (graph*) malloc(sizeof(graph));
    temp -> N = vertices;
    temp -> arr = (node*) malloc(sizeof(node) * vertices);
    for (int i = 0; i<vertices; i++) {
        temp -> arr[i].head = NULL;
        temp -> arr[i].visited = 0;
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
    printf("Graph :\n");
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

void dfs_traversal(graph* g, int src) {
    printf(" --> %d", src);
    g -> arr[src].visited = 1;
    edge *temp = g -> arr[src].head;
    while (temp) {
        if (g -> arr[temp -> dest].visited == 0) {
            dfs_traversal(g, temp -> dest);
        }
        temp = temp -> next;
    }
}

int main() {
    int v, s, d, s_dfs;
    printf("Input no. of vertices : ");
    scanf("%d", &v);
    graph* graph = create_graph(v);
    printf("Input edges (source and destination), Enter -1 to exit :\n");
    while (1) {
        scanf("%d", &s);
        if (s == -1) {
            break;
        }
        scanf("%d", &d);
        add_edge(graph, s, d);
    }
    print_graph(graph);
    printf("Enter source node for dfs traversal : ");
    scanf("%d", &s_dfs);
    printf("DFS :\n");
    dfs_traversal(graph, s_dfs);
}
