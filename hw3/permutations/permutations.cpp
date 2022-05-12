#include <iostream>
#include <string>

using namespace std;

void permuHelper(string prefix, string in, int size) {
	if ((int) prefix.length() == size) {
		cout << prefix << endl;
	} else {
		for (int i = 0; i < (int) in.length(); i++) {
			string newPrefix = prefix + in[i];
			string newIn = in.substr(0, i) + in.substr(i+1);
			permuHelper(newPrefix, newIn, size);
		} 
	}

}

void permutations(string in) {
	int size = (int) in.size();

	if (size == 0) {
		cout << "Empty String";
	}

	permuHelper("", in, size);
}
