#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>	// isdigit
#include <exception>
#include <stack>
#include <map>

#include "command.h"
#include "arithmetic.h"
#include "boolean.h"

using namespace std;


class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void formatPrint(std::ostream& out);

    void execute(std::istream& in);


    string parse_constant(string line, int &position);
    string parse_variable_name(string line, int &position);
    NumericExpression* parse_numeric_expression(string line, int &position);
    BooleanExpression* parse_boolean_expression(string line, int &position);

private:
    void parse(std::istream& in);

    

    Command *ParsedCmd;

    map<int, Command*> cmdMap;                  // cmdMap <lineNum, cmd*>

    map<int, Command*>::iterator cmdMapIt = cmdMap.begin(); // index

    map<string, int> numVarMap;     // NumVarMap for numVar map<name, value>
    map<string, map<int, int>> arrVarMap;      // ArrVar double map<name, map<index, value> >

    stack<int> retStack;

    string output;
};


#endif
