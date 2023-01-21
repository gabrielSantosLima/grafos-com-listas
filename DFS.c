// busca em profundidade

#include <stdio.h>
#include <stdlib.h>

typedef struct no_lista {
  int destino;
  struct no_lista* prox;
}no_lista;


typedef struct grafo {
  int tamanho;
  int* visitado;
  // armazenar uma matriz de lista de adjacencia
  struct no_lista** lista_adj;
}grafo;


// função para criar novo no
no_lista* novoNo(int destino) {
  no_lista* novoNo = (no_lista*) malloc(sizeof(no_lista));
  novoNo->destino = destino;
  novoNo->prox = NULL;
  return novoNo;
}


// Função para criar grafo
grafo* criarGrafo(int tamanho) {
  grafo* Grafo = (grafo*) malloc(sizeof(grafo));
  Grafo->tamanho = tamanho;
  Grafo->lista_adj = malloc(tamanho * sizeof(no_lista*));
  Grafo->visitado = malloc(tamanho * sizeof(int));

  for (int i = 0; i < tamanho; i++) {
    Grafo->lista_adj[i] = NULL;
    Grafo->visitado[i] = 0;
  }
  return Grafo;
}


// Função para adicionar arestas na lista 
void adicionarArestas(grafo* Grafo, int ponto, int destino) {

  no_lista* novo_no = novoNo(destino);
  novo_no->prox = Grafo->lista_adj[ponto];
  Grafo->lista_adj[ponto] = novo_no;

  // adicionar arestas do destino ate o ponto
  novo_no = novoNo(ponto);
  novo_no->prox = Grafo->lista_adj[destino];
  Grafo->lista_adj[destino] = novo_no;
}


// Função do DFS
void DFS(grafo* Grafo, int destino) {
  no_lista* list_adjacencia = Grafo->lista_adj[destino];
  no_lista* temp = list_adjacencia;
  
  printf("Visitados");

  Grafo->visitado[destino] = 1;
  printf("-> %d \n", destino);

  while (temp != NULL) {
    int conectaVertices = temp->destino;
    if (Grafo->visitado[conectaVertices] == 0) {
      DFS(Grafo, conectaVertices);
    }
    temp = temp->prox;
  }
}


int main() {
  grafo* Grafo = criarGrafo(4);
  
  adicionarArestas(Grafo, 0, 3);
  adicionarArestas(Grafo, 0, 2);
  adicionarArestas(Grafo, 0, 1);
  adicionarArestas(Grafo, 2, 4);

  DFS(Grafo, 0);

  return 0;
}
