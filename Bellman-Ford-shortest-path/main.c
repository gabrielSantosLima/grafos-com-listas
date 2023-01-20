#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct edge
{

    size_t end_vertex;
    int weight;

    struct edge *next;

} Edge;

typedef struct graph
{

    // e points to the adjacency list representation of the graph.
    Edge **e;

    // n is the number of vertices.
    size_t n;

    // s is the source vertex.
    size_t s;

    // dist stores the shortest distance estimates from s to the other vertices.
    int *dist;

    // pre stores the shortest path predecessors of the vertices.
    size_t *pre;

} Graph;

void take_input_from_user_and_create_graph(Graph *);
bool bellman_ford(Graph *);
void print_shortest_paths(Graph *);
void print_shortest_path_from_s_to_t(Graph *, size_t);
void free_graph(Graph *);

int main(void)
{

    Graph g;
    take_input_from_user_and_create_graph(&g);

    if (bellman_ford(&g))
        print_shortest_paths(&g);
    else
        printf("\nError: Negative-weight cycle reachable from source exists\n");

    free_graph(&g);

    return 0;
}

void take_input_from_user_and_create_graph(Graph *ptr_g)
{

    printf("Enter the number of vertices: ");
    scanf("%zu", &((ptr_g)->n));

    printf("Enter the source vertex (vertex numbering begins from 0): ");
    scanf("%zu", &((ptr_g)->s));

    (ptr_g)->e = calloc((ptr_g)->n, sizeof(Edge *));
    if ((ptr_g)->e == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    (ptr_g)->dist = malloc(((ptr_g)->n) * sizeof(int));
    if ((ptr_g)->dist == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    (ptr_g)->pre = malloc(((ptr_g)->n) * sizeof(size_t));
    if ((ptr_g)->pre == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    printf("\nEnter edges (q to quit) :-\n");
    printf("(0 2 5 means an edge from vertex 0 to vertex 2 of weight 5)\n\n");

    while (true)
    {
        size_t start_vertex, end_vertex;
        int weight;

        printf(">>> ");
        if (scanf("%zu %zu %d", &(start_vertex), &(end_vertex), &(weight)) != 3)
            break;

        Edge *ptr_current_edge = malloc(sizeof(Edge));
        if (ptr_current_edge == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        (ptr_current_edge)->end_vertex = end_vertex;
        (ptr_current_edge)->weight = weight;

        (ptr_current_edge)->next = ((ptr_g)->e)[start_vertex];
        ((ptr_g)->e)[start_vertex] = ptr_current_edge;
    }
}

bool bellman_ford(Graph *ptr_g)
{

    for (size_t t = 0; t < ((ptr_g)->n); t++)
        ((ptr_g)->dist)[t] = INT_MAX;
    ((ptr_g)->dist)[(ptr_g)->s] = 0;

    for (size_t i = 0; i < (((ptr_g)->n) - 1); i++)
    {
        for (size_t u = 0; u < ((ptr_g)->n); u++)
        {
            Edge *ptr_current_edge = ((ptr_g)->e)[u];

            while (ptr_current_edge)
            {
                size_t v = ((ptr_current_edge)->end_vertex);
                int weight = ((ptr_current_edge)->weight);

                if ((((ptr_g)->dist)[u] != INT_MAX) &&
                    (((ptr_g)->dist)[v] > (((ptr_g)->dist)[u] + weight)))
                {
                    ((ptr_g)->dist)[v] = (((ptr_g)->dist)[u] + weight);
                    ((ptr_g)->pre)[v] = u;
                }

                ptr_current_edge = ((ptr_current_edge)->next);
            }
        }
    }

    for (size_t u = 0; u < ((ptr_g)->n); u++)
    {
        Edge *ptr_current_edge = ((ptr_g)->e)[u];

        while (ptr_current_edge)
        {
            size_t v = ((ptr_current_edge)->end_vertex);
            int weight = ((ptr_current_edge)->weight);

            if ((((ptr_g)->dist)[u] != INT_MAX) &&
                (((ptr_g)->dist)[v] > (((ptr_g)->dist)[u] + weight)))
            {
                return false;
            }

            ptr_current_edge = ((ptr_current_edge)->next);
        }
    }

    return true;
}

void print_shortest_paths(Graph *ptr_g)
{

    printf("\nShortest paths :-\n");

    for (size_t t = 0; t < ((ptr_g)->n); t++)
    {
        if (((ptr_g)->dist)[t] != INT_MAX)
        {
            printf("%zu to %zu (shortest distance = %3d): ", (ptr_g)->s, t,
                   ((ptr_g)->dist)[t]);
            print_shortest_path_from_s_to_t(ptr_g, t);
            putchar('\n');
        }

        else
        {
            printf("%zu to %zu (shortest distance = N/A): N/A\n", (ptr_g)->s, t);
        }
    }
}

void print_shortest_path_from_s_to_t(Graph *ptr_g, size_t t)
{

    if ((ptr_g)->s != t)
        print_shortest_path_from_s_to_t(ptr_g, ((ptr_g)->pre)[t]);

    printf("%zu ", t);
}

void free_graph(Graph *ptr_g)
{

    for (size_t i = 0; i < ((ptr_g)->n); i++)
    {
        Edge *ptr_current_edge = ((ptr_g)->e)[i];

        while (ptr_current_edge)
        {
            Edge *temp = (ptr_current_edge)->next;
            free(ptr_current_edge);
            ptr_current_edge = temp;
        }
    }

    free((ptr_g)->e);

    free((ptr_g)->dist);
    free((ptr_g)->pre);
}