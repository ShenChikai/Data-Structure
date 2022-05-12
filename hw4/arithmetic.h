#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <math.h>
#include <ctype.h>
#include <exception>
using namespace std;

class NumericExpression {
public:
    virtual ~NumericExpression() {}
    virtual string getName() = 0;
    virtual void write(NumericExpression *v) = 0;
    virtual	int get() = 0;
    virtual int getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) = 0;
    virtual bool checkArrVar() = 0;
    virtual bool checkBinary() = 0;
    virtual string format() const = 0;
    virtual int getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap)= 0;
};

	// UniaryExp: SHOULD INCLUDE Variable;
	// LINE NUM

class Line : public NumericExpression {
public:
	Line(int l);

	~Line();

	virtual string getName();

	virtual void write(NumericExpression *v);

	virtual int get();

	virtual int getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

	virtual bool checkArrVar();

	virtual bool checkBinary();

	virtual std::string format() const;

	virtual int getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

private:
	int lineNum;
};


	// Const

class ConstVariable : public NumericExpression {
public:
	ConstVariable();

    ConstVariable(string n);

    ~ConstVariable();

    virtual string getName();

    virtual void write(NumericExpression *v);	// no implementation

    virtual int get();

    virtual int getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

    virtual bool checkArrVar();

    virtual bool checkBinary();

    virtual std::string format() const;

    virtual int getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

private:
	int value;
};

	// Num

class NumericVariable : public NumericExpression {
public:
	NumericVariable(string n);

    NumericVariable(string n, NumericExpression *v);

    ~NumericVariable();

    virtual string getName();

    virtual void write(NumericExpression *v);

    virtual int get();

    virtual int getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

    virtual bool checkArrVar();

    virtual bool checkBinary();

    virtual std::string format() const;

    virtual int getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

private:
	string name;
	int value;
};

	// Arr

class ArrayVariable : public NumericExpression {
public:
    ArrayVariable(string n);

    ArrayVariable(string n, NumericExpression *i);

    ArrayVariable(string n, NumericExpression *i, int v);

    ~ArrayVariable();

    virtual string getName();

    virtual void write(NumericExpression *v);

    virtual int get() ; // get value at index i

    virtual int getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

    virtual bool checkArrVar();

    virtual bool checkBinary();

    virtual std::string format() const;

    virtual int getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

private:
	string name;
	NumericExpression *index;
	//map<int, int> infArr; 	// This is the infinite array
							// Insert the (index, value) as (KEY, VAL) pairs
							// If index FIND, return value
							// If index not FIND, return 0
};


	// BinaryExp

class BinaryExpression : public NumericExpression {
public:
	BinaryExpression(NumericExpression* left, string op, NumericExpression* right);

	~BinaryExpression();

	virtual string getName();

    virtual void write(NumericExpression *v);	// no implementation

	virtual int get() ;

	virtual int getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

	virtual bool checkArrVar();

	virtual bool checkBinary();

	virtual std::string format() const;

	virtual int getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

private:

	NumericExpression* left;
	string BiOperator;
    NumericExpression* right;
};


#endif
