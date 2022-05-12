#include "interpreter.h"

using namespace std;

// GLOBAL FUNCTIONS | PARSER HELPER FUNCTIONS


	// CLASS INTERPRETER

Interpreter::Interpreter(std::istream& in) {
    //this->parse(in);
    this->execute(in);
}

Interpreter::~Interpreter() {
	delete this->ParsedCmd;
}

void Interpreter::parse(std::istream& in) {
    string line;
    int position = 0;
    while (getline(in, line)) {
        string line_number;

        stringstream stream(line);				// stream takes line, line can now be edited

		while (stream.peek() == ' ' || stream.peek() == '\t') {
			stream.get();
			position++;
		}

        if (stream.rdbuf()->in_avail() == 0) {	// check empty input line...
    		cout << endl;
    		position = 0;
    	} else {

	        stream >> line_number;					// Chceck LINE
	        Line *l = new Line(stoi(line_number));
	        position += (int) line_number.size();

	        while (stream.peek() == ' '|| stream.peek() == '\t') {
				stream.get();
				position++;
			}

			string cmd;
	        stream >> cmd;						// Check COMMAND
	        position += (int) cmd.size();		// pos += skip cmd


	        while (stream.peek() == ' ' || stream.peek() == '\t') {
	        	stream.get();
				position++;
			}


			if (cmd == "PRINT")	{ 														// <LINE> PRINT <NEXP>
	        		
	        		NumericExpression *nexp = parse_numeric_expression(line, position);

					this->ParsedCmd = new Print(l, nexp);

			} else if (cmd == "LET") {													// <LINE> LET <VAR> <NEXP>
	        																			// <LINE> LET { <VAR> [<NEXP1>] } <NEXP2>
																							// { <VAR> [<NEXP1>] } treated as 1 NEXP

					NumericExpression *nexp1 = parse_numeric_expression(line, position); // nexp1: A or A[]

					while (line[position] == ' ' || line[position] == '\t') {
						position++;
					}

					NumericExpression *nexp2 = parse_numeric_expression(line, position); // nexp2: assigned value

					this->ParsedCmd = new Let(l, nexp1, nexp2);

			} else if (cmd == "GOTO") {														// <LINE> GOTO <JLINE>
	        		int intJline = stoi(parse_constant(line, position));
	        		Line *jline = new Line(intJline);

	        		this->ParsedCmd = new Goto(l, jline);

			} else if (cmd == "IF") {														// <LINE> IF <BEXP> THEN <JLINE>

	        		BooleanExpression *bexp = parse_boolean_expression(line, position);

	        		while (line[position] == ' ' || line[position] == '\t') {
						position++;
					}

					string then = parse_variable_name(line, position);


					while (line[position] == ' ' || line[position] == '\t') {
						position++;
					}
	        		
	        		int intJline = stoi(parse_constant(line, position));
	        		Line *jline = new Line(intJline);

	        		this->ParsedCmd = new IfThen(l, bexp, jline);

			} else if (cmd == "GOSUB") {													// Gosub <LINE> GOSUB <JLINE>

	        		int intJline = stoi(parse_constant(line, position));

	        		Line *jline = new Line(intJline);

	        		this->ParsedCmd = new Gosub(l, jline);

			} else if (cmd == "RETURN") {													// RETURN

	        		this->ParsedCmd = new Return(l);

			} else if (cmd == "END") {														// END

	        		this->ParsedCmd = new End(l);

			}

			position = 0;									// reset for next while loop
			output += this->ParsedCmd->format();			// Pretty-Print	


	    }	//empty line check
	} // big while
}

void Interpreter::formatPrint(std::ostream& out) {
	out << output;
}

string Interpreter::parse_constant(string line, int &position) {
	string c = "";

	position--;

		while (line[position + 1] == '-') {
			c += line[position + 1];
			position++;
		}

		if(1 < (int) c.size()) {	// remove additional -sign
			while(c[0] == '-' && c[1] == '-') {
				c.erase(0, 2);
			}
		}

	while (isdigit(line[position + 1]) && position < ( ((int) line.size()) - 1 ) ) {
		c += line[position + 1];
		position++;
	}

	if (position < ( ((int) line.size()) - 1 ) ) position++;

	return c;
}

