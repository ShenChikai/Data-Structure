#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <vector>
using namespace std;

class NumericExpression {
public:
    virtual ~NumericExpression() {};
    virtual std::string format() const = 0;
};

	// UniaryExp: SHOULD INCLUDE Variable;
	// LINE NUM

class Line : public NumericExpression {
public:
	Line(int l);

	~Line();

	virtual std::string format() const;

private:
	int lineNum;
};


	// Const

class ConstVariable : public NumericExpression {
public:
	ConstVariable();

    ConstVariable(int v);

    ~ConstVariable();

    virtual std::string format() const;

private:
	int value;
};

	// Num

class NumericVariable : public NumericExpression {
public:
	NumericVariable(string n);

    NumericVariable(string n, NumericExpression *v);

    ~NumericVariable();

    virtual std::string format() const;

private:
	string name;
	NumericExpression *value;
};

	// Arr

class ArrayVariable : public NumericExpression {
public:
    ArrayVariable(string n);

	ArrayVariable(string n, NumericExpression *i);

    ArrayVariable(string n, NumericExpression *i, int v);

    ~ArrayVariable();

    virtual std::string format() const;

private:
	string name;
	vector<int> *arr;
	NumericExpression *index;
	// int value;
};


	// BinaryExp

class BinaryExpression : public NumericExpression {
public:
	BinaryExpression(NumericExpression* left, string op, NumericExpression* right);

	~BinaryExpression();

	virtual std::string format() const;

	NumericExpression* left;
	string BiOperator;
    NumericExpression* right;
};


#endif
