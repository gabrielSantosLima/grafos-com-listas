#include <stdio.h>
#include <stdlib.h>

// Representa um no da lista de adjacencia
typedef struct no_lista
{
    int destino;
    struct no_lista *prox;
} no_lista;

// Representa uma lista de adjacencia
typedef struct lista_adjacencia
{
    int tamanho;
    struct no_lista *inicio;
} lista_adjacencia;

// Representa um grafo. Um grafo é um array da lista de adjacencia
typedef struct grafo
{
    int tamanho; // tamanho do grafo
    struct lista_adjacencia *vetor;
} grafo;

// função para criar novo no
no_lista *criar_novo_no(int destino)
{
    no_lista *novoNo = (no_lista *)malloc(sizeof(no_lista));
    novoNo->destino = destino;
    novoNo->prox = NULL;
    return novoNo;
}

// função para criar grafo
grafo *criar_grafo(int tamanho)
{
    grafo *novo_grafo = (grafo *)malloc(sizeof(grafo));
    novo_grafo->tamanho = tamanho;

    // criar um array da lista de adjacencia
    novo_grafo->vetor = (lista_adjacencia *)malloc(tamanho * sizeof(lista_adjacencia));

    for (int i = 0; i < tamanho; i++)
        novo_grafo->vetor[i].inicio = NULL;

    return novo_grafo;
}

// Função para adicionar arestas na lista
void adicionar_arestas(grafo *cgrafo, int ponto, int destino)
{

    no_lista *checar = NULL;
    no_lista *novo_no = criar_novo_no(destino);

    if (cgrafo->vetor[ponto].inicio == NULL)
    {
        novo_no->prox = cgrafo->vetor[ponto].inicio;
        cgrafo->vetor[ponto].inicio = novo_no;
    }
    else
    {
        checar = cgrafo->vetor[ponto].inicio;
        while (checar->prox != NULL)
            checar = checar->prox;
        checar->prox = novo_no;
    }

    // adicionar arestas do destino ate o ponto
    novo_no = criar_novo_no(ponto);
    if (cgrafo->vetor[destino].inicio == NULL)
    {
        novo_no->prox = cgrafo->vetor[destino].inicio;
        cgrafo->vetor[destino].inicio = novo_no;
    }
    else
    {
        checar = cgrafo->vetor[destino].inicio;
        while (checar->prox != NULL)
            checar = checar->prox;
        checar->prox = novo_no;
    }
}

// Imprimir a lista de adjacencia representando o grafo
void imprimirGrafo(grafo *Grafo)
{
    for (int i = 0; i < Grafo->tamanho; i++)
    {
        no_lista *add = Grafo->vetor[i].inicio;
        printf("\n lista de adjacencia do vertice %d\n head ", i);

        while (add)
        {
            printf("-> %d", add->destino);
            add = add->prox;
        }
        printf("\n");
    }
}

int main()
{
    int tamanho = 5;
    grafo *Grafo = criar_grafo(tamanho);
    adicionar_arestas(Grafo, 0, 1);
    adicionar_arestas(Grafo, 0, 4);
    adicionar_arestas(Grafo, 1, 2);
    adicionar_arestas(Grafo, 1, 3);
    adicionar_arestas(Grafo, 1, 4);
    adicionar_arestas(Grafo, 2, 3);
    adicionar_arestas(Grafo, 3, 4);

    imprimirGrafo(Grafo);

    return 0;
}