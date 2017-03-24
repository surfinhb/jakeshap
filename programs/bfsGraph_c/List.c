// Jake Shapiro
// jtshapir@ucsc.edu
// November 13, 2016
// cs 101: pa4
// GraphTest.c

#include <stdlib.h>
#include <stdio.h>
#include "List.h"

// Structs --------------------------------------------------------------------
typedef struct Node {
   node next;
   node last;
   int value;
}
Node;

typedef struct Listobj {
   int size, index;
   node first, end, cursor;
}
Listobj;

node nodeConstructor(int value) {
   node build = malloc(sizeof(Node));
   build->value = value;
   return(build);
}

node nodeSuperConstructor(int value, node last, node next) {
   node construct = malloc(sizeof(Node));
   construct->value = value;
   construct->next = next;
   construct->last = last;
   return(construct);
}

// Constructors-Destructors ---------------------------------------------------

//returns a List which points to a new empty list object 
List newList(void) {
   List list = malloc(sizeof(Listobj));
   list->size = 0;
   list->cursor = NULL;
   list->first = NULL;
   list->end = NULL;
   return(list);
}

// frees all heap memory associated with its List* argument, and sets *pL to NULL
void freeList(List *pL) {

   if(pL == NULL || *pL == NULL) return;
   node freedom = (*pL)->end;

   while (freedom != NULL) {
      node hendrix = freedom;
      freedom = freedom->last;
      free(hendrix);
   }
   free(*pL);
   *pL = NULL;
}


// Access functions -----------------------------------------------------------

// Returns the number of elements in this List.
int length(List L) {
   return L->size;
}

// If cursor is defined return the index of cursor otherwise returns -1.
int index(List L) {
   if (L->cursor == NULL) return -1;
   else                return L->index;
}

// Returns front element. Pre: length() > 0
int front(List L) {
   if(L->size >= 0) { return L->first->value; }
   else             { printf("front() called on an empty List"); exit(1); }
}

// Returns back element. Pre: length() > 0
int back(List L) {
   if(L->size >= 0) { return L->end->value; }
   else             { printf("back() called on an empty List"); exit(1); }
}

// Returns cursor element. Pre: length()>0, index()>=0
int get(List L) {
   if(L->index >= 0 && L->size > 0) { return L->cursor->value; }
   else                             { printf("get() illegal call"); exit(1); }
}

// Returns true if this List and L are the same integer sequence
int equals(List A, List B) {

   node list1 = A->first;
   node list2 = B->first;

   if (A->size != B->size) {
      return 1;
   } else {
      int compare = 1;
      while (compare == 1) {
         if (list1->value != list2->value) compare = 0;
         list1 = list1->next;
         list2 = list2->next;
         if (list1 == NULL) break;
      }
      return compare;
   }
}

// Manipulation procedures ----------------------------------------------------

// Resets this List to its original empty state.
void clear(List L) {
   L->size = 0;
   L->index = -1;
   L->cursor = NULL;
   L->first = NULL;
   L->end = NULL;
}

// places the cursor under the front element
void moveFront(List L) {
   if(L->size >= 1) {
      L->cursor = L->first;
      L->index = 0;
   }
}

// places the cursor under the end element
void moveBack(List L) {
   if(L->size >= 1) {
      L->cursor = L->end;
      L->index = L->size-1;   
   }
}

// moves cursor one step toward front of this List
void movePrev(List L) {
   if(L->cursor != NULL) {
      if (L->cursor == L->first) {
         L->cursor = NULL;
      } else {
         L->cursor = L->cursor->last; 
      }
   }
}

// moves cursor one step toward end of the list
void moveNext(List L) {
   if(L->cursor != NULL) {
      if (L->cursor == L->end) {
	 L->cursor = NULL;
      } else {
	 L->cursor = L->cursor->next;
      }
   }
}

// Insert new element into List. If List non-empty, takes place before front
void prepend(List L, int data) {
   node prep = nodeSuperConstructor(data, NULL, L->first);
   if(L->size >= 1) L->first->last = prep;
   else             L->end = prep;
   L->first = prep;
   L->size++;
}

// Insert new element into List. If List non-empty, takes place after end
void append(List L, int data) {
   node app = nodeSuperConstructor(data, L->end, NULL);
   if(L->size >= 1) L->end->next = app;
   else             L->first = app;
   L->end = app;
   L->size++;
}

// Insert new element before cursor. Pre: length() > 0, index() >= 0
void insertBefore(List L, int data) {
   // exception handling
   if(L->size <= 0 || L->index < 0) printf("insertBefore() illegal call");
   // new node
   node insert = nodeConstructor(data);
   // insertion
   insert->next = L->cursor;
   if(L->cursor->last != NULL){
      insert->last = L->cursor->last;
      L->cursor->last->next = insert;
   }
   L->cursor->last = insert;
   if (insert->last == NULL) L->first = insert;
   // incremention 
   L->index++;
   L->size++;
}

// Inserts new element after cursor. Pre: length() > 0, index() >= 0
void insertAfter(List L, int data) {
   // exception handling
   if(L->size <= 0 || L->index < 0) printf("insertBefore() illegal call");
   // new node
   node insert = nodeSuperConstructor(data, L->cursor, L->cursor->next);
   // insertion
   if (L->cursor->next == NULL) L->end = insert;
   else                     (L->cursor->next)->last = insert;
   L->cursor->next = insert;
   // incremention
   L->size++;
}

// Deletes the front element. Pre: length() > 0
void deleteFront(List L) {
   // exception handling
   if(L->size <= 0) printf("deleteFront() called on empty List");
   // deletion
   if (L->index >= 1) {
      L->first = L->first->next;
      L->first->last = NULL;
      L->size--;
   } else {
      L->cursor = NULL;
   }
}

// Deletes the end element. Pre: length() > 0
void deleteBack(List L) {
   // exception handling
   if(L->size == 0) printf("deleteBack() called on empty List");
   // deletion
   if (L->size == 1) {
      L->end = NULL;
   } else {
      L->end = L->end->last;
      L->end->next = NULL;
   }
   L->size--;
}

// Deletes cursor element, making cursor undefined. Pre: length() > 0, index() >= 0
void delete(List L) {
   // exception handling
   if(L->size <= 0 || L->index < 0) printf("insertBefore() illegal call");
   // deletion
   (L->cursor->next)->last = L->cursor->last;
   (L->cursor->last)->next = L->cursor->next;
   L->cursor = NULL;
   L->size--;
   L->index = -1;
}

// Other operations -----------------------------------------------------------

// prints L to the file pointed to by out as a space-separated string
void printList(FILE *out, List L) {
   node print = NULL;
   for (print = L->first; print != NULL; print=print->next) {
      fprintf(out, "%d ", print->value);
   }
}
   
// Returns a new List representing the same integer sequence as this List
List copyList(List L) {
   // new node duplicate 
   node duplicate = NULL;
   // new list L2 where data copied to;
   List L2 = newList();
   // loop through L
   for (duplicate = L->end; duplicate != NULL; duplicate = duplicate->last) {
      // add each element of L to L2
      prepend (L2, duplicate->value);
   }
   // return the newly created L2
   return L2;
}


      

