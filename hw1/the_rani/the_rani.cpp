#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <exception>
#include <typeinfo>
#include <cctype>
#include <cmath>
using namespace std;

class TheRani {
public:
    TheRani(char* input_path, char* output_path);
    ~TheRani();
    bool isDigit(const string str);

    // Call execute and handles exceptions
    void main();

private:
    int experiment_count;       // You will need to track the number of experiments
    int* subject_counts;        // For each, the number of subjects
    string** subject_history;   // And for each subject, their history
    bool firstStart;
    int lineNum;

    ifstream input;             // Input file stream
    ofstream output;            // Output file stream

    // Called in the main method.

    void execute(const string& line);

    // Possible helper: deallocate all current members
};

TheRani::TheRani(char* input_path, char* output_path) : input(input_path), output(output_path) {
    experiment_count = 0;
}


TheRani::~TheRani() {
	if (experiment_count == 0) {

	} else {
	    for (int i = 0; i < experiment_count; i++) {   // delete 2nd layer of array
	        delete [] subject_history[i];
	    }
	    delete [] subject_history;  // delete 1st layer of array
	    subject_history =  NULL;
	}
}

// Possible helper: read an integer argument from a stream

void TheRani::main() {
    string line;
    lineNum = 1;
    firstStart = true;
    while (getline(input, line)) {
        try {
            this->execute(line);
        } catch(exception& e) {
            // If you use exceptions, make sure the line number is printed here
            this->output <<"Error on line " << lineNum << " : " << e.what() << endl;
        }
        lineNum++;
    }
}

