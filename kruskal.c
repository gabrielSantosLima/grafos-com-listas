#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000

// Edge structure
struct Edge
{
    int src, dest, weight;
};

// ListNode structure
struct ListNode
{
    int dest, weight;
    struct ListNode *next;
};

// Linked list structure
struct LinkedList
{
    struct ListNode *head;
};

// Graph structure
struct Graph
{
    int V, E;
    struct Edge *edge;
    struct LinkedList *array;
};

// Creates a graph with V vertices and E edges
struct Graph *createGraph(int V, int E)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge *)malloc(E * sizeof(struct Edge));
    graph->array = (struct LinkedList *)malloc(V * sizeof(struct LinkedList));
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

// Adds an edge to the graph
void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Comparison function for sorting edges by weight
int compare(const void *a, const void *b)
{
    struct Edge *a1 = (struct Edge *)a;
    struct Edge *b1 = (struct Edge *)b;
    return a1->weight > b1->weight;
}

// Finds the parent of a node in a disjoint set
int findParent(int *parent, int i)
{
    if (parent[i] == -1)
        return i;
    return findParent(parent, parent[i]);
}

// Perform union operation on two disjoint sets
void unionSet(int *parent, int x, int y)
{
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    parent[xset] = yset;
}

// Kruskal algorithm for finding a minimum spanning tree
void Kruskal(struct Graph *graph)
{
    int V = graph->V;
    int E = graph->E;
    int i, e, x, y;

    // Sort edges by weight
    qsort(graph->edge, E, sizeof(graph->edge[0]), compare);

    // Initialize disjoint sets
    int *parent = (int *)malloc(V * sizeof(int));
    for (i = 0; i < V; i++)
        parent[i] = -1;

    // Iterate through edges and add to MST if they don't form a cycle
    e = 0;
    i = 0;
    while (e < V - 1)
    {
        struct Edge next_edge = graph->edge[i++];
        x = findParent(parent, next_edge.src);
        y = findParent(parent, next_edge.dest);
        if (x != y)
        {
            printf("Edge %d-%d with weight %d included in MST\n",
                   next_edge.src, next_edge.dest, next_edge.weight);
            unionSet(parent, x, y);
            e++;
        }
    }
    free(parent);
}

void printGraph(struct Graph *graph)
{
    int V = graph->V;
    for (int v = 0; v < V; v++)
    {
        struct ListNode *pCrawl = graph->array[v].head;
        printf("%d: ", v);
        while (pCrawl)
        {
            printf("-> %d(%d)", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int main()
{
    int V = 7;
    int E = 11;
    struct Graph *graph = createGraph(V, E);

    addEdge(graph, 0, 1, 7);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 3, 9);
    addEdge(graph, 1, 4, 7);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 3, 4, 15);
    addEdge(graph, 3, 5, 6);
    addEdge(graph, 4, 5, 8);
    addEdge(graph, 4, 6, 9);
    addEdge(graph, 5, 6, 11);

    printGraph(graph);
    Kruskal(graph);
    printGraph(graph);
    return 0;
}