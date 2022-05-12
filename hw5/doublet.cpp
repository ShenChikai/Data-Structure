#include <fstream>
#include <iostream>
#include <sstream>
#include "heap.h"
#include <string>
#include <set>
#include <map>
#include <stdlib.h>

// creating all possible words that you can form by replacing one letter at a time
// then looking up whether they are actually words

// min in minHeap is the word with smallest prio, that is closest to TARGET word.

/*
	struct item
	      {
	        item(const T& d, int p, int n);
	        T data;								
	        int prio;
	        int nth;
	      };
*/

using namespace std;

struct item{
  item(string d, int p, int n);
  string data;
  int prio;
  int nth;
};

int geth(string word, string target) {
	int h = 0;
	for(int i = 0; i < (int) word.length(); i++) {
		if(word[i] != target[i]){
			h++;
		}
	}
	return h;
}

void doublet(string start, string target, set<string> dictionary) {
	map<string, int> d;		// distance from start for a word
	map<string, bool> v;	// visted?
	map<string, string> p;	// path (parent)
	MinHeap<string> HP(3);
	string temp;
	int steps = 0;
	int expansions = 0;
	bool found = false;

	if (dictionary.find(start) == dictionary.end() || dictionary.find(target) == dictionary.end()) {
		cout << "Warning: " << endl;
		cout << "	Starting or Ending word does not exist in word.txt." << endl;
		exit(0);
	}

	// initialize map distance from start
	for (set<string>::iterator itd = dictionary.begin(); itd != dictionary.end(); ++itd) {
		d[*itd] = 2147483647; // init to INT_MAX
	}

	// initialize map visit
	for (set<string>::iterator itv = dictionary.begin(); itv != dictionary.end(); ++itv) {
		v[*itv] = false; // init to not yet visited
	}

	d[start] = 0;
	v[start] = true;
	p[start] = "done";
	HP.add(start, d[start] + geth(start, target));

	while (!HP.isEmpty()) {
		temp = HP.peekDoublet(target);	// tie break here

		HP.remove();

		if (temp == target) {				// check found yet;
			found = true;
			break;
		}

		expansions++;

		for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
			
		    if (geth(temp, *it) == 1) { // for all not visited words thats one letter diff from temp (h = 1)

		    	if ( !v[*it] || (d[temp] + geth(temp, target) + 1 < d[*it] + geth(*it, target)) ) {	
		    		d[*it] = d[temp] + 1;	// update distance from start
		    		p[*it] = temp;

		    		if (!v[*it]) {	// first time visit
		    			HP.add(*it, d[*it] + geth(target, *it));	// add to heap if new
		    			v[*it] = true; 	// now visited

		    		} else {
		    			int nth = HP.getNth(*it);
		    			HP.update(nth, d[*it] + geth(target, *it));
		    		}
					
		    		
		    	}
			}
		}
	}

	map<string, string>::iterator itp = p.find(target);
	while (1) {
		if (itp->second == "done") {
			break;
		} else {
			itp = p.find(p[itp->first]);
			steps++;
		}
	} 

	if (found) {
		cout << steps << endl;			
		cout << expansions << endl;		
	} else {
		cout << "No transformation." << endl;
		cout << expansions << endl;
	}
}

int main(int argc, char* argv[]) {
	// ./doublet head tail words.txt

    if (argc < 4) {
        cerr << "Please provide a starting word, an ending word, and an word file!" << endl;
        return 1;
    }

    string start, target;
    start = argv[1];
    target = argv[2];

    ifstream input(argv[3]);
    string temp;
    set<string> dictionary;

	while(getline(input, temp)) {
		dictionary.insert(temp);
	}

	input.close();

    doublet(start, target, dictionary);
    return 0;
}