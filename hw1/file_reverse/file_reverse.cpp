#include <iostream>
#include <fstream>
using namespace std;

void fileRev(char* inputPath) {
	ifstream input(inputPath);
	int size;	// declare size
	input >> size;
	char* a = new char[size]; // declare dynamic allocated char array

	int j = 0;
	while (!input.eof()) {	// reverse
		input >> std::noskipws >> a[size - j]; 
		j++;
	}

	input.close();

	for (int i = 0; i < size; i++) {	// print
		cout << a[i];
	}

	cout << endl;

	delete[] a;
	a = NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide an input file!" << endl;
        return 1;
    }

    fileRev(argv[1]);
    return 0;
}
