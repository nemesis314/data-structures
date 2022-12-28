#include <stdio.h>
#include <stdlib.h>

//linked list node for storing graph edges
typedef struct lnode {
    struct edge *gedge;
    struct lnode *next;
} lnode;

//weighted graph
typedef struct graph {
    int N;
    struct gnode *arr;
} graph;

typedef struct gnode {
    struct edge *head; 
} gnode;

typedef struct edge {
    int src;
    int dest;
    int weight;
    struct edge *next;
} edge;

graph *create_graph(int vertices) {
    graph *temp = (graph*) malloc(sizeof(graph));
    temp -> N = vertices;
    temp -> arr = (gnode*) malloc(sizeof(gnode) * vertices);
    for (int i = 0; i<vertices; i++) {
        temp -> arr[i].head = NULL;
    }
    return temp;
}

//adds a edge from src to dest (directed)
void add_edge(graph *g, int src, int dest, int weight) {
    edge *temp = (edge*) malloc(sizeof(edge));
    temp -> src = src;
    temp -> dest = dest;
    temp -> weight = weight;
    if (g -> arr[src].head) {
        temp -> next = g -> arr[src].head;
    }
    else {
        temp -> next = NULL;
    }
    g -> arr[src].head = temp;
}

//adds edge from src to dest (undirected)
void add_edge_u(graph *g, int src, int dest, int weight) {
    add_edge(g, src, dest, weight);
    add_edge(g, dest, src, weight);
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

//graph to edge linkedlist sorted in ascending order of weights of edges
lnode* graph_to_linkedlist(graph *g) {
    lnode *head = NULL;
    int N = g -> N;
    for (int i = 0; i<N; i++) {
        edge *temp_edge = g -> arr[i].head;
        while (temp_edge) {
            lnode *temp_lnode = (lnode*) malloc(sizeof(lnode));
            temp_lnode -> gedge = temp_edge;
            
            //finding proper position for edge in linked list
            if (head == NULL || (temp_lnode -> gedge -> weight) <= (head -> gedge -> weight)) {
                temp_lnode -> next = head;
                head = temp_lnode;
            }
            else {
                lnode *temp_head = head;
                while (temp_head -> next != NULL && (temp_lnode -> gedge -> weight) > (temp_head -> next -> gedge -> weight)) {
                    temp_head = temp_head -> next;
                }
                temp_lnode -> next = temp_head -> next;
                temp_head -> next = temp_lnode;
            }
            temp_edge = temp_edge -> next;
        }
    }
    return head;
}

//print edge list
void print_edges(lnode *head) {
    edge *temp;
    printf("src | dest | weight");
    while (head) {
        temp = head -> gedge;
        printf("\n%d\t%d\t%d", temp -> src, temp -> dest, temp -> weight);
        head = head -> next;
    }
    printf("\n");
}

//disjoint set / union find functions
int root(int parents[], int i) {
    while (parents[i] != i) {
        i = parents[i];
    }
    return i;
}

void connect(int parents[], int p, int q) {
    parents[root(parents, p)] = root(parents, q);
}

//kruskal's algorithm to find minimum spanning tree
graph *kruskal_mst(lnode *head, int vertices) {
    graph *mst = create_graph(vertices);
    edge *temp_edge;
    int parents[vertices], total_weight = 0;
    for (int i = 0; i<vertices; i++) {
        parents[i] = i;
    }
    while (head) {
        temp_edge = head -> gedge;
        int r1 = root(parents, temp_edge -> src),
            r2 = root(parents, temp_edge -> dest);
        if (r1 != r2) {
            add_edge(mst, temp_edge -> src, temp_edge -> dest, temp_edge -> weight);
            connect(parents, r1, r2);
            total_weight += temp_edge -> weight;
        }
        head = head -> next;
    }
    printf("TOTAL COST : %d\n", total_weight);
    return mst;
}

int main() {
    int v, s, d, w;
    printf("Input no. of vertices : ");
    scanf("%d", &v);
    graph* Graph = create_graph(v);
    printf("Input edges (source, destination and weight)\nEnter -1 to exit :\n");
    while (1) {
        scanf("%d", &s);
        if (s == -1) {
            break;
        }
        scanf("%d%d", &d, &w);
        add_edge(Graph, s, d, w);
    }
    graph *kmst = kruskal_mst(graph_to_linkedlist(Graph), v);
    printf("MST OBTAINED FROM KURSKAL'S ALGORITHM :\n");
    print_graph(kmst);
}
