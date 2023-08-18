#include "dialog.h"
#include "../base.h"

//изменения веса ребра
int D_ModifyEdge(Graph **graph) {
    char *from, *to;
    int new_weight;
    printf("Enter from (vertex) to modify: --> ");
    from = myReadline();
    if (from == NULL) {
        return 0;
    }
    printf("Enter to (vertex) to modify: --> ");
    to = myReadline();
    if (to == NULL) {
        return 0;
    }
    while (1) {
        printf("Enter weight (from -10 to 10) for edge %s -> %s: ", from, to);
        getInt(&new_weight);
        if (!new_weight) {
            continue;
        }
        if (new_weight > 10 || new_weight < -10) {
            printf("\nWeight must be from -10 to 10\n\n");
        } else {
            break;
        }
    }
    modifyEdgeData(*graph, from, to, new_weight);
    free(from);
    free(to);
    return 1;
}

//изменение в вершине
int D_ModifyVertex(Graph **graph){
    char *name, *new;
    printf("Enter name (vertex) to modify: --> ");
    name = myReadline();
    if (name == NULL) {
        return 0;
    }
    printf("Enter new name (vertex) for %s: --> ", name);
    new = myReadline();
    if (new == NULL) {
        return 0;
    }
    modifyVertexData(*graph, name, new);
    free(name);
    free(new);
}

//удаление вершины
int D_RemoveVertex(Graph **graph){
    char *name;
    printf("Enter name (vertex) to delete: --> ");
    name = myReadline();
    if (name == NULL) {
        return 0;
    }
    removeVertex(*graph, name);
    free(name);
}

//удаление ребра
int D_RemoveEdge(Graph **graph){
    char *from, *to;
    printf("Enter edge to delete from (vertex): --> ");
    from = myReadline();
    if (from == NULL) {
        return 0;
    }
    printf("Enter edge to delete to (vertex): --> ");
    to = myReadline();
    if (to == NULL) {
        return 0;
    }
    removeEdge(*graph, from, to);
    free(from);
    free(to);
}

//добавление вершины
int D_AddVertex(Graph **graph) {
    char *name;
    printf("Enter name (vertex): --> ");
    name = myReadline();
    if (name == NULL) {
        return 0;
    }
    if(addVertex(*graph, name))
        printf("\nVertex %s added\n", name);
    free(name);
    return 1;
}

//добавление ребра
int D_AddEdge(Graph **graph) {
    char *from, *to;
    int weight;
    printf("Enter from (vertex): --> ");
    from = myReadline();
    if (from == NULL) {
        return 0;
    }
    printf("Enter to (vertex): --> ");
    to = myReadline();
    if (to == NULL) {
        return 0;
    }
    while (1) {
        printf("Enter weight (from -10 to 10) for edge %s -> %s: ", from, to);
        getInt(&weight);
        if (!weight) {
            continue;
        }
        if (weight > 10 || weight < -10) {
            printf("\nWeight must be from -10 to 10\n\n");
        } else {
            break;
        }
    }
    if(addEdge(*graph, from, to, weight))
        printf("\nEdge from %s to %s with weight = %d added\n", from, to, weight);
    free(from);
    free(to);
    return 1;
}

int D_ShortestPath(Graph **graph){
    char *from, *to;
    printf("Enter edge from start (vertex): --> ");
    from = myReadline();
    if (from == NULL) {
        return 0;
    }
    printf("Enter edge to end (vertex): --> ");
    to = myReadline();
    if (to == NULL) {
        return 0;
    }
    dijkstraShortestPath(*graph, from, to);
    free(from);
    free(to);
}

//вывод дерева
int D_Show(Graph **graph) {
    graph_print_graphviz(*graph);
    return 1;
}

int D_ShowMatrix(Graph **graph){
    printGraphMatrix(*graph);
    printGraphAdjacencyList(*graph);
}

//BFS
int D_Bfs(Graph **graph){
    char *from;
    printf("Enter start (vertex): --> ");
    from = myReadline();
    if (from == NULL) {
        return 0;
    }
    breadthFirstSearch(*graph, from);
    free(from);
}

//worshall
int D_Worshall(Graph **graph){
    char *from;
    printf("Enter start (vertex): --> ");
    from = myReadline();
    if (from == NULL) {
        return 0;
    }
    worshall(*graph, from);
    free(from);
}