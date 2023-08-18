#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

//dialog functions
int D_AddVertex(Graph **graph);

int D_AddEdge(Graph **graph);

int D_Show(Graph **graph);

int D_ShowMatrix(Graph **graph);

int D_RemoveVertex(Graph **graph);

int D_RemoveEdge(Graph **graph);

int D_ModifyVertex(Graph **graph);

int D_ModifyEdge(Graph **graph);

int D_ShortestPath(Graph **graph);

int D_Bfs(Graph **graph);

int D_Worshall(Graph **graph);