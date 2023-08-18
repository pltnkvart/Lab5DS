#include "graph.h"
#include "limits.h"

//добавление вершины
int addVertex(Graph* graph, char* name) {
    int vertex_count = graph->vertex_count;
    graph->vertices = (Vertex*)realloc(graph->vertices, (vertex_count + 1) * sizeof(Vertex));
    graph->vertices[vertex_count].edge_count = 0;
    graph->vertices[vertex_count].name = strdup(name);
    graph->vertices[vertex_count].edges = NULL;
    graph->vertex_count++;
    return 1;
}

//добавление ребра
int addEdge(Graph* graph, char* from, char* to, int weight) {
    int vertex_count = graph->vertex_count;
    int from_index = -1, to_index = -1;

    for (int i = 0; i < vertex_count; i++) {
        if (strcmp(graph->vertices[i].name, from) == 0) {
            from_index = i;
        }
        if (strcmp(graph->vertices[i].name, to) == 0) {
            to_index = i;
        }
    }

    if (from_index == -1 || to_index == -1) {
        printf("Error: Vertex not found.\n");
        return 0;
    }
    Vertex* vertex = &(graph->vertices[from_index]);
    vertex->edge_count++;
    vertex->edges = (Edge*)realloc(vertex->edges, vertex->edge_count * sizeof(Edge));

    Edge* edge = &(vertex->edges[vertex->edge_count - 1]);
    edge->from = strdup(from);
    edge->to = strdup(to);
    edge->weight = weight;
    return 1;
}

