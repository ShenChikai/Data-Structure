## CSCI 104
## Name: Chikai Shen
## E-mail: dennyshe@usc.edu 

# Problem 1: Heaps 
## All answers are written in a text file named "hw5.txt".

# Problem 2: Backtracking
## Type 'make learning' in Console, it will generate executable learning which requires a input text file.
## 'input.txt' input file is not included, user must write a input text file.
## Type './learning input.txt' followed by the name of the input text file to execute.
## It might take 6s to compute for n=25.

# Problem 3: Create a d-ary Heap
## 'heap.h' only contains the class itself. No main function is included.
## makefile does NOT include the make command for 'heap.h'.
## No 'heapMain.cpp' is inlcuded for show case, please write the main file to pass commands in the main function.
## Here is an example of how 'heapMain.cpp' might be written:
### #include "heap.h"
### #include <string>
### using namespace std;
### 
### int main(int argc, char* argv[]){
###  MinHeap<string> myHeap(3);
### 
###  myHeap.add("c", 3);
###  myHeap.add("a", 5);
###  myHeap.add("d", 2);

###  cout << myHeap.peek() << endl;
###  myHeap.remove();

###  return 0;
### }

# Problem 4: A* Search
## 'doublet.cpp' needs to be under the same folder with heap.h is it includes it.
## 'word.txt' input file is not included, and user must write a input text file for the program to execute.
## Type 'make doublet' in the Console to generate executable 'doublet'.
## Type './doublet START_WORD END_WORD word.txt' to execute. START_WORD and END_WORD are the two words of user's choice, and 'word.txt' is the input text file.

# makefile is cleanly written, user may feel free to make changes to it to accomodate user's files.
