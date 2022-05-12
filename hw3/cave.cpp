#include <string>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int cave(char* input_path) {
	ifstream input(input_path);
	stack <char> track;
	char dir;
	int unrolled = 0;

	while (input >> dir) {
		if ( !track.empty() &&
				( (dir == 'N' && track.top() == 'S') || (dir == 'S' && track.top() == 'N') 
					|| (dir == 'W' && track.top() == 'E') || (dir == 'E' && track.top() == 'W') ) ) {
			track.pop();
			unrolled--;
		} else {
			track.push(dir);
			unrolled++;
		}
	}

	input.close();
	return unrolled;
}


int main(int argc, char *argv[])
{
	if (argc < 2) {
        cerr << "Please provide an input file!" << endl;
        return 1;
    }

    cout << "The number of units of string that are unrolled: " << cave(argv[1]) << endl;
	return 0;
}