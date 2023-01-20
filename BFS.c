// busca em largura

#include <stdio.h>
#include <stdlib.h>

typedef struct grafo
{
    int numero_vertices;
    int grau_max;  // maximo de arestas que vao ser definidas no input
    int **arestas; // matriz: linha=vertice coluna=arestas
    int *grau;     // verifica quais ja foram inseridos e as prox posicoes vagas
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

void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado)
{
    int i, vert, NV, cont = 1;
    int *fila, inicio_fila = 0, fim_fila = 0;

    // marcar vertices como nao visitados
    for (i = 0; i < gr->numero_vertices; i++)
        visitado[i] = 0;

    NV = gr->numero_vertices;
    fila = (int *)malloc(NV * sizeof(int));
    fim_fila++;

    // coloca o vertice ini no fim da fila e marca como visitado
    fila[fim_fila] = ini;
    visitado[ini] = cont;

    // equanto a fila nao estiver vazia
    while (inicio_fila != fim_fila)
    {
        // pega o primeiro da fila
        inicio_fila = (inicio_fila + 1) % NV; // (1+1)%2 = 0
        vert = fila[inicio_fila];
        cont++;

        // visita os vizinhos nao visitados e coloca na fila
        for (i = 0; i < gr->grau[vert]; i++)
        {
            if (!visitado[gr->arestas[vert][i]])
            {
                fim_fila = (fim_fila + 1) % NV;
                fila[fim_fila] = gr->arestas[vert][i]; //(5+1) % 2 = 0
                // marca como visitado
                visitado[gr->arestas[vert][i]] = cont;
            }
        }
    }
    for (i = 0; i < gr->numero_vertices; i++)
        printf("%d -> %d\n", i, visitado[i]);
}

int main()
{

    Grafo *gr = cria_Grafo(5, 5);

    inserirArestas(gr, 0, 1);
    inserirArestas(gr, 1, 3);
    inserirArestas(gr, 1, 2);
    inserirArestas(gr, 2, 4);
    inserirArestas(gr, 3, 0);
    inserirArestas(gr, 3, 4);
    inserirArestas(gr, 4, 1);

    int vis[5]; // vetor para marcar a ordem que os vertices foram visitados
    buscaLargura_Grafo(gr, 0, vis);

    return 0;
}