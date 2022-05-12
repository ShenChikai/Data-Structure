#include "interpreter.h"

using namespace std;

// GLOBAL FUNCTIONS | PARSER HELPER FUNCTIONS


	// CLASS INTERPRETER

Interpreter::Interpreter(std::istream& in) {
    this->parse(in);
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
			output += this->ParsedCmd->format();	
	    }	//empty line check
	} // big while
}

void Interpreter::write(std::ostream& out) {
	out << output;
}

string Interpreter::parse_constant(string line, int &position) {
	string c = "";

	position--;

		if (line[position + 1] == '-') {
			c += line[position + 1];
			position++;
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
		return new ConstVariable(stoi(constantNum));

	} else if (line[position] == '(') {							// Binary Expression
		position++;							// skip '('

		string op = "";
		while (line[position] == ' ' || line[position] == '\t') {
			position++;
		}

		NumericExpression *left = parse_numeric_expression(line, position);

		while (line[position] == ' ' || line[position] == '\t') {	
			position++;
		}

		op += line[position]; // assign operator
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

		return new BinaryExpression(left, op, right);

	} else {													// Variable
		while (line[position] == ' ' || line[position] == '\t') {
			position++;
		}
		
		string name = parse_variable_name(line, position);

		while (line[position] == ' ' || line[position] == '\t') {
			position++;
		}

		if (line[position] == '[') {		// Arr Var
			position++; 			// skip [

			while (line[position] == ' ' || line[position] == '\t') {
				position++;
			}
			

			NumericExpression* index = parse_numeric_expression(line, position); // Numeric Expression inside []

			while (line[position] == ' ' || line[position] == '\t') {
				position++;
			}

			if (line[position] == ']') {
				position++;
			}

			return new ArrayVariable(name, index);

		} else {							// Num Var
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