string Interpreter::parse_variable_name(string line, int &position) {
	string name = "";

	position--;
	while (isalpha(line[position + 1]) && position < ( ((int) line.size()) - 1 ) ) {
		name += line[position + 1];
		position++;
	}

	if (position < ( ((int) line.size()) - 1 ) ) position++;

	return name;
}

NumericExpression* Interpreter::parse_numeric_expression(string line, int &position) {
	if (line[position] == '-' || isdigit(line[position])) {		// Constant
		string constantNum = parse_constant(line, position);
		if (this->numVarMap.find(constantNum) == this->numVarMap.end()) {	// if var did not exist	
			this->numVarMap.insert({constantNum, stoi(constantNum)});
		}

		return new ConstVariable(constantNum);

	} else if (line[position] == '(') {							// Binary Expression
		position++;							// skip '('

		string BiOperator = "";
		while (line[position] == ' ' || line[position] == '\t') {
			position++;
		}

		NumericExpression *left = parse_numeric_expression(line, position);

		while (line[position] == ' ' || line[position] == '\t') {	
			position++;
		}

		BiOperator += line[position]; // assign operator
		position++;

		while (line[position] == ' ' || line[position] == '\t') {
			position++;
		}


		NumericExpression *right = parse_numeric_expression(line, position);

		while (line[position] == ' ' || line[position] == '\t') {
			position++;
		}

		if (line[position] == ')') {	// end with ')'
			position++;
		}

		return new BinaryExpression(left, BiOperator, right);

	} else {													// 2 kinds of Var
		while (line[position] == ' ' || line[position] == '\t') {
			position++;
		}
		
		string name = parse_variable_name(line, position);

		while (line[position] == ' ' || line[position] == '\t') {
			position++;
		}

		if (line[position] == '[') {							// ArrVar
			position++; 			// skip [

			while (line[position] == ' ' || line[position] == '\t') {
				position++;
			}
			

			NumericExpression* index = parse_numeric_expression(line, position); // nested NumExp

			while (line[position] == ' ' || line[position] == '\t') {
				position++;
			}

			if (line[position] == ']') {
				position++;
			}

			if (this->arrVarMap.find(name) == this->arrVarMap.end()) {	// if var did not exist	

				this->arrVarMap[name][index->get()] = 0;	// Add ArrVar to its Map
			}

			return new ArrayVariable(name, index);

		} else {												// NumVar
			if (this->numVarMap.find(name) == this->numVarMap.end()) {	// if var did not exist	
				this->numVarMap.insert({name, 0});	// Add NumVar into its Map
			}
			return new NumericVariable(name);
		}

	}
}

BooleanExpression* Interpreter::parse_boolean_expression(string line, int &position) {
	string op = "";
	while (line[position] == ' ' || line[position] == '\t') {
			position++;
	}

	NumericExpression *left = parse_numeric_expression(line, position);

	while (line[position] == ' ' || line[position] == '\t') {
			position++;
	}

	op += line[position];	// assign operator which is of length of 1 char
	position++;

	while (line[position] == ' ' || line[position] == '\t') {
			position++;
	}

	NumericExpression *right = parse_numeric_expression(line, position);

	return new NumericBooleanExpression(left, op, right);
}