//удаление вершины
void removeVertex(Graph* graph, char* name) {
    int vertex_count = graph->vertex_count;
    int index = -1;

    for (int i = 0; i < vertex_count; i++) {
        if (strcmp(graph->vertices[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Vertex not found.\n");
        return;
    }

    Vertex* vertex = &(graph->vertices[index]);
    for (int i = 0; i < vertex->edge_count; i++) {
        free(vertex->edges[i].from);
        free(vertex->edges[i].to);
    }
    free(vertex->name);
    free(vertex->edges);

    for (int i = index; i < vertex_count - 1; i++) {
        graph->vertices[i] = graph->vertices[i + 1];
    }

    graph->vertex_count--;
    graph->vertices = (Vertex*)realloc(graph->vertices, graph->vertex_count * sizeof(Vertex));
}

//удаление ребра
void removeEdge(Graph* graph, char* from, char* to) {
    int vertex_count = graph->vertex_count;
    int from_index = -1, to_index = -1;

    for (int i = 0; i < vertex_count; i++) {
        if (strcmp(graph->vertices[i].name, from) == 0) {
            from_index = i;
        }
        if (strcmp(graph->vertices[i].name, to) == 0) {
            to_index = i;
        }
    }

    if (from_index == -1 || to_index == -1) {
        printf("Error: Vertex not found.\n");
        return;
    }

    Vertex* vertex = &(graph->vertices[from_index]);
    int edge_count = vertex->edge_count;
    int index = -1;

    for (int i = 0; i < edge_count; i++) {
        if (strcmp(vertex->edges[i].to, to) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Edge not found.\n");
        return;
    }

    free(vertex->edges[index].from);
    free(vertex->edges[index].to);

    for (int i = index; i < edge_count - 1; i++) {
        vertex->edges[i] = vertex->edges[i + 1];
    }

    vertex->edge_count--;
    vertex->edges = (Edge*)realloc(vertex->edges, vertex->edge_count * sizeof(Edge));
}

//изменить вершину
void modifyVertexData(Graph* graph, char* name, char* new_name) {
    int vertex_count = graph->vertex_count;
    int index = -1;

    for (int i = 0; i < vertex_count; i++) {
        if (strcmp(graph->vertices[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Vertex not found.\n");
        return;
    }

    free(graph->vertices[index].name);
    graph->vertices[index].name = strdup(new_name);
}

//изменить ребро
void modifyEdgeData(Graph* graph, char* from, char* to, int new_weight) {
    int vertex_count = graph->vertex_count;
    int from_index = -1, to_index = -1;

    for (int i = 0; i < vertex_count; i++) {
        if (strcmp(graph->vertices[i].name, from) == 0) {
            from_index = i;
        }
        if (strcmp(graph->vertices[i].name, to) == 0) {
            to_index = i;
        }
    }

    if (from_index == -1 || to_index == -1) {
        printf("Error: Vertex not found.\n");
        return;
    }

    Vertex* vertex = &(graph->vertices[from_index]);
    int edge_count = vertex->edge_count;
    int index = -1;

    for (int i = 0; i < edge_count; i++) {
        if (strcmp(vertex->edges[i].to, to) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Edge not found.\n");
        return;
    }

    vertex->edges[index].weight = new_weight;
}

//Дейкстра
void dijkstraShortestPath(const Graph* graph, char* start_vertex, char* end_vertex) {
    int vertex_count = graph->vertex_count;
    int* distances = malloc(vertex_count * sizeof(int));
    int* visited = malloc(vertex_count * sizeof(int));
    char** path = malloc(vertex_count * sizeof(char*));
    int start_index = -1;
    int end_index = -1;

    for (int i = 0; i < vertex_count; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
        path[i] = NULL;
        if (strcmp(graph->vertices[i].name, start_vertex) == 0) {
            distances[i] = 0;
            start_index = i;
        }
        if (strcmp(graph->vertices[i].name, end_vertex) == 0) {
            end_index = i;
        }
    }

    if (start_index == -1 || end_index == -1) {
        printf("Error: Start or end vertex not found.\n");
        free(distances);
        free(visited);
        free(path);
        return;
    }

    for (int i = 0; i < vertex_count - 1; i++) {
        int min_distance = INT_MAX;
        int min_index = -1;

        // Находим вершину с минимальным расстоянием
        for (int j = 0; j < vertex_count; j++) {
            if (visited[j] == 0 && distances[j] < min_distance) {
                min_distance = distances[j];
                min_index = j;
            }
        }
        if(min_index == -1)
            break;

        visited[min_index] = 1;

        // Обновляем расстояния до смежных вершин
        for (int j = 0; j < graph->vertices[min_index].edge_count; j++) {
            Edge edge = graph->vertices[min_index].edges[j];
            int neighbor_index = -1;
            for (int k = 0; k < vertex_count; k++) {
                if (strcmp(graph->vertices[k].name, edge.to) == 0) {
                    neighbor_index = k;
                    break;
                }
            }
            if (neighbor_index != -1 && edge.weight > 0) {
                int new_distance = distances[min_index] + edge.weight;
                if (new_distance < distances[neighbor_index]) {
                    distances[neighbor_index] = new_distance;
                    path[neighbor_index] = graph->vertices[min_index].name;
                }
            }
        }
    }

    if (distances[end_index] == INT_MAX) {
        printf("No path exists between %s and %s\n", start_vertex, end_vertex);
    } else {
        printf("Shortest path length from %s to %s: %d\n", start_vertex, end_vertex, distances[end_index]);

        printf("Shortest path: ");
        int index = end_index;
        while (index != -1) {
            printf("%s ", graph->vertices[index].name);
            char* previous_vertex = path[index];
            index = -1;
            for (int i = 0; i < vertex_count; i++) {
                if (previous_vertex != NULL && strcmp(graph->vertices[i].name, previous_vertex) == 0) {
                    index = i;
                    break;
                }
            }
        }
        printf("\n");
    }

    free(distances);
    free(visited);
    free(path);
}

//BFS
void breadthFirstSearch(const Graph* graph, char* start_vertex) {
    int vertex_count = graph->vertex_count;
    int* visited = (int*)malloc(vertex_count * sizeof(int));
    for (int i = 0; i < vertex_count; i++) {
        visited[i] = 0;
    }

    int start_index = -1;
    for (int i = 0; i < vertex_count; i++) {
        if (strcmp(graph->vertices[i].name, start_vertex) == 0) {
            start_index = i;
            break;
        }
    }

    if (start_index == -1) {
        printf("Error: Start vertex not found.\n");
        free(visited);
        return;
    }

    printf("BFS traversal starting from %s: ", start_vertex);

    int queue_capacity = vertex_count;
    char** queue = (char**)malloc(queue_capacity * sizeof(char*));
    int front = 0, rear = 0;

    queue[rear] = strdup(start_vertex);
    rear = (rear + 1) % queue_capacity;
    visited[start_index] = 1;

    while (front != rear) {
        char* vertex_name = queue[front];
        printf("%s ", vertex_name);
        front = (front + 1) % queue_capacity;

        int vertex_index = -1;
        for (int i = 0; i < vertex_count; i++) {
            if (strcmp(graph->vertices[i].name, vertex_name) == 0) {
                vertex_index = i;
                break;
            }
        }

        Vertex vertex = graph->vertices[vertex_index];
        int edge_count = vertex.edge_count;

        for (int i = 0; i < edge_count; i++) {
            Edge edge = vertex.edges[i];

            if (edge.weight > 0) {
                char* adjacent_vertex_name = edge.to;
                int adjacent_vertex_index = -1;

                for (int j = 0; j < vertex_count; j++) {
                    if (strcmp(graph->vertices[j].name, adjacent_vertex_name) == 0) {
                        adjacent_vertex_index = j;
                        break;
                    }
                }

                if (adjacent_vertex_index != -1 && visited[adjacent_vertex_index] == 0) {
                    queue[rear] = strdup(adjacent_vertex_name);
                    rear = (rear + 1) % queue_capacity;
                    visited[adjacent_vertex_index] = 1;
                }
            }
        }
        free(vertex_name);
    }

    printf("\n");
    free(visited);
    free(queue);
}



//матрица смежности
void printGraphMatrix(const Graph* graph) {
    int vertex_count = graph->vertex_count;

    printf("\nGraph Matrix:\n");
    for(int i = 0; i < vertex_count; i++){
        printf("\t%s", graph->vertices[i].name);
    }
    printf("\n");
    for (int i = 0; i < vertex_count; i++) {
        printf("%s\t", graph->vertices[i].name);

        for (int j = 0; j < vertex_count; j++) {
            int edge_count = graph->vertices[i].edge_count;
            int edge_weight = 0;
            for (int k = 0; k < edge_count; k++) {
                if (strcmp(graph->vertices[i].edges[k].to, graph->vertices[j].name) == 0) {
                    edge_weight = graph->vertices[i].edges[k].weight;
                    break;
                }
            }
            printf("%d\t", edge_weight);
        }
        printf("\n");
    }
}

//список смежности
void printGraphAdjacencyList(const Graph* graph) {
    int vertex_count = graph->vertex_count;

    printf("\nGraph Adjacency List:\n");
    for (int i = 0; i < vertex_count; i++) {
        printf("%s: ", graph->vertices[i].name);

        int edge_count = graph->vertices[i].edge_count;
        for (int j = 0; j < edge_count; j++) {
            printf("(%s, %d) ", graph->vertices[i].edges[j].to, graph->vertices[i].edges[j].weight);
        }

        printf("\n");
    }
}

void printMatrix(int size, int matrix[][size], Graph *graph) {
    printf("Distance matrix:\n");
    for(int i = 0; i < graph->vertex_count; i++){
        printf("%s\t", graph->vertices[i].name);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == -1) {
                printf("%d\t", matrix[i][j]);
            } else {
                printf("%d\t", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    return;
}

//WORSHALL
void worshall(Graph *graph, const char *person) {
    int size = graph->vertex_count;
    int distances[size][size];

    // Инициализация матрицы расстояний и пути
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                distances[i][j] = 0;
            } else {
                distances[i][j] = 100000;
            }
        }
    }
    // Заполнение матрицы расстояний
    for (int i = 0; i < graph->vertex_count; i++) {
        for (int j = 0; j < graph->vertices[i].edge_count; j++) {
            int from_index = -1;
            int to_index = -1;

            for (int k = 0; k < graph->vertex_count; k++) {
                if (strcmp(graph->vertices[k].name, graph->vertices[i].edges[j].from) == 0) {
                    from_index = k;
                }
                if (strcmp(graph->vertices[k].name, graph->vertices[i].edges[j].to) == 0) {
                    to_index = k;
                }
            }

            if (from_index != -1 && to_index != -1) {
                distances[from_index][to_index] = graph->vertices[i].edges[j].weight;
            }
        }
    }
    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (distances[i][k] + distances[k][j] < distances[i][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                }
            }
        }
    }
    printf("\nafter\n");
    printMatrix(size, distances, graph);
    int person_index = -1;
    for (int i = 0; i < graph->vertex_count; i++) {
        if (strcmp(graph->vertices[i].name, person) == 0) {
            person_index = i;
            break;
        }
    }

    if (person_index == -1) {
        printf("Person '%s' not found in the graph.\n", person);
        return;
    }

    int max_weight_sum = 0;
    int max_weight_index = -1;

    for (int i = 0; i < size; i++) {
        if (distances[person_index][i] != -1 && distances[person_index][i] > max_weight_sum) {
            max_weight_sum = distances[person_index][i];
            max_weight_index = i;
        }
    }
    if (max_weight_index == -1) {
        printf("No potential acquaintance found for person '%s'.\n", person);
        return;
    }

    printf("The most acquainted person for '%s' is '%s'\n", person, graph->vertices[max_weight_index].name);
    return;
}


//free memory
void freeGraph(Graph* graph) {
    int vertex_count = graph->vertex_count;
    for (int i = 0; i < vertex_count; i++) {
        int edge_count = graph->vertices[i].edge_count;
        for (int j = 0; j < edge_count; j++) {
            free(graph->vertices[i].edges[j].from);
            free(graph->vertices[i].edges[j].to);
        }
        free(graph->vertices[i].name);
        free(graph->vertices[i].edges);
    }
    free(graph->vertices);
    free(graph);
}

//output
void graph_print_dot(Graph* graph, FILE *stream) {
    int vertex_count = graph->vertex_count;
    for (int i = 0; i < vertex_count; i++) {
        Vertex vertex = graph->vertices[i];
        char* vertex_name = vertex.name;

        int edge_count = vertex.edge_count;
        for (int j = 0; j < edge_count; j++) {
            Edge edge = vertex.edges[j];
            char* to_vertex_name = edge.to;
            int weight = edge.weight;
            fprintf(stream, "\t\"%s\" -> \"%s\" [label=\"%d\"];\n", vertex_name, to_vertex_name, weight);
        }
    }
}

void graph_print_graphviz(Graph *graph) {
    FILE *stream = fopen("graph.dot", "w+");
    if (stream == NULL) {
        printf("Error: cannot open file.\n");
        return;
    }
    fprintf(stream, "digraph {\n rankdir=RL;\n layout=\"sfdp\"\nbeautify=true\n ");
    graph_print_dot(graph, stream);
    fprintf(stream, "}\n");
    fclose(stream);
    system("dot -Tpng graph.dot -o graph.png -s[10]");
    system("catimg graph.png");
}