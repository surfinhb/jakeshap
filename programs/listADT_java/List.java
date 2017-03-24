// Jake Shapiro
// jtshapir@ucsc.edu
// October 3, 2016
// CS 101: PA1
// List.java

public class List {
   private class node {
      node next;
      node last;
      int value;

      // default node constructor
      node(int value) { this.value = value; }
      
      // specialized node constructor
      node (int value, node last, node next) {this.next = next; this.last = last; this.value = value;}

      // get string of value
      public String toString() {
         return String.valueOf(value);
      }
   }
   
   // variable declaration
   private int size, index;
   private node first, end, cursor;
   
   // Creates a new empty List.
   List() {
      size = 0;
      index = -1;  // let -1 be undefined
      cursor = null;
      first = null;
      end = null;
   }

   // Returns the number of elements in this List.
   int length() {
      return size;
   }

   // If cursor is defined return the index of cursor otherwise returns -1.
   int index() {
      if (cursor == null) return -1;
      return index;
   }

   // Returns front element. Pre: length() > 0
   int front() {
      if(size >= 0) return first.value;
      else throw new RuntimeException("front() called on an empty List");
   }

   // Returns back element. Pre: length() > 0
   int back() {
      if(size >= 0) return end.value;
      else throw new RuntimeException("back() called on an empty List");
   }

   // Returns cursor element. Pre: length()>0, index()>=0
   int get() {
      if(index >= 0 && size > 0) return cursor.value;
      else throw new RuntimeException("get() illegal call");
   }

   // Returns true if this List and L are the same integer sequence
   boolean equals(List L){
      node list1 = this.first;
      node list2 = L.first;

      if (this.size != L.size) {
         return false;
      } else {
         boolean compare = true;
         while (compare) {
            compare = (list1.value==list2.value);
            list1 = list1.next;
            list2 = list2.next;
            if (list1 == null) break;
         }
         return compare;
      }
   }


   // Resets this List to its original empty state.
   void clear() {
      size = 0;
      index = -1;
      cursor = null;
      first = null;
      end = null;
   }
   
   // places the cursor under the front element
   void moveFront() {
      if(size >= 1) {
         cursor = first;
         index = 0;
      } 
   }

   // places the cursor under the end element
   void moveBack() {
      if(size >= 1) {
         cursor = end;
         index = size-1;
      }
   }

   // moves cursor one step toward front of this List
   void movePrev() {
      if(cursor != null) {
         if (cursor == first) {
            cursor = null;
         } else { 
            cursor = cursor.last;
         }
      }
   }
   
   // moves cursor one step toward end of the list
   void moveNext() {
      if(cursor != null) {
         if (cursor == end) {
            cursor = null;
         } else {
            cursor = cursor.next;
         }
      }
   }

   // Insert new element into List. If List non-empty, takes place before front
   void prepend(int data) {
      node prep = new node(data, null, first);
      if(size >= 1) first.last = prep;
      else          end = prep;
      first = prep;
      size++;
   }
  
   // Insert new element into List. If List non-empty, takes place after end
   void append(int data) {
      node app = new node(data, end, null);
      if(size >= 1) end.next = app;
      else          first = app;
      end = app;
      size++;
   }

   // Insert new element before cursor. Pre: length() > 0, index() >= 0
   void insertBefore(int data) {
      // exception handling
      if(size <= 0 || index < 0) throw new RuntimeException("insertBefore() illegal call");
      // new node
      node insert = new node(data);
      // insertion
      insert.next = cursor;
      if(cursor.last != null){
         insert.last = cursor.last;
         cursor.last.next = insert;
      }
      cursor.last = insert;
      if (insert.last == null) first = insert;
      // incremention 
      index++;
      size++;     
   }
   
   // Inserts new element after cursor. Pre: length() > 0, index() >= 0
   void insertAfter(int data) {
      // exception handling
      if(size <= 0 || index < 0) throw new RuntimeException("insertBefore() illegal call");     
      // new node
      node insert = new node(data, cursor, cursor.next);
      // insertion
      if (cursor.next == null) end = insert;
      else                     (cursor.next).last = insert;
      cursor.next = insert;
      // incremention
      size++; 
   }
   
   // Deletes the front element. Pre: length() > 0
   void deleteFront() {
      // exception handling
      if(size <= 0) throw new RuntimeException("deleteFront() called on empty List");
      // deletion
      if (index >= 1) {
         first = first.next;
         first.last = null;
         size--;
      } else {
         cursor = null;
      }
   }
   
   // Deletes the end element. Pre: length() > 0
   void deleteBack() {
      // exception handling
      if(size <= 0) throw new RuntimeException("deleteBack() called on empty List");
      // deletion
      if (index < size-1) {
         end = end.last;
         end.next = null;
         size--;
      } else {
         cursor = null;
      }
   }
   
   // Deletes cursor element, making cursor undefined. Pre: length() > 0, index() >= 0
   void delete() {
      // exception handling
      if(size <= 0 || index < 0) throw new RuntimeException("insertBefore() illegal call");
      // deletion
      (cursor.next).last = cursor.last;
      (cursor.last).next = cursor.next;
      cursor = null;
      size--;
      index = -1;
   }
   

   // Return a String representation of this List
   public String toString() {
      String alphabet = new String();
      // loop through list
      for (node convert = first; convert != null; convert = convert.next) {
         alphabet = alphabet + String.valueOf(convert.value) + " ";
      }
      // return the new list alphabet that has been converted to a string
      return alphabet;
   }

   // Returns a new List representing the same integer sequence as this List
   List copy() {
      // new list duplicate
      List duplicate = new List();
      // loop through list appending value to duplicate
      for (node copy = first; copy != null ;copy = copy.next) {
         duplicate.append(copy.value);
      }
      // return copied list
      return duplicate;
   }

   List concat(List L) {
      return null;
   }
}
