## CSCI 104
## Name: Chikai Shen
## E-mail: dennyshe@usc.edu 


# Instruction

## This homework contains 1 text file, 1 hear file, and 3 cpp files.

### The text file "hw3.txt" contains the answers to the First Three problems.

### Notice the Permutation problem does not have a makefile. The "permutations.cpp" contains ONLY the functions that used to print out the combinations to the console, user is required to write a seperate *main* function to call the *permutation* function which takes in a string parameter written in this cpp file.

### The *makefile* is set up for cave.cpp by typing cmd, make cave. This produces an executable named cave, and it should take a single command-line parameter, which is the name of the input text file to read from.

### The The *makefile* is set up for company.cpp and company.h by typing cmd, make company. However, the user is required to write a *main.cpp* file under the same path, and the *main.cpp* should not take any input text file as parameter. Otherwise, please take use of the company.cpp and company.h files in any other way you prefer. The signiture is not changed.

#### The code in *main.cpp* should look something like below (hard-wire test-cases):
#### CompanyTracker ctr(5);
#### ctr.merge(0,1);
#### ctr.merge(2,3);
#### ctr.merge(0,3);
#### ctr.split(2);
#### ctr.split(2);
#### ctr.merge(2,4);
#### ctr.split(0);
#### cout << ctr.inSameCompany(0, 1) << endl;	// 0

#### Please read the *makefile* if the instrunctions above was not clear enough.
