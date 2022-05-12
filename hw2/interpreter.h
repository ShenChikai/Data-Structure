#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>	// isdigit

#include "command.h"
#include "arithmetic.h"
#include "boolean.h"

using namespace std;


class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out);


    string parse_constant(string line, int &position);
    string parse_variable_name(string line, int &position);
    NumericExpression* parse_numeric_expression(string line, int &position);
    BooleanExpression* parse_boolean_expression(string line, int &position);

private:
    void parse(std::istream& in);

    Command *ParsedCmd;

    string output;
};


#endif
