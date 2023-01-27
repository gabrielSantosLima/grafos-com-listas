#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int bool;

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef struct list
{
    int length;
    node *root;
} list;

typedef struct graph
{
    int vertex_size;
    int edges_length;
    list **data;
} graph;

node *create_node(int value)
{
    node *nnode = (node *)malloc(sizeof(node));
    nnode->value = value;
    nnode->next = NULL;
    return nnode;
}

list *create_list()
{
    list *nlist = (list *)malloc(sizeof(list));
    nlist->length = 0;
    nlist->root = NULL;
    return nlist;
}

void insert_node_list(list *nlist, int value)
{
    if (nlist == NULL)
        return;
    if (nlist->root == NULL)
    {
        nlist->root = create_node(value);
        nlist->length++;
        return;
    }
    node *temp_node = nlist->root;
    while (temp_node->next != NULL)
        temp_node = temp_node->next;
    temp_node->next = create_node(value);
    nlist->length++;
}

void print_list(list *nlist)
{
    if (nlist == NULL)
    {
        printf("empty.");
        return;
    }
    node *temp_node = nlist->root;
    while (temp_node != NULL)
    {
        printf("%d ", temp_node->value);
        temp_node = temp_node->next;
    }
}

graph *create_graph(int vertex_size)
{
    graph *ngraph = (graph *)malloc(sizeof(graph));
    ngraph->vertex_size = vertex_size;
    ngraph->edges_length = 0;
    ngraph->data = (list **)malloc(vertex_size * sizeof(list *));
    for (int index = 0; index < vertex_size; index++)
        ngraph->data[index] = NULL;
    return ngraph;
}

bool is_full(graph *ngraph)
{
    return ngraph->edges_length == (ngraph->vertex_size * ngraph->vertex_size);
}

void insert_vertex(graph *ngraph, int vertex)
{
    if (ngraph == NULL || is_full(ngraph))
        return;
    if (ngraph->data[vertex] != NULL)
        return;
    ngraph->data[vertex] = create_list();
}

void insert_edge(graph *ngraph, int vertex1, int vertex2)
{
    if (ngraph == NULL || is_full(ngraph))
        return;
    if (ngraph->data[vertex1] == NULL || ngraph->data[vertex2] == NULL)
        return;
    insert_node_list(ngraph->data[vertex1], vertex2);
    ngraph->edges_length++;
}

void print_graph(graph *ngraph)
{
    if (ngraph == NULL || ngraph->vertex_size <= 0)
    {
        printf("empty graph.");
        return;
    }
    for (int index = 0; index < ngraph->vertex_size; index++)
    {
        printf("%d: ", index);
        print_list(ngraph->data[index]);
        printf("\n");
    }
}

bool includes(list *nlist, int value)
{
    node *nnode = nlist->root;
    while (nnode != NULL)
    {
        if (nnode->value == value)
            return true;
        nnode = nnode->next;
    }
    return false;
}

void print_provinces(list *provinces)
{
    node *temp_node = provinces->root;
    while (temp_node != NULL)
    {
        printf("%d ", temp_node->value);
        temp_node = temp_node->next;
    }
}

// void BFS(graph *ngraph, int ini_vert)
// {
//     fila *f = criarFila();
//     Grafo->visitado[ini_vert] = 1;
//     enfileirar(f, ini_vert);

//     while (!filaVazia(f))
//     {
//         imprimirFila(f);
//         int atual_vert = desenfileirar(f);
//         printf("Visitado %d\n", atual_vert);

//         no_lista *temp = Grafo->lista_adj[atual_vert];

//         while (temp)
//         {
//             int adj_vert = temp->destino;

//             if (Grafo->visitado[adj_vert] == 0)
//             {
//                 Grafo->visitado[adj_vert] = 1;
//                 enfileirar(f, adj_vert);
//             }
//             temp = temp->prox;
//         }
//     }
// }

/*
- A província-irmã não tem que está na lista
- Tem que ter 3 províncias alcançáveis na lista
*/
list *get_provinces(graph *ngraph)
{
    list *provinces = create_list();

    return provinces;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    graph *ngraph = create_graph(2 * n);
    for (int index = 0; index < 2 * n; index++)
        insert_vertex(ngraph, index);
    for (int index = 0; index < 2 * n; index++)
    {
        for (int j = 0; j < 6; j++)
        {
            int i = 0;
            scanf("%d", &i);
            insert_edge(ngraph, index, i - 1);
        }
    }
    print_provinces(get_provinces(ngraph));
    return 0;
}