#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0


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

    // criar um array da lista de adjacencia (quantidade de vertices definida)
    novo_grafo->vetor = (lista_adjacencia *)malloc(tamanho * sizeof(lista_adjacencia));

    // laço para percorrer a lista de adjacência de um grafo
    for (int i = 0; i < tamanho; i++)
        // aqui se define que o vetor não possui vértices
        novo_grafo->vetor[i].inicio = NULL;

    return novo_grafo;
}