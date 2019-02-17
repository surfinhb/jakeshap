// Jake Shapiro
// jtshapir@ucsc.edu
// November 13, 2016
// cs 101: pa4
// GraphTest.c

#include <stdio.h>
#include "List.h"

#define WHITE 0
#define GRAY 128
#define BLACK 256
#define NIL -10
#define INF -8

typedef struct GraphObject* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE *out, Graph G);

//#endif
