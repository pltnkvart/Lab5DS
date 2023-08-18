#include "dialog.h"
#include "../base.h"


int main() {
    Graph *graph = calloc(1, sizeof(Graph));
    // Добавление вершин
    addVertex(graph, "1");
    addVertex(graph, "2");
    addVertex(graph, "3");
    addVertex(graph, "4");
    addVertex(graph, "5");
    addVertex(graph, "6");
    // Добавление ребер
    addEdge(graph, "1", "4", 2);
    addEdge(graph, "4", "1", -2);
    addEdge(graph, "1", "5", 5);
    addEdge(graph, "5", "2", 2);
    addEdge(graph, "2", "6", 10);
    addEdge(graph, "6", "5", 3);
    addEdge(graph, "6", "4", 8);
    addEdge(graph, "1", "3", -2);
    addEdge(graph, "6", "3", 2);
    int (*fptr[])(Graph **) = {NULL, D_AddVertex, D_AddEdge, D_RemoveVertex, D_RemoveEdge, D_ModifyVertex, D_ModifyEdge, D_Show, D_ShowMatrix, D_ShortestPath, D_Bfs, D_Worshall};
    const char *msgs[] = {"0. Quit", "1. Add vertex", "2. Add edge", "3. Remove vertex", "4. Remove Edge", "5. Modify Vertex", "6. Modify Edge", "7. Show (graphviz)",
                          "8. Show matrix and adjacency list", "9. Find shortest path", "10. BFS", "11. Worshall"};
    int rc;
    while ((rc = dialog(msgs, 12)))
        if (!fptr[rc](&graph)) {
            break;
        }
    printf("That's all. Bye!\n");
    freeGraph(graph);
    return 0;
}