#ifndef COMMAND_HPP
#define COMMAND_HPP

using namespace std;

#include <string>
#include <stack>
#include <map>
#include "arithmetic.h"
#include "boolean.h"

class Command {
public:
	virtual ~Command() {};

	virtual void Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it, 
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s) = 0;

	virtual int getLine() = 0;

	virtual int getJline() = 0;

    virtual std::string format() const = 0;

};

	// Print, <LINE> PRINT <NEXP>

class Print : public Command {
public:
	Print(Line *l, NumericExpression *n);

	~Print();

	virtual void Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s);

	virtual int getLine();

	virtual int getJline();

	virtual std::string format() const;

private:
	Line* line;
	NumericExpression *nexp;
};

	// Let: LET <VAR> <AEXPR2> / LET <VAR> [<AEXPR1>] <AEXPR2>

class Let : public Command {
public:
	Let(Line *l, NumericExpression *n1, NumericExpression *n2);

	~Let();

	virtual void Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s);

	virtual int getLine();

	virtual int getJline();

    virtual std::string format() const;

private:
	Line* line;
	NumericExpression *nexp1;	// VAR
	NumericExpression *nexp2;	// VALUE
};


	// Goto, <LINE> GOTO <JLINE>

class Goto : public Command {
public:
	Goto(Line *l, Line *j);

	~Goto();

	virtual void Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s);

	virtual int getLine();

	virtual int getJline();

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

	virtual void Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s);

	virtual int getLine();

	virtual int getJline();

	virtual std::string format() const;

private:
	Line *line;
	BooleanExpression *boolExp;
	Line *jline;
};

	// Gosub <LINE> GOSUB <JLINE>

class Gosub : public Command {
public:
	Gosub(Line *l, Line *j);

	~Gosub();

	virtual void Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s);

	virtual int getLine();

	virtual int getJline();

	virtual std::string format() const;

private:
	Line *line;
	Line *jline;
};

	// Return <LINE> RETURN

class Return : public Command {
public:
	Return(Line *l);

	~Return();

	virtual void Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s);

	virtual int getLine();

	virtual int getJline();

	virtual std::string format() const;

	NumericExpression *bline; // public s.t. it can be changed when a gosub is reached

private:
	Line *line;
};

	// End

class End : public Command {
public:
	End(Line *l);

	~End();

	virtual void Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s);

	virtual int getLine();

	virtual int getJline();

	virtual std::string format() const;

private:
	Line *line;
};

#endif
