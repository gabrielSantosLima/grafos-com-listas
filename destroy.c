#include <stdlib.h>

typedef struct no
{
    int v; /* Vértice */
    struct no *prox;
} No;

typedef struct grafo
{
    int n; /* Número de nós */
    No **lista;
} Grafo;

void cria_grafo(Grafo *g, int n)
{
    g->lista = calloc(n, sizeof(No *));
    g->n = n;
}

void destroi(Grafo *g)
{
    int i;
    for (i = 0; i < g->n; i++)
    {
        No *l = g->lista[i];
        while (l)
        {
            No *r = l;
            l = l->prox;
            free(r);
        }
    }
    free(g->lista);
}

void adiciona_aresta(Grafo *g, int v1, int v2)
{
    No **ap_l = &g->lista[v1];
    while (*ap_l != NULL &&
           (*ap_l)->v < v2)
        ap_l = &(*ap_l)->prox;
    if (*ap_l == NULL || (*ap_l)->v != v2)
    {
        No *n = malloc(sizeof(No));
        n->v = v2;
        n->prox = *ap_l;
        *ap_l = n;
    }
}

int existe_aresta(Grafo *g, int v1, int v2)
{
    No *l = g->lista[v1];
    while (l != NULL && l->v < v2)
        l = l->prox;
    if (l != NULL && l->v == v2)
        return 1;
    return 0;
}

void remove_aresta(Grafo *g, int v1, int v2)
{
    No **ap_l = &g->lista[v1];
    while (*ap_l != NULL &&
           (*ap_l)->v < v2)
        ap_l = &(*ap_l)->prox;
    if (*ap_l != NULL && (*ap_l)->v == v2)
    {
        No *r = *ap_l;
        *ap_l = (*ap_l)->prox;
        free(r);
    }
}

void imprime_grafo(Grafo *g)
{
}

int main()
{
    Grafo g;
    cria_grafo(&g, 6);
    adiciona_aresta(&g, 0, 1);
    adiciona_aresta(&g, 1, 2);
    adiciona_aresta(&g, 3, 1);
    adiciona_aresta(&g, 4, 0);
    adiciona_aresta(&g, 5, 3);
    return 0;
}