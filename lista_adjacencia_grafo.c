#include <stdio.h>
#include <stdlib.h>

typedef struct adjacencia {
    int vertice; 
    struct adjacencia *prox; 
} ADJACENCIA;


typedef struct vertice {
    ADJACENCIA *inicio; 
}VERTICE;


typedef struct grafo {
    int vertices; 
    VERTICE *vet; 
}GRAFO;


/*criar um GRAFO*/
GRAFO *criarGrafo (int v) {
	GRAFO *grafo = (GRAFO *)malloc(sizeof(GRAFO)); 
	grafo->vertices = v; 
	grafo->vet = (VERTICE *)malloc(v*sizeof(VERTICE)); 
	
  for (int i=1; i<=v; i++)
		grafo->vet[i].inicio = NULL; 
	
	return(grafo);
}


/*adicionar arestas no GRAFO*/
ADJACENCIA *AdicionarAresta(int vertice){ 
	ADJACENCIA *temp = (ADJACENCIA *) malloc (sizeof(ADJACENCIA)); 
	temp->vertice = vertice; 
	temp->prox = NULL; 
	return(temp); 
}


/*adicionar arestas no GRAFO*/
int criarAresta(GRAFO *grafo, int vertice_ini, int vertice_final) { 
	if(!grafo) return (0);   
	if((vertice_final<0)||(vertice_final >= grafo->vertices))return(0); 
	if((vertice_ini<0)||(vertice_final >= grafo->vertices))return(0); 
	
	ADJACENCIA *novo = AdicionarAresta(vertice_final); 
	novo->prox = grafo->vet[vertice_ini].inicio; 
	grafo->vet[vertice_ini].inicio = novo; 
	return (1);
}


/*Imprimir lista de os vertices adjacentes*/
void imprime(GRAFO *grafo){
	for(int i=1; i <= grafo->vertices; i++){
		ADJACENCIA *adj = grafo->vet[i].inicio; 
    printf("\n Lista de adjacência do vértice %d\n Inicio ", i);
			
      while(adj){ 
				printf("-> %d ", adj->vertice);
				adj = adj->prox; 
			}
		printf("\n");	
	}
}


int main(){
	
	GRAFO * grafo = criarGrafo(6);
	criarAresta(grafo, 1, 2);
	criarAresta(grafo, 1, 3);
	criarAresta(grafo, 2, 4);
	criarAresta(grafo, 2, 7);
	criarAresta(grafo, 3, 1);
	criarAresta(grafo, 4, 3);
	criarAresta(grafo, 5, 2);
	criarAresta(grafo, 6, 1);
	criarAresta(grafo, 6, 4);

    
  imprime(grafo);
}