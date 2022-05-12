#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP

#include <string>
#include <stack>
#include <map>
#include "arithmetic.h"

using namespace std;

class BooleanExpression {
public:
    virtual ~BooleanExpression() {};

    virtual bool compare(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) = 0;

    virtual std::string format() const = 0;
};

class NumericBooleanExpression : public BooleanExpression {
public:
	NumericBooleanExpression(NumericExpression* left, string op, NumericExpression* right);

    ~NumericBooleanExpression();

    virtual bool compare(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

    virtual std::string format() const;

    NumericExpression* left;
    string CompOperator;
    NumericExpression* right;
};

class ConstBooleanExpression : public BooleanExpression {
public:
	ConstBooleanExpression(int left, string op, int right);

    ~ConstBooleanExpression();

    virtual bool compare(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap);

    virtual std::string format() const;

    int left;
    string CompOperator;
    int right;
};

#endif