void TheRani::execute(const string& line) {
    string command;
    stringstream stream(line);  // Initialize the stream with the line
    stream >> command;          // Read the first word, which is the command

	// cerr << command << endl; // for debugging

    if (command == "START") {   // This code should be edited for error checking

    	int subject_pool_count;
        string strSubPool;

    	if (stream.eof()) { 			// too few param? check expFrom
        		throw invalid_argument("too few arguments");
        		return;
        	} else {
	        	stream >> strSubPool;			// type check
	        	if (!isDigit(strSubPool)) { 	// string?
	            	throw invalid_argument("expected integer argument");
	            	return;
	        	} else {			
	        		double dSubPool = stod(strSubPool);
	        		if (dSubPool - floor(dSubPool) == 0) { 	// int?
	        			subject_pool_count = (int) dSubPool;
	        		} else {						// double.
	        			throw invalid_argument("expected integer argument");
	            		return;
	        	}
	        }
	    }

		if (!firstStart) { 		// not 1st START, discard old sub_history
		    for (int i = 0; i < experiment_count; i++) {   // delete 2nd layer of array
	        	delete [] subject_history[i];
	    	}
	   		delete [] subject_history;  // delete 1st layer of array
	    	subject_history =  NULL;
			delete[] subject_counts;	// delete sub_count
			subject_counts = NULL;
    	}
        firstStart = false; 

        
	    int exPara;
        while (stream >> exPara) { // extra para

        }

        if (subject_pool_count < 0) { // sub_pool < 0
            throw out_of_range("argument out of range");
            return;
        } else if (subject_pool_count == 0) { // sub_pool = 0
        	subject_history = new string*[1];
	        subject_history[0] = new string[0];

	        subject_counts = new int[1];	// update sub_count to 0S
	        subject_counts[0] = 0;
	        experiment_count = 1;

        } else { // exception check is done above

	        subject_history = new string*[1];
	        subject_history[0] = new string[subject_pool_count];	
	        for (int i = 0; i < subject_pool_count; i++) {    // initialize the data to empty str
	            subject_history[0][i] = "";
	        }

	        subject_counts = new int[1];    // update sub_count, which serves as sizes of each row
	        subject_counts[0] = subject_pool_count;
	        experiment_count = 1;

        }

    } else if (command == "ADD") {  // add one more exp
        if (experiment_count == 0) {    // missing start
            throw invalid_argument("no subject yet");
        } else {

	        int exPara;
	        while (stream >> exPara) { // extra para

	        }

	        	// exception check is done above

	        experiment_count += 1;

	        int* count = new int[experiment_count];     // add room for size for new exp(row) in sub_count
	        for (int i = 0; i < experiment_count - 1; i++) { // set what before exp_count - 1
	            count[i] = subject_counts[i];
	        }

	        count[experiment_count - 1] = 0;

	        delete[] subject_counts; 
	        subject_counts = count;
	        count = NULL;

	        string** temp = new string* [experiment_count]; // create a temp sub_hist
	        for (int i = 0; i < experiment_count; i++) {    // resize temp to be 1 exp more that sub_hist
	            temp[i] = new string[subject_counts[i]];       
	        }

	        for (int i = 0; i < experiment_count - 1; i++) { // copy from sub_hist to temp
	            for (int j = 0; j < subject_counts[i]; j++) {
	                temp[i][j] = subject_history[i][j];
	            }
	        }
	        temp[experiment_count - 1] = NULL;


	        for (int i = 0; i < experiment_count - 1; i++) {   // delete old sub_hist
	            delete[] subject_history[i];
	        }
	        delete[] subject_history;
	        subject_history = temp; // reasign temp
	        temp = NULL;
        }

    } else if (command == "MOVE") { // MOVE subject from subFrom to subTo, from expFrom to expTo

        if (experiment_count == 0) {    // missing start
            throw invalid_argument("no subject yet");
        } else {

	        int expFrom, expTo, subFrom, subTo; // x, y, n, m
	        string strExpFrom, strExpTo, strSubFrom, strSubTo; // temp strings for type check

	        // data type check expFrom

	        if (stream.eof()) { 			// too few param? check expFrom
        		throw invalid_argument("too few arguments");
        		return;
        	} else {
	        	stream >> strExpFrom;			// type check
	        	if (!isDigit(strExpFrom)) { 	// string?
	            	throw invalid_argument("expected integer argument");
	            	return;
	        	} else {				
	        		double dExpFrom = stod(strExpFrom);
	        		if (dExpFrom - floor(dExpFrom) == 0) { 	// int?
	        			expFrom = (int) dExpFrom;
	        		} else {						// double.
	        			throw invalid_argument("expected integer argument");
	            		return;
	        		}
	        	}
	    	}

	    	// data type check expTo

	    	if (stream.eof()) {			 // too few param? check expFTo
        		throw invalid_argument("too few arguments");
        		return;
        	} else {
		        stream >> strExpTo;			// type check
		        	if (!isDigit(strExpTo)) { 	// string?
		            	throw invalid_argument("expected integer argument");
		            	return;
		        	} else {				
		        		double dExpTo = stod(strExpTo);
		        		if (dExpTo - floor(dExpTo) == 0) { 	// int?
		        			expTo = (int) dExpTo;
		        		} else {						// double.
		        			throw invalid_argument("expected integer argument");
		            		return;
		        		}
		        	}
		    }

	    	// data type check subFrom

	    	if (stream.eof()) { 			// too few param? check subFrom
        		throw invalid_argument("too few arguments");
        		return;
        	} else {
	        	stream >> strSubFrom;			// type check
		        if (!isDigit(strSubFrom)) { 	// string?
		           	throw invalid_argument("expected integer argument");
		           	return;
		       	} else {				
		       		double dSubFrom = stod(strSubFrom);
		       		if (dSubFrom - floor(dSubFrom) == 0) { 	// int?
		       			subFrom = (int) dSubFrom;
		       		} else {						// double.
		        			throw invalid_argument("expected integer argument");
		            		return;
		        	}
		        }
		    }
	    	
	    	// data type check subTo

	    	if (stream.eof()) { 			// too few param? check subTo
        		throw invalid_argument("too few arguments");
        		return;
        	} else {
	        	stream >> strSubTo;			// type check
		        if (!isDigit(strSubTo)) { 	// string?
		           	throw invalid_argument("expected integer argument");
		           	return;
		       	} else {				
		       		double dSubTo = stod(strSubTo);
		       		if (dSubTo - floor(dSubTo) == 0) { 	// int?
		       			subTo = (int) dSubTo;
		       		} else {						// double.
		        			throw invalid_argument("expected integer argument");
		            		return;
		        	}
		        } 

	    	}
	        
	        int exPara;
	        while (stream >> exPara) { // extra para
	        	// do nothing
	        }

	        if (expFrom < 0 || expTo < 0 || subFrom < 0 || subTo < 0) { // negative?
	            throw out_of_range("argument out of range");
	            return;
	        } else if (subject_counts[subFrom] == 0) {	// no subject exist for moving
	        	throw out_of_range("argument out of range");
	        	return;
	    	} else if (subFrom > subject_counts[expFrom] || subTo > subject_counts[expFrom]
	        				|| expFrom > (experiment_count - 1) || expTo > (experiment_count - 1)) { // sub exist? exp exist?
	            throw out_of_range("argument out of range");
	            return;
	        } else if (subFrom > subTo) {  // n > m
	            throw out_of_range("invalid range of subjects to move");
	            return;
	        }

	        	// exception check is done above

	        int MoveSize = subTo - subFrom + 1;
	        if (expTo == expFrom) { // moving to self
	            // In this case, sub_count stay the same
	        	int size = subject_counts[expFrom];
	            string* tempX = new string[size];
	            for (int i = 0; i < subFrom; i++) { // <= n
	                tempX[i] = subject_history[expFrom][i];
	            }

	            for (int i = subTo + 1; i < size; i++) { //  => m

	            	for (int j = subFrom; j < (size - subTo - 1); j++) {
	                	tempX[j] = subject_history[expFrom][i];
	            	}
	            }

	            for (int i = (size - MoveSize); i < size; i++) {
	                for (int j = subFrom; j <= subTo; j++) { // n-m
	                    tempX[i] = subject_history[expFrom][j];
	                    if (expTo != 0) {
	                    	tempX[i] += to_string(expTo);
	                    	tempX[i] += ' ';
	                	}
	                }
	            }
	            delete[] subject_history[expFrom];  // re-assign expFrom
	            subject_history[expFrom] = tempX;
	            //delete[] tempX;
	            tempX = NULL;
	            subject_counts[expTo] = size;

	        } else {	// From != To

	            string *tempExpFrom;
	            tempExpFrom = new string[subject_counts[expFrom] - MoveSize];  // new sizes for the two rows
	            string *tempExpTo;
	            tempExpTo = new string[subject_counts[expTo] + MoveSize];

	            for (int i = 0; i < subject_counts[expTo]; i++) { // copy from expTo to tempExpTo
	                tempExpTo[i] = subject_history[expTo][i];
	            }

	            for (int i = subject_counts[expTo]; i < subject_counts[expTo] + MoveSize; i++) { // copy sub n-m to tempExpTo
	                for (int j = subFrom; j <= subTo; j++) {
	                    tempExpTo[i] = subject_history[expFrom][j];
	                    if (expTo != 0) {
	                    	tempExpTo[i] += to_string(expTo);
	                    	tempExpTo[i] += ' ';
	                	}
	                }
	            }

	            delete[] subject_history[expTo];
	            subject_history[expTo] = tempExpTo; // re-assign expTo
	            //delete[] tempExpTo;
	            tempExpTo = NULL;

	            // Now, fix expFrom



	            for (int i = 0; i < subFrom; i++) {    // copy data before n
	                tempExpFrom[i] = subject_history[expFrom][i];
	            }

	            for (int i = subFrom; i < subject_counts[expFrom] - MoveSize; i++) {
	                for (int j = subTo + 1; j < subject_counts[expFrom]; j++) { // copy data after m
	                    tempExpFrom[i] = subject_history[expFrom][j];
	                }
	            }
	            
	            delete[] subject_history[expFrom];
	            subject_history[expFrom] = tempExpFrom; // re-assign expFrom
	            //delete[] tempExpFrom;
	            tempExpFrom = NULL;

	            subject_counts[expFrom] -= MoveSize; // update sub_count after MOVE
	            subject_counts[expTo] += MoveSize;

	        }
	    }

    } else if (command == "QUERY") { // getVal

        if (experiment_count == 0) {    // missing start
            throw invalid_argument("no subject yet");
        } else {

        	int exp, sub;
        	string strExp, strSub;

        	if (stream.eof()) { 				// too few param? check exp
        		throw invalid_argument("too few arguments");
        		return;
        	} else {
        		stream >> strExp;			// type check
	        	if (!isDigit(strExp)) { 	// string?
	            	throw invalid_argument("expected integer argument");
	            	return;
	        	} else {			
	        		double dExp = stod(strExp);
	        		if (dExp - floor(dExp) == 0) { 	// int?
	        			exp = (int) dExp;
	        		} else {						// double.
	        			throw invalid_argument("expected integer argument");
	            		return;
	        		}
	        	}
	    	}

	        if (stream.eof()) {					// too few param? check sub
        		throw invalid_argument("too few arguments");
        		return;
        	} else {
				stream >> strSub;			// type check
	        	if (!isDigit(strSub)) { 	// string?
	            	throw invalid_argument("expected integer argument");
	            	return;
	        	} else {				
	        		double dSub = stod(strSub);
	        		if (dSub - floor(dSub) == 0) { 	// int?
	        			sub = (int) dSub;
	        		} else {						// double.
	        			throw invalid_argument("expected integer argument");
	            		return;
	        		}
	        	}
        	}

	        

	        int exPara;
	        while (stream >> exPara) { // extra para

	        }

	        if (exp < 0 || sub < 0) { // negative?
	            throw out_of_range("argument out of range");
	            return;
	        } else if (sub >= subject_counts[exp] || exp > (experiment_count - 1)) { // exp , sub exist?
	            throw out_of_range("argument out of range");
	            return;
	        }

	        	// exception check is done above

	        output << subject_history[exp][sub] << endl; // output

	    }
    } else { 
        throw invalid_argument("command does not exist"); // illegal command
		int exPara;
        while (stream >> exPara) { // extra para

        }
    }
}

bool TheRani::isDigit(const string str) {
	bool isDot = false;

	if (str[0] == '-') { }

	for (int i = 0; i < (int)str.length(); i++) {
			if (str[i] == '.') {
				if (!isDot) {
					isDot = true;
				} else {			// more than 1 dot?
					return false;
				}
			} else {
		        if (!isdigit(str[i])) {
		        	return false;
		        }
		    }
	}

    return true;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Please provide an input and output file!" << endl;
        return 1;
    }


    TheRani tr(argv[1], argv[2]);
    tr.main();
    return 0;
}
