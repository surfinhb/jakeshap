// Jake Shapiro
// jtshapir@ucsc.edu
// October 3, 2016
// CS 101: PA1
// Lex.java

import java.io.*;
import java.util.Scanner;

public class Lex {
   public static void main(String[] args) throws IOException {
      // Check if two arguments are passed
      if(args.length < 2 || args.length > 2) {
         System.out.println("Use-> Lex input output");
         System.exit(1);
      }

      // IO
      Scanner scan1 = new Scanner(new File(args[0]));
      Scanner scan2 = new Scanner(new File(args[0]));
      PrintWriter output = new PrintWriter(new File(args[1]));

      // Count the number of lines n in the file named by args[0].
      int n = 0;
      while(scan1.hasNextLine()) {
         ++n;
         scan1.nextLine();
      }
      
      // Create a String array of length n
      String[] lineArray = new String[n];
      
      // read in lines of the file as Strings, place them in array
      int m = -1;
      while(scan2.hasNextLine()) {
         lineArray[++m] = scan2.nextLine();
      }
            
      // begin with an initially empty List
      List indexList = new List();

      // insert other indices of array one by one
      indexList.append(0);
      // insertion sort using ADT      
      for(int i = 1; i < n; i++) {
         // move cursor to the back
         indexList.moveBack();
         // while cursor is defined and cursor is bigger than last element
         while(indexList.index() != -1  && lineArray[i].compareTo(lineArray[indexList.get()]) <= 0) {             
            // move cursor back
            indexList.movePrev();
         }
         // if cursor is undefined insert element at beggining of list 
         // (i.e. it iterated over whole list w/o finding larger string)
         if(indexList.index() == -1) indexList.prepend(i);
         // otherwise insert after cursor element
         else                        indexList.insertAfter(i);
      }

      // print
      for (indexList.moveFront(); indexList.index() >= 0; indexList.moveNext()){
         output.println(lineArray[indexList.get()]);
      }
      output.close();
   }
}
