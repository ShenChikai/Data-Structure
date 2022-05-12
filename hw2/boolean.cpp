#include "boolean.h"

using namespace std;

// numeric exp bool

NumericBooleanExpression::NumericBooleanExpression(NumericExpression* left, string op, NumericExpression* right) : left(left), CompOperator(op), right(right) {

}

NumericBooleanExpression::~NumericBooleanExpression() {
    delete this->left;
    delete this->right;
}

string NumericBooleanExpression::format() const {
    return "[" + this->left->format() + ' ' + CompOperator + ' ' + this->right->format() + "]";
}

// const direct

ConstBooleanExpression::ConstBooleanExpression(int left, string op, int right) : left(left), CompOperator(op), right(right) {

}

ConstBooleanExpression::~ConstBooleanExpression() {

}

string ConstBooleanExpression::format() const {
    return "[" + to_string(left) + ' ' + CompOperator + ' ' + to_string(right) + "]";
}

/*
	// const
 + " "
ConstantComparison::ConstantComparison(Variable* left, string op, Variable* right) left(left), CompOperator(op), right(right) {

}

ConstantComparison::~ConstantComparison() {
    delete this->left;
    delete this->right;
}

string ConstantComparison::format() const {
    return "[" + this->left->format() + CompOperator + this->right->format() + "]";
}


	// 2 NumericExp

NumericComparison::NumericComparison(NumericExpression* left, string op, NumericExpression* right) left(left), CompOperator(op), right(right) {

}

NumericComparison::~NumericComparison() {
    delete this->left;
    delete this->right;
}

string NumericComparison::format() const {
    return "[" + this->left->format() + CompOperator + this->right->format() + "]";
}

	// Constant & NumericExp

ConstNumComparison::ConstNumComparison(Variable* left, string op, NumericExpression* right) left(left), CompOperator(op), right(right) {

}

ConstNumComparison::~ConstNumComparison() {
    delete this->left;
    delete this->right;
}

string ConstNumComparison::format() const {
    return "[" + this->left->format() + CompOperator + this->right->format() + "]";
}

	// NumericExp & Constant

NumConstComparison::NumConstComparison(NumericExpression* left, string op, Variable* right) left(left), CompOperator(op), right(right) {

}

NumConstComparison::~NumConstComparison() {
    delete this->left;
    delete this->right;
}

string NumConstComparison::format() const {
    return "[" + this->left->format() + CompOperator + this->right->format() + "]";
}

*/
