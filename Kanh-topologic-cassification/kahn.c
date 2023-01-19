#include <stdio.h>
#include <stdlib.h>

typedef struct grafo
{
    int numero_vertices;
    int grau_max;       // maximo de arestas que vao ser definidas no input
    int **arestas;      // matriz: linha=vertice coluna=arestas
    int *grau;          // verifica quais ja foram inseridos e as prox posicoes vagas

} Grafo;

Grafo *cria_Grafo(int numero_vertices, int grau_max)
{
    Grafo *gr = (Grafo *)malloc(sizeof(struct grafo));

    gr->numero_vertices = numero_vertices;
    gr->grau_max = grau_max;

    gr->grau = (int *)calloc(numero_vertices, sizeof(int)); // inicia com grau 0
    gr->arestas = (int **)malloc(numero_vertices * sizeof(int *));

    for (int i = 0; i < numero_vertices; i++)
        // cada posicao possui uma lista de adjacencia que tem um tamanho de grau max
        gr->arestas[i] = (int *)malloc(grau_max * sizeof(int));

    return gr;
}

int inserirArestas(Grafo *gr, int ini, int fim)
{
    if (gr == NULL)
        return 0;
    // verifica se o vertice eh valido
    if (ini < 0 || ini >= gr->numero_vertices)
        return 0;
    if (fim < 0 || fim >= gr->numero_vertices)
        return 0;

    // insere no fim da linha
    gr->arestas[ini][gr->grau[ini]] = fim;
    gr->grau[ini]++;

    return 1;
}

void imprimirGrafo(Grafo *gr)
{
    if (gr == NULL)
        return;

    for (int i = 0; i < gr->numero_vertices; i++)
    {
        printf(" %d: ", i);
        for (int j = 0; j < gr->grau[i]; j++)
            printf("-> %d ", gr->arestas[i][j]);

        printf("\n");
    }
}

int * kahnAlg(int n)
{
    int l[n];
    int s[n];

    while(!l[i])
    {

    }

    return l;
}

int main()
{

    //número total de nós no gráfico(rotulado de 0 a 7)
    n = 8;

    Grafo *gr = cria_Grafo(n, 3);


    //Adicionando arestas ao grafo

    inserirArestas(gr, 0, 6);
    inserirArestas(gr, 1, 2);
    inserirArestas(gr, 1, 4);
    inserirArestas(gr, 1, 6);
    inserirArestas(gr, 3, 0);
    inserirArestas(gr, 3, 4);
    inserirArestas(gr, 5, 1);
    inserirArestas(gr, 7, 0);
    inserirArestas(gr, 7, 1);

    // [0] -> 6
    // [1] -> 2, 4
    // [2] -> 
    // [3] -> 0, 4, 1
    // [4] -> 
    // [5] -> 1
    // [6] -> 
    // [7] -> 0, 1


    int vis[n]; 

    l = kahnAlg(gr, 0, vis);
    
    // Printando lista de ordem topologica
    for(i = 0; i < n; i++)
    {
        printf("%d ", l[i])
    }
    printf("\n");

    return 0;
}