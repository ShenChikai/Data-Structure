#ifndef COMMAND_HPP
#define COMMAND_HPP

using namespace std;

#include <string>
#include "arithmetic.h"
#include "boolean.h"

class Command {
public:
	virtual ~Command() {};
    virtual std::string format() const = 0;

};

	// Print, <LINE> PRINT <NEXP>

class Print : public Command {
public:
	Print(Line *l, NumericExpression *n);

	~Print();

	virtual std::string format() const;

private:
	Line* line;
	NumericExpression *nexp;
};

	// Let 

class Let : public Command {
public:
	Let(Line *l, NumericExpression *n1, NumericExpression *n2);

	~Let();

    virtual std::string format() const;

private:
	Line* line;
	NumericExpression *nexp1;
	NumericExpression *nexp2;
};


	// Goto, <LINE> GOTO <JLINE>

class Goto : public Command {
public:
	Goto(Line *l, Line *j);

	~Goto();

	virtual std::string format() const;

private:
	Line *line;
	Line *jline;

};

	// IF THEN, <LINE> IF <BEXP> THEN <JLINE>

class IfThen : public Command {
public:
	IfThen(Line *l, BooleanExpression *b, Line *j);

	~IfThen();

	virtual std::string format() const;

private:
	Line *line;
	BooleanExpression *boolean;
	Line *jline;

};

	// Gosub <LINE> GOSUB <JLINE>

class Gosub : public Command {
public:
	Gosub(Line *l, Line *j);

	~Gosub();

	virtual std::string format() const;

private:
	Line *line;
	Line *jline;
};

	// Return <LINE> RETURN

class Return : public Command {
public:
	Return(Line *l);

	Return(Line *l, Line *r);

	~Return();

	virtual std::string format() const;

private:
	Line *line;
	Line *ret;
};

	// End

class End : public Command {
public:
	End(Line *l);

	~End();

	virtual std::string format() const;

private:
	Line *line;
};

#endif
