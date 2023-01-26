#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0


typedef struct NO
{
    int fonte;
    int destino;
    int peso;
    struct NO *prox;
} NO;

typedef struct vertice
{
    int valor;
    NO *adj_list;
} vertice;

typedef struct GRAFO
{
    int tamanho;
    vertice **lista_vertices;
} GRAFO;

// função para criar grafo
GRAFO *createGraph(int vertices)
{
    GRAFO *graph = (GRAFO *)malloc(sizeof(GRAFO));
    graph->tamanho = vertices;

    graph->lista_vertices = (vertice **)malloc(vertices * sizeof(vertice*));

    for (int i = 0; i < vertices; i++)
    {
        graph->lista_vertices[i]->adj_list = NULL;
    }

    return graph;
}

void addEdge(GRAFO *graph, int src, int dest)
{
    struct NO* newNode = (NO *)malloc(sizeof(NO));
    newNode->destino = dest;
    newNode->prox = graph->lista_vertices[src];
    graph->lista_vertices[src] = newNode;
}

void kahnAlgorithm(GRAFO* grafo)
{
    int i;

    // Criação e inicialização da lista de grau de entrada
    int tam = grafo->tamanho;
    int indegree[tam];
    for (int i = 0; i < tam; i++)
    {
        indegree[i] = 0;
    }

    // Verificação dos graus de entrada ao percorrer as listas de adjacência
    for(i = 0; i < tam; i++)
    {
        struct NO* lista = grafo->lista_vertices[i]->adj_list;
        while (lista)
        {
            int j = lista->destino;
            indegree[j]++;
            lista = lista->prox;
        }
    }

    // Criação de fila auxiliar para o algoritmo 
    int fila[tam];
    int start = 0;
    int end = -1;

    // armazena inicialmente os vertices com grau de entrada 0 (nenhum outro chega até eles)
    for(i = 0; i < tam; i++)
    {
        if(indegree[i] == 0)
        {
            fila[++end] = i;
        }
    }


    int visto = 0;
    int ordem_top[tam];
    while(start <= end)
    {
        int u = fila[start++];
        ordem_top[visto++] = u;

        struct NO* lista = grafo->lista_vertices[u]->adj_list;
        while(lista)
        {
            if(!(--indegree[lista->destino]))
            {
                fila[++end] = lista->destino;
                lista = lista->prox;
            }
        }
    }
}


int main()
{
    int tamanho = 6;
    GRAFO *Grafo = createGraph(tamanho);
    addEdge(Grafo, 0, 1);
    addEdge(Grafo, 0, 4);
    addEdge(Grafo, 1, 2);
    addEdge(Grafo, 1, 3);
    addEdge(Grafo, 1, 4);
    addEdge(Grafo, 2, 3);
    addEdge(Grafo, 3, 4);

    kahnAlgorithm(Grafo);

    return 0;
}