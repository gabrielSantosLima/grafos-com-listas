// busca em largura

#include <stdio.h>
#include <stdlib.h>
#define SIZE 40

typedef struct fila {
  int itens[SIZE];
  int inicio;
  int fim;
} fila;


typedef struct no_lista {
  int destino;
  struct no_lista* prox;
} no_lista;


typedef struct grafo {
  int tamanho;
  int* visitado;
  no_lista** lista_adj;
} grafo;


// Criar uma fila
fila* criarFila() {
  fila* f = malloc(sizeof(fila));
  f->inicio = -1;
  f->fim = -1;
  return f;
}

// Checar se a fila esta vazia
int filaVazia(fila* f) {
  if (f->fim == -1)
    return 1;
  else
    return 0;
}

// adicionar elementos na fila
void enfileirar(fila* f, int valor) {
  if (f->fim == SIZE - 1)
    printf("\nFila esta cheia!");
  else {
    if (f->inicio == -1)
      f->inicio = 0;
    f->fim++;
    f->itens[f->fim] = valor;
  }
}

// Removendo elementos da fila
int desenfileirar(fila* f) {
  int item;
  if (filaVazia(f)) {
    printf("Fila esta vazia");
    item = -1;
  } else {
    item = f->itens[f->inicio];
    f->inicio++;
    if (f->inicio > f->fim) {
      printf("Resetando a fila \n");
      f->inicio = f->fim = -1;
    }
  }
  return item;
}

// imprimindo fila
void imprimirFila(fila* f) {
  int i = f->inicio;

  if (filaVazia(f)) {
    printf("Fila esta vazia");
  } else {
    printf("\nFila contem: ");
    for (i = f->inicio; i < f->fim + 1; i++) {
      printf("%d ", f->itens[i]);
    }
    printf("\n");
  }
}


// Função para criar novo no
no_lista* novoNo(int valor) {
  no_lista* novo_no = malloc(sizeof(no_lista));
  novo_no->destino = valor;
  novo_no->prox = NULL;
  return novo_no;
}


// Função para criar grafo
grafo* criarGrafo(int tamanho) {
  grafo* Grafo = malloc(sizeof(grafo));
  Grafo->tamanho = tamanho;

  Grafo->lista_adj = malloc(tamanho * sizeof(no_lista*));
  Grafo->visitado = malloc(tamanho * sizeof(int));

  for (int i = 0; i < tamanho; i++) {
    Grafo->lista_adj[i] = NULL;
    Grafo->visitado[i] = 0;
  }
  return Grafo;
}

// Adicionar arestas
void adicionarArestas(grafo* Grafo, int ponto, int destino) {
  no_lista* novo_no = novoNo(destino);
  novo_no->prox = Grafo->lista_adj[ponto];
  Grafo->lista_adj[ponto] = novo_no;

  // Add aresta de destino ate o ponto
  novo_no = novoNo(ponto);
  novo_no->prox = Grafo->lista_adj[destino];
  Grafo->lista_adj[destino] = novo_no;
}


// Função do BFS
void BFS(grafo* Grafo, int ini_vert) {
  fila* f = criarFila();
  Grafo->visitado[ini_vert] = 1;
  enfileirar(f, ini_vert);

  while (!filaVazia(f)) {
    imprimirFila(f);
    int atual_vert = desenfileirar(f);
    printf("Visitado %d\n", atual_vert);

    no_lista* temp = Grafo->lista_adj[atual_vert];

    while (temp) {
      int adj_vert = temp->destino;

      if (Grafo->visitado[adj_vert] == 0) {
        Grafo->visitado[adj_vert] = 1;
        enfileirar(f, adj_vert);
      }
      temp = temp->prox;
    }
  }
}



int main() {
  grafo* Grafo = criarGrafo(5);
  adicionarArestas(Grafo, 0, 3);
  adicionarArestas(Grafo, 0, 2);
  adicionarArestas(Grafo, 0, 1);
  adicionarArestas(Grafo, 2, 4);

  BFS(Grafo, 0);

  return 0;
}
