#include <stdio.h>
#include <stdlib.h>
#define INF 99999

typedef struct NO
{
    int peso;
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

void adicionar_vertice(GRAFO *grafo, int fonte, int destino, int peso)
{
    NO *novo_no = (NO *)malloc(sizeof(NO));
    novo_no->fonte = fonte;
    novo_no->destino = destino;
    novo_no->peso = peso;
    novo_no->prox = grafo->lista_vertices[fonte]->adj_list;
    grafo->lista_vertices[fonte]->adj_list = novo_no;
}

void floydWarshall(GRAFO *grafo)
{
    int i, j, k;
    int reach[grafo->tamanho][grafo->tamanho];

    for (i = 0; i < grafo->tamanho; i++)
    {
        for (j = 0; j < grafo->tamanho; j++)
        {
            reach[i][j] = 0;
        }
    }

    for (i = 0; i < grafo->tamanho; i++)
    {
        VERTICE *vertice = grafo->lista_vertices[i];
        NO *adj = vertice->adj_list;
        while (adj != NULL)
        {
            reach[adj->fonte - 1][adj->destino - 1] = adj->peso;
            adj = adj->prox;
        }
    }

    for (int i = 0; i < grafo->tamanho; i++)
    {
        for (int j = 0; j < grafo->tamanho; j++)
        {
            if (i != j && reach[i][j] == 0)
                reach[i][j] = INF;
        }
        printf("\n");
    }

    for (int i = 0; i < grafo->tamanho; i++)
    {
        for (int j = 0; j < grafo->tamanho; j++)
        {
            printf("%7d", reach[i][j]);
        }
        printf("\n");
    }

    printf("==================================================\n");

    for (k = 0; k < grafo->tamanho; k++)
    {

        for (i = 0; i < grafo->tamanho; i++)
        {

            for (j = 0; j < grafo->tamanho; j++)
            {

                if (reach[i][k] + reach[k][j] < reach[i][j])
                    reach[i][j] = reach[i][k] + reach[k][j];
            }
        }
    }

    for (int i = 0; i < grafo->tamanho; i++)
    {
        for (int j = 0; j < grafo->tamanho; j++)
        {
            if (reach[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", reach[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int tamanho = 4;
    GRAFO *Grafo = criar_grafo(tamanho);
    adicionar_vertice(Grafo, 1, 2, 5);
    adicionar_vertice(Grafo, 1, 4, 10);
    adicionar_vertice(Grafo, 2, 3, 3);
    adicionar_vertice(Grafo, 3, 4, 1);

    // adicionar_vertice(Grafo, 1, 2, 10);
    // adicionar_vertice(Grafo, 1, 4, 5);
    // adicionar_vertice(Grafo, 2, 4, 9);
    // adicionar_vertice(Grafo, 3, 1, -2);
    // adicionar_vertice(Grafo, 3, 2, 4);
    // adicionar_vertice(Grafo, 4, 2, -3);
    // adicionar_vertice(Grafo, 4, 3, 1);

    // adicionar_vertice(Grafo, 1, 2, 3);
    // adicionar_vertice(Grafo, 1, 3, 8);
    // adicionar_vertice(Grafo, 1, 5, -4);
    // adicionar_vertice(Grafo, 2, 4, 1);
    // adicionar_vertice(Grafo, 2, 5, 7);
    // adicionar_vertice(Grafo, 3, 2, 4);
    // adicionar_vertice(Grafo, 4, 1, 2);
    // adicionar_vertice(Grafo, 4, 3, -5);
    // adicionar_vertice(Grafo, 5, 4, 6);

    floydWarshall(Grafo);
}