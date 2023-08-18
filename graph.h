#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Edge{
    char *from;    //вершина из который выходит ребро
    char *to;      //вершина в которую входит
    int weight;
} Edge;

typedef struct Vertex{
    int edge_count; //количество исходящих ребер
    char *name;
    Edge *edges;    //вектор исходящих ребер
} Vertex;

typedef struct Graph{
    int vertex_count; //количество вершин
    Vertex *vertices; //вектор вершин
} Graph;


int addVertex(Graph* graph, char* name);

int addEdge(Graph* graph, char* from, char* to, int weight);

void removeVertex(Graph* graph, char* name);

void removeEdge(Graph* graph, char* from, char* to);

void modifyVertexData(Graph* graph, char* name, char* new_name);

void modifyEdgeData(Graph* graph, char* from, char* to, int new_weight);

void printGraphMatrix(const Graph* graph);

void printGraphAdjacencyList(const Graph* graph);

void dijkstraShortestPath(const Graph* graph, char* start_vertex, char* end_vertex);

void breadthFirstSearch(const Graph* graph, char* start_vertex);

void freeGraph(Graph* graph);

void graph_print_dot(Graph* graph, FILE *stream);

void graph_print_graphviz(Graph *graph);

int findVertexIndex(const Graph* graph, const char* vertex_name);

void worshall(Graph* graph, const char* person);

void printMatrix(int size, int matrix[][size], Graph *graph);