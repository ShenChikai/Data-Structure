#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>

#include "../bst/bst.h"
#include "../avl/avlbst.h"
#include "../splay/splay.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please provide an input file and an ouput file!" << endl;
        return 1;
    }

    clock_t start1, start2;
    double duration1, duration2;

    /* Preprocessing here that you don't want to time */

    // Read from the Input
    ifstream input(argv[1]);
	string temp;
	vector<string> vec;

	while (!input.eof()) {
		input >> temp;
		vec.push_back(temp);
	}

	input.close();
	// Done Reading

	int r = 10;			// repeat 100 times
    

    /* Your algorithm here */

    // Insert for AVLTree
	start1 = clock();

    int t1 = 0;
    AVLTree<string, int> avl;
    while (t1 < r) {
	    for (int i = 0; i < (int) vec.size(); ++i) {
			avl.insert(pair <string, int> (vec[i], i));
		}
		avl.clear();
		t1++;
	}

	duration1 = ( clock() - start1 ) / (double) CLOCKS_PER_SEC;

	// Insert for Splay Tree
	start2 = clock();

    int t2 = 0;
    SplayTree<string, int> splay;
    while (t2 < r) {
	    for (int i = 0; i < (int) vec.size(); ++i) {
			splay.insert(pair <string, int> (vec[i], i));
		}
		splay.clear();
		t2++;
	}

	duration2 = ( clock() - start2 ) / (double) CLOCKS_PER_SEC;
    

    // Output
	ofstream Output(argv[2]);
	Output << (int) vec.size() << " insertions." << "\n";
	Output << "AVL: " << duration1 << " seconds" << "\n";
	Output << "Splay: " << duration2 << " seconds" << "\n";
	Output << "Splay expensive: " << splay.report() << "\n";
	Output.close();


    return 0;
}