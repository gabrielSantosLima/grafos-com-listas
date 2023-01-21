//Implementação de algoritmo de cheque de caminho hamiltoniano num grafo

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Representa um Grafo. Um Grafo é um array da lista de adjacencia
typedef struct 
{
    int tamanho; // tamanho do Grafo
    struct lista_adjacencia *vetor;
} Grafo;

// função para criar novo no
no_lista *criar_novo_no(int destino)
{
    no_lista *novoNo = (no_lista *)malloc(sizeof(no_lista));
    novoNo->destino = destino;
    novoNo->prox = NULL;
    return novoNo;
}

// função para criar Grafo
Grafo *criar_grafo(int tamanho)
{
    Grafo *novo_Grafo = (Grafo *)malloc(sizeof(Grafo));
    novo_Grafo->tamanho = tamanho;

    // criar um array da lista de adjacencia
    novo_Grafo->vetor = (lista_adjacencia *)malloc(tamanho * sizeof(lista_adjacencia));

    for (int i = 0; i < tamanho; i++)
        novo_Grafo->vetor[i].inicio = NULL;

    return novo_Grafo;
}

// Função para adicionar arestas na lista
void adicionar_arestas(Grafo *grafo, int ponto, int destino)
{

    no_lista *checar = NULL;
    no_lista *novo_no = criar_novo_no(destino);

    if (grafo->vetor[ponto].inicio == NULL)
    {
        novo_no->prox = grafo->vetor[ponto].inicio;
        grafo->vetor[ponto].inicio = novo_no;
    }
    else
    {
        checar = grafo->vetor[ponto].inicio;
        while (checar->prox != NULL)
            checar = checar->prox;
        checar->prox = novo_no;
    }

    // adicionar arestas do destino ate o ponto
    novo_no = criar_novo_no(ponto);
    if (grafo->vetor[destino].inicio == NULL)
    {
        novo_no->prox = grafo->vetor[destino].inicio;
        grafo->vetor[destino].inicio = novo_no;
    }
    else
    {
        checar = grafo->vetor[destino].inicio;
        while (checar->prox != NULL)
            checar = checar->prox;
        checar->prox = novo_no;
    }
}

// Imprimir a lista de adjacencia representando o Grafo
void imprimirGrafo(Grafo *grafo)
{
    for (int i = 0; i < grafo->tamanho; i++)
    {
        no_lista *add = grafo->vetor[i].inicio;
        printf("\n lista de adjacencia do vertice %d\n head ", i);

        while (add)
        {
            printf("-> %d", add->destino);
            add = add->prox;
        }
        printf("\n");
    }
}

static bool buscar(no_lista* no, bool* visitados, Grafo* grafo)
{
	bool todos_visitados = true;
	
	for(int i=0; i < grafo->tamanho; i++)
	       if(!visitados[i])
	       {
		       todos_visitados = false;
		       break;
	       }

	if(todos_visitados)
	{
		free(visitados);
		return true;
	}


	do
	{
		if(visitados[no->destino])
			continue;

		bool* novo_visitados = calloc(grafo->tamanho, sizeof(bool));

		for(int i=0; i<grafo->tamanho; i++)
			novo_visitados[i] = visitados[i];

		novo_visitados[no->destino] = visitados[no->destino] = true;

		if(buscar(grafo->vetor[no->destino].inicio, novo_visitados, grafo))
		{
			free(visitados);
			return true;
		}

	} while( no = no->prox);

	free(visitados);
	return false;
}

bool hamiltoniano_grafo(Grafo* grafo)
{
	bool* no_visitados = calloc(grafo->tamanho, sizeof(bool));

	for(int i = 0; i < grafo->tamanho; i++)
		no_visitados[i] = false;

	no_visitados[0] = true;

	return buscar(grafo->vetor[0].inicio, no_visitados, grafo);
}


int main()
{
    int tamanho = 5;
    Grafo *grafo = criar_grafo(tamanho);
    adicionar_arestas(grafo, 0, 1);
    adicionar_arestas(grafo, 0, 4);
    adicionar_arestas(grafo, 1, 2);
    adicionar_arestas(grafo, 1, 3);
    adicionar_arestas(grafo, 1, 4);
    adicionar_arestas(grafo, 2, 3);
    adicionar_arestas(grafo, 3, 4);

    imprimirGrafo(grafo);

    if(hamiltoniano_grafo(grafo))
	    puts("Grafo e hamiltoniano");
    else
	    puts("Grafo nao e hamiltoniano");

    return 0;
}
