//Implementação de algoritmo de cheque de caminho euleriano num grafo

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

    grafo->vetor[ponto].tamanho++;

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

    grafo->vetor[destino].tamanho++;
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

//Retorna true se o grafo é conecxo e false caso contrário
static bool buscar(no_lista* no, bool* visitados, Grafo* grafo)
{
	bool todos_visitados = true;	
	for(int i=0; i < grafo->tamanho; i++)
	       if(!visitados[i])
	       {
		       todos_visitados = false;
		       break;
	       }

	//Checar nessa iteração se todas as vértices já foram visitadas, se sim abortar toda a cadeia de busca.
	if(todos_visitados)
		return true;

	//Atravessar por todos os vértices vizinhos que ainda não foram visitados
	do
	{
		//este vértice já foi visitado, próximo
		if(visitados[no->destino])
			continue;

		//Marcar o vértice [vizinho] como visitado
		visitados[no->destino] = true;

		//iniciar busca do grafo vizinho
		if(buscar(grafo->vetor[no->destino].inicio, visitados, grafo))
			return true;

	} while(no = no->prox);

	//Todos os vértices não foram visitados, desconecxo
	return false;
}




bool euleriano_grafo(Grafo* grafo)
{
	bool* visitados = calloc(grafo->tamanho, sizeof(bool));

	for(int i = 0; i < grafo->tamanho; i++)
		visitados[i] = false;

	visitados[0] = true;

	//Iniciar a árvore de busca, retorna true se o grafo é conecxo e false caso contrário
	bool conectado = buscar(grafo->vetor[0].inicio, visitados, grafo);

	free(visitados);
	if(!conectado)
		return false;

	//Teorema de euler: todo grafo com vertices de grau par tem caminho euleriano
	for(int i=0; i<grafo->tamanho; i++)
	{
		if(grafo->vetor[i].tamanho % 2)
			return false;
	}

	return true;
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

    if(euleriano_grafo(grafo))
	    puts("Grafo tem caminho euleriano");
    else
	    puts("Grafo nao tem caminho euleriano");

    return 0;
}
