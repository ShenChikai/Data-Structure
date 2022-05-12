#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct course
{
	string name;
	double work;
	double learn;
};

bool isMaxWork (vector<course> v, double workCurrent, double workTotal) {
	if (v.empty()) return true;

	for(int i = 0; i < (int) v.size(); i++) {
		if(workCurrent + v[i].work <= workTotal) {
			return false;
		}
	}

	return true;
}


void backTrack (vector<course> v, double workCurrent, double workTotal, double learned, double &max) {
	if (isMaxWork(v, workCurrent, workTotal)) {
		if (learned > max) {
			max = learned;	
		}
	} 
	
	if ((int) v.size() > 1) {
		vector<course> copy( v.begin() + 1, v.end() );

		if (workCurrent + v[0].work <= workTotal) {

			backTrack(copy, workCurrent + v[0].work, workTotal, learned + v[0].learn, max);
			backTrack(copy, workCurrent, workTotal, learned, max);

		} else {

			backTrack(copy, workCurrent, workTotal, learned, max);

		}
	} else if (v.size() == 1) {		
		if (workCurrent + v[0].work <= workTotal) {
			vector<course> copy;

			backTrack(copy, workCurrent + v[0].work, workTotal, learned + v[0].learn, max);

		} else {

			

		}
	} 

}


void loadVecAndBackTrack (char* inputPath) {
	ifstream input(inputPath);
	int line;
	double workTotal;
	string tempName, tempWork, tempLearn;
	vector<course> v;

	input >> line;
	input >> workTotal;

	for(int i = 0; i < line; ++i) {
		input >> tempName;
		input >> tempWork;
		input >> tempLearn;
		course prop;
		prop.name = tempName;
		prop.work = stod(tempWork);
		prop.learn = stod(tempLearn);
		v.push_back(prop);
	}

	input.close();



	// map loaded;

	double max = 0;
	
	backTrack(v, 0, workTotal, 0, max);

	cout << max << endl;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide an input file!" << endl;
        return 1;
    }

    loadVecAndBackTrack(argv[1]);
    return 0;
}
