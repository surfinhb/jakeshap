// Jake Shapiro
// jtshapir@ucsc.edu
// November 13, 2016
// cs 101: pa4
// FindPath.c

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(int argc, char * argv[]){
   // Check if correct arguments are passed
   if(argc < 3 || argc > 3) {
      printf("Use-> FindPath infile outfile");
      exit(1);
   }

   // IO
   FILE *scan1 = fopen(argv[1], "r");
   FILE *scan2 = fopen(argv[1], "r");
   FILE *output = fopen(argv[2], "w");

   // other variables
   int order;
   int boolean = 1;
   char read[4096];
   char read2[4096];
   int col1, col2 = NULL;

   // get order of Graph
   for (int count = 0; count < argc; count++) {
      if (count == 0) {
	 fgets(read, 4096, scan1);
	 sscanf(read, "%d", &order);
      } else {
	 break;
      }
   }
   // make new graph using order
   Graph G = newGraph(order);   
   
   // read in columns and print out graph
   while (boolean) {
      for (;fgets(read, 4096, scan1) != NULL && boolean; addEdge(G, col1, col2)) {
         sscanf(read, "%d %d", &col1, &col2);
         if (col1 != 0) {
	    boolean = 1;
	 } else {
	    if (col2 != 0) {
	       boolean = 1;
	    } else {
	       break;
	    }
	 }
      }
      boolean = 0;
   }
   printGraph(output, G);
   
      
   while( fgets(read, 4096, scan1) != NULL)  {
      fprintf(output, " \n \n");
      sscanf(read, "%d %d", &col1, &col2);
      if (col1 != 0) {
	 boolean = 1;
      } else {
	 if (col2 != 0) {
	    boolean = 1;
	 } else {
	    break;
	 }
      }
      fgets(read2, 4096, scan2);
      // calling BFS
      BFS(G, col1);
      List path = newList();
      getPath(path, G, col2);

      if(getDist(G, col2) != -8) { 
         fprintf(output, "The distance from %d to %d is %d\n", col1, col2, getDist(G, col2));
         fprintf(output, "A shortest %d-%d path is: ", col1, col2);
         printList(output, path);
      } else {
         fprintf(output, "The distance from %d to %d is infinity\n"
                 "No %d-%d path exists", col1, col2, col1, col2);      
      }
   }
   // finishing touches
   fprintf(output, "\n");
   freeGraph(&G);   
   fclose(output);
}