void Interpreter::execute(std::istream& in) {
	// put cmd in vector so that it execute line by line
	// put cmd in map so that jump and return are allowed

    string line;
    int position = 0;

    while (getline(in, line)) {
        string line_number;

        stringstream stream(line);				// stream takes line, line can now be edited

		while (stream.peek() == ' ' || stream.peek() == '\t') {
			stream.get();
			position++;
		}

        if (stream.rdbuf()->in_avail() == 0) {	// check empty input line...
    		//cout << endl;
    		position = 0;
    	} else {

	        stream >> line_number;					// Chceck LINE
	        Line *l = new Line(stoi(line_number));
	        position += (int) line_number.size();

	        while (stream.peek() == ' '|| stream.peek() == '\t') {
				stream.get();
				position++;
			}

			string cmd;
	        stream >> cmd;						// Check COMMAND
	        position += (int) cmd.size();		// pos += skip cmd


	        while (stream.peek() == ' ' || stream.peek() == '\t') {
	        	stream.get();
				position++;
			}

			if (cmd == "PRINT")	{ 														// <LINE> PRINT <NEXP>
	        		
	        		NumericExpression *nexp = parse_numeric_expression(line, position);

					this->ParsedCmd = new Print(l, nexp);

			} else if (cmd == "LET") {													// <LINE> LET <VAR> <NEXP>
	        																			// <LINE> LET { <VAR> [<NEXP1>] } <NEXP2>
																							// { <VAR> [<NEXP1>] } treated as 1 NEXP
			
					NumericExpression *nexp1 = parse_numeric_expression(line, position); // nexp1: A or A[]

					while (line[position] == ' ' || line[position] == '\t') {
						position++;
					}

					NumericExpression *nexp2 = parse_numeric_expression(line, position); // nexp2: assigned value

					this->ParsedCmd = new Let(l, nexp1, nexp2);


			} else if (cmd == "GOTO") {														// <LINE> GOTO <JLINE>
	        		NumericExpression *jl = parse_numeric_expression(line, position);	//jline
	        		
	        		Line *jline = new Line(jl->get());

	        		this->ParsedCmd = new Goto(l, jline);
	        		
			} else if (cmd == "IF") {														// <LINE> IF <BEXP> THEN <JLINE>

	        		BooleanExpression *bexp = parse_boolean_expression(line, position);

	        		while (line[position] == ' ' || line[position] == '\t') {
						position++;
					}

					string then = parse_variable_name(line, position);


					while (line[position] == ' ' || line[position] == '\t') {
						position++;
					}
	        		
	        		NumericExpression *jl = parse_numeric_expression(line, position);	//jline
	        		
	        		Line *jline = new Line(jl->get());

	        		this->ParsedCmd = new IfThen(l, bexp, jline);

			} else if (cmd == "GOSUB") {													// Gosub <LINE> GOSUB <JLINE>

	        		NumericExpression *jl = parse_numeric_expression(line, position);	//jline
	        		
	        		Line *jline = new Line(jl->get());

	        		this->ParsedCmd = new Gosub(l, jline);

			} else if (cmd == "RETURN") {													// RETURN

	        		this->ParsedCmd = new Return(l);

			} else if (cmd == "END") {														// END

	        		this->ParsedCmd = new End(l);

			}

			position = 0;									// reset for next while loop

			this->cmdMap.insert ({stoi(line_number), this->ParsedCmd}); // put cmd in map
		    }	//empty line check
	} // big while

	// EXECUTE!

	this->cmdMapIt = this->cmdMap.begin();
	while (this->cmdMapIt != this->cmdMap.end()) {
		try {
			// check for different cmd s.t. we can pass less arguments
			// 4 argu for LET; 2 argu for GOTO, IF, GOSUB, RETURN

            this->cmdMapIt->second->Do(this->cmdMap, this->cmdMapIt, 
            							this->numVarMap, this->arrVarMap, this->retStack);

        } catch(invalid_argument &e) {	// GOTO IF GOSUB 
            cout <<"Error in line " << this->cmdMapIt->first << ": " 
            			<< e.what() << "<" << this->cmdMapIt->second->getJline() << ">" << endl;
            return;
        } catch(out_of_range &e) {	// RET
        	cout <<"Error in line " << this->cmdMapIt->first << ": " << e.what() << endl;
            return;
        } catch(logic_error &e) {	// DIVISION 0
        	cout <<"Error in line " << this->cmdMapIt->first << ": " 
            			<< e.what() << endl;
            return;
        } catch(exception &e) {
			cout <<"Error in line " << this->cmdMapIt->first << ": " << e.what() << endl;
        }

        this->cmdMapIt++; // go to next line
	}


}