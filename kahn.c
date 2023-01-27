#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0


typedef struct NO
{
    int fonte;
    int destino;
    struct NO *prox;
} NO;

typedef struct VERTICE
{
    int valor;
    NO *adj_list;
} VERTICE;

typedef struct GRAFO
{
    int tamanho;
    VERTICE **lista_vertices;
} GRAFO;

// função para criar grafo
GRAFO *criar_grafo(int tamanho)
{
    GRAFO *grafo = (GRAFO *)malloc(sizeof(GRAFO));
    grafo->tamanho = tamanho;
    grafo->lista_vertices = (VERTICE **)malloc(tamanho * sizeof(VERTICE *));
    int i;
    for (i = 0; i < tamanho; i++)
    {
        grafo->lista_vertices[i] = (VERTICE *)malloc(sizeof(VERTICE));
        grafo->lista_vertices[i]->valor = i;
        grafo->lista_vertices[i]->adj_list = NULL;
    }
    return grafo;
}

void adicionar_vertice(GRAFO *grafo, int fonte, int destino)
{
    NO *novo_no = (NO *)malloc(sizeof(NO));
    novo_no->fonte = fonte;
    novo_no->destino = destino;
    novo_no->prox = grafo->lista_vertices[fonte]->adj_list;
    grafo->lista_vertices[fonte]->adj_list = novo_no;
}

void kahnAlgorithm(GRAFO* grafo)
{
    int i;

    // Criação e inicialização da lista de grau de entrada
    const int tam = grafo->tamanho;
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
            }
            lista = lista->prox;
        }
    }

    printf("Ordem topológica:");
    for(int j = 0; j < grafo->tamanho; j++)
    {
        printf("%d -> ", ordem_top[j]);
    }

}


int main()
{
    int tamanho = 6;
    GRAFO *Grafo = criar_grafo(tamanho);
    adicionar_vertice(Grafo, 0, 1);
    adicionar_vertice(Grafo, 0, 4);
    adicionar_vertice(Grafo, 1, 2);
    adicionar_vertice(Grafo, 1, 3);
    adicionar_vertice(Grafo, 1, 4);
    adicionar_vertice(Grafo, 2, 3);
    adicionar_vertice(Grafo, 3, 4);

    kahnAlgorithm(Grafo);

    return 0;
}