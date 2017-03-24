// Jake Shapiro
// jtshapir@ucsc.edu
// November 13, 2016
// cs 101: pa4
// Graph.c

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


struct GraphObject {
   // single ints
   int order; // fields storing the number of vertices
   int size; // the number of edges
   int origin; // label of the vertex that was most recently used as source for BFS    
   // arrays of pointers to ints
   int *color; // array of ints: ith element is the color (white, gray, black) of vertex i.
   int *parent; // array of ints: ith element is the parent of vertex i
   int *space; // array of ints: ith element = distance from (most recent) source to vertex i
   // array of pointers to List Objects
   List *neighbor; // array of Lists: ith element contains the neighbors of vertex i   
} GraphObject;

typedef struct GraphObject *Graph;

/*********************** Constructors-Destructors ***********************/

// returns graph pointing to new Graph with n vertices and no edges
Graph newGraph(int n) {
   // create new Graph
   Graph newG = malloc(sizeof(GraphObject));
   // intitialize ints
   newG->order = n; // n vertices
   newG->size  = 0; // 0 edges
   // initialize arrays
   newG->color    = calloc(n+1, sizeof(int));
   newG->parent   = calloc(n+1, sizeof(int));
   newG->space    = calloc(n+1, sizeof(int));
   // create array of lists for every vertice
   int vertice = 0;
   newG->neighbor = calloc(n+1, sizeof(List));
   while (vertice!=n+1) {
      newG->neighbor[vertice]=newList();
      vertice++;
   }   
   return newG;
}

// frees memory from Graph *pG, sets handle *pG to NULL
void freeGraph(Graph *pG) {
   int vertice = 0;
   List fG = newList();
   while (vertice <= (*pG)->order) {
      (*pG)->neighbor[vertice] = fG;
      freeList(&fG);
      vertice++;
   }
   *pG = NULL;
}

/*********************** Access functions ***********************/

// return order of graph
int getOrder(Graph G) {
   return G->order;
}

//return size of graph
int getSize(Graph G) {
   return G->size;
}

// returns source vertex most recently used BFS()
// NIL if BFS() has never been called
int getSource(Graph G) {
   return G->origin;
}

// returns parent of vertex u in the BreadthFirst tree created by BFS()
// NIL if BFS() has not yet been called
// precondition: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
   // check precondition
   if (!(1 <= u) && !(u <= G->order)) {
      printf("getParent() illegal call");
      exit(1);
   }   
   return G->parent[u];
}

// returns distance from most recent BFS source to vertex u
// INF if BFS() has not yet been called
// precondition: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
   // check precondition
   if (!(1 <= u) && !(u <= G->order)) {
      printf("getDist() illegal call");
      exit(1);
   }
   return G->space[u];
}

// appends to List L vertices of shortest path in G from source to u
// if no path exists appends to L the value NIL
// precondition: getSource(G)!=NIL (i.e BFS called before getPath)
// precondition: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
   // check precondition 1
   if (G->origin == NIL) {
      printf("getPath() illegal call 1");
      exit(1);
   }
   // check precondition 2
   if (!(1 <= u) && !(u <= G->order)) {
      printf("getPath() illegal call 2");
      exit(1);
   }
   // appends to List L vertices of shortest path in G from source to u
   if (getSource(G) != u) {
      if (getParent(G, u) != -10) {
         prepend(L, u);
         getPath(L, G, getParent(G, u));
      // if no path exists appends to L the value NIL
      } else {
         append(L, -10);
      }
   } else {
      prepend(L, u);
   }
}

/*********************** Manipulation procedures ***********************/

//* deletes all edges of G
void makeNull(Graph G) {
   int c = 0;
   while (c <= getOrder(G)) {
      List cuL = G->neighbor[c];
      while (index(cuL)!=-1) {
         moveNext(cuL);
      }
      clear(cuL);
      c++;
   }
}        

// inserts a new edge joining u to v
// i.e. u is added to the adjacency List of v, and v to the adjacency List of u
// Need to maintain lists in sorted order by increasing labels.
void addEdge(Graph G, int u, int v) {
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}   

// inserts a new directed edge from u to v
// i.e. v is added to the adjacency List of u 
void addArc(Graph G, int u, int v) {
   G->size++;
   // loop through queue
   for (moveBack(G->neighbor[u]); index(G->neighbor[u]) != -1; 
        movePrev(G->neighbor[u])) {
      // checking how v relates to cursor
      int key = get(G->neighbor[u]);
      // if they are equal insert after cursor
      if (v == key) {
         insertBefore(G->neighbor[u], v);
         return;
      }
      // if < current index insert after cursor
      if (v > key) {
         insertAfter(G->neighbor[u], v);
         return;
      }
   }
   // if iterated out of list insert at beginning
   prepend(G->neighbor[u], v);
}

// run BFS on the G with source s
// set color, distance, parent, and source
void BFS(Graph G, int s) {
   // initialize variables
   G->origin = s;
   // intitializing arrays
   int initialize = 0;
   while (initialize <= getOrder(G)) {
      // if source is same as current iteration fill grey
      if (getSource(G) == initialize) {
         G->color[initialize] = 126;
         G->space[initialize] = 0;
      } else {
         G->color[initialize] = 0;
         G->space[initialize] = -8;
      }
      G->parent[initialize] = -10;
      initialize++;
   }

   // make a new list of lists
   List graphList = newList();
   // until list is empty
   for (prepend(graphList,s); length(graphList) != 0; deleteBack(graphList)){
      // specific list inside graphList
      List cuL = G->neighbor[back(graphList)];
      // loop through that list
      for (moveFront(cuL); index(cuL) != -1;) {
         int color = G->color[get(cuL)];
         // Black: has been to
         if(color == 256) {
            moveNext(cuL);
         } else {
            // Grey: has been to
            if (color == 128) {
               moveNext(cuL);
            } else {
               // White: has not been to i.e match
               if (color == 0) {
                  G->color[get(cuL)] += 128;
                  G->parent[get(cuL)] = back(graphList);
                  G->space[get(cuL)] = getDist(G, back(graphList)) + 1;
                  prepend(graphList, get(cuL));
               } else {
                  moveNext(cuL);
               }
            }
         }
      }
   }
}

/********************** Other operations **********************/

void printGraph(FILE *out, Graph G) {
   int listIndex = 1;
   while (listIndex != G->order+1) {
      fprintf(out, "%d: ", listIndex);
      List cuL = G->neighbor[listIndex];
      moveFront(cuL);
      if (index(cuL) != -1) {
         printList(out, cuL);
      }
      fprintf(out, "\n");
      listIndex++;
   }
}
