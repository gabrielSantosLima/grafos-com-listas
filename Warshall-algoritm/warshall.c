#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int vertex;
    struct Node *next;

} Node;

typedef struct Graph
{
    int numVertices;
    struct Node **adjLists;

} Graph;

Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node **)malloc(vertices * sizeof(Node *));

    int i;
    for (i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void addEdge(Graph *graph, int src, int dest)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void warshall(Graph *graph)
{
    int i, j, k, m, n;
    int reach[graph->numVertices][graph->numVertices];

    for (i = 0; i < graph->numVertices; i++)
    {
        for (j = 0; j < graph->numVertices; j++)
        {
            reach[i][j] = 0;
        }
    }

    for (i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjLists[i];
        while (temp)
        {
            reach[i][temp->vertex] = 1;
            temp = temp->next;
        }
    }

    for (k = 0; k < graph->numVertices; k++)
    {
        for (i = 0; i < graph->numVertices; i++)
        {
            for (j = 0; j < graph->numVertices; j++)
            {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }

    printf("Transitive closure of the graph:\n");

    /* Display the matrix */
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d\t", reach[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int main()
{
    int tamanho = 4;
    Graph *Grafo = createGraph(tamanho);
    addEdge(Grafo, 0, 1);
    addEdge(Grafo, 0, 4);
    addEdge(Grafo, 1, 2);
    addEdge(Grafo, 1, 3);
    addEdge(Grafo, 1, 4);
    addEdge(Grafo, 2, 3);
    addEdge(Grafo, 3, 4);

    warshall(Grafo);

}