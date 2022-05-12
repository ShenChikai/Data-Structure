#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include <string>
#include "arithmetic.h"

using namespace std;

class BooleanExpression {
public:
    virtual ~BooleanExpression() {};

    virtual std::string format() const = 0;
};

class NumericBooleanExpression : public BooleanExpression {
public:
	NumericBooleanExpression(NumericExpression* left, string op, NumericExpression* right);

    ~NumericBooleanExpression();

    virtual std::string format() const;

    NumericExpression* left;
    string CompOperator;
    NumericExpression* right;
};

class ConstBooleanExpression : public BooleanExpression {
public:
	ConstBooleanExpression(int left, string op, int right);

    ~ConstBooleanExpression();

    virtual std::string format() const;

    int left;
    string CompOperator;
    int right;
};

/*

	// Direct Comparison b/w const

class ConstantComparison : public BooleanExpression {
public:
	ConstantComparison(Variable* left, string op, Variable* right);

	~ConstantComparison();

	virtual std::string format() const;

}

	// 2 NumericExp Comparison

class NumericComparison : public BooleanExpression {
public:
	NumericComparison(NumericExpression* left, string op, NumericExpression* right);

	~NumericComparison();

	virtual std::string format() const;

}

	// Constant & NumericExp Comparison

class ConstNumComparison : public BooleanExpression {
public:
	ConstNumComparison(Variable* left, string op, NumericExpression* right);

	~ConstNumComparison();

	virtual std::string format() const;

}

	// NumericExp & Constant Comparison

class NumConstComparison : public BooleanExpression {
public:
	NumConstComparison(NumericExpression* left, string op, Variable* right);

	~NumConstComparison();

	virtual std::string format() const;

}

*/

#endif
