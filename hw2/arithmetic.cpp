#include "arithmetic.h"

using namespace std;

	// UninrayExp

// Line

Line::Line(int l) : lineNum(l) {

}

Line::~Line() {

}

string Line::format() const {
	return to_string(this->lineNum);
}


	// const

ConstVariable::ConstVariable() : value(0) {

}

ConstVariable::ConstVariable(int v) : value(v) {

}

ConstVariable::~ConstVariable() {
	// do nothing
}

string ConstVariable::format() const {
    return to_string(this->value);
}

	// NumVar

NumericVariable::NumericVariable(string n) : name(n) {
	value = new ConstVariable();
}

NumericVariable::NumericVariable(string n, NumericExpression *v) : name(n), value(v) {

}

NumericVariable::~NumericVariable() {
	delete value;
}

string NumericVariable::format() const {
    return this->name;
}


	// ArrayVar

ArrayVariable::ArrayVariable(string n) {
	this->name = n;
	// wait to be implemented, this->arr  = new vector<int>;
}

ArrayVariable::ArrayVariable(string n, NumericExpression *i) : name(n), index(i){

}

ArrayVariable::ArrayVariable(string n, NumericExpression *i, int v) {
	this->name = n;
	this->index = i;
	// wait to be implemented
}

ArrayVariable::~ArrayVariable() {
	//if (this->arr->empty()) {
	//	delete[] this->arr;
	//}	
	//delete this->arr;
	delete this->index;
}

string ArrayVariable::format() const {
    return this->name + "[" + this->index->format() + "]";
}


	// BinaryExp


BinaryExpression::BinaryExpression(NumericExpression* left, string op, NumericExpression* right) : left(left), BiOperator(op), right(right) {

}

BinaryExpression::~BinaryExpression() {
    delete this->left;
    delete this->right;
}

string BinaryExpression::format() const {
    return "(" + this->left->format() + " " + this->BiOperator + " " + this->right->format() + ")";
}
