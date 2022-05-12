#include "arithmetic.h"

using namespace std;

	// UninrayExp

	// Line

Line::Line(int l) : lineNum(l) {

}

Line::~Line() {

}

void Line::write(NumericExpression *v) {
	this->lineNum = v->get();
}

int Line::get() {
	return this->lineNum;
}

int Line::getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	return -1;
}

string Line::getName() {
	return "NoName4Line";
}

bool Line::checkArrVar() {
	return false;
}

bool Line::checkBinary() {
	return false;
}

string Line::format() const {
	return to_string(this->lineNum);
}

int Line::getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	return -1; // never called
}


	// const

ConstVariable::ConstVariable() : value(0) {

}

ConstVariable::ConstVariable(string n) {
	this->value = stoi(n);
}

ConstVariable::~ConstVariable() {
	
}

void ConstVariable::write(NumericExpression *v) {
	//this->value = v->get();  Const Value cannot be changed
}

string ConstVariable::getName() {
	return to_string(this->value);
}

int ConstVariable::get() {
	return this->value;
}

int ConstVariable::getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	return this->value;
}

bool ConstVariable::checkArrVar() {
	return false;
}

bool ConstVariable::checkBinary() {
	return false;
}

string ConstVariable::format() const {
    return to_string(this->value);
}

int ConstVariable::getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	return -1; // never called
}

	// NumVar

NumericVariable::NumericVariable(string n) : name(n), value(0) {

}

NumericVariable::NumericVariable(string n, NumericExpression *v) : name(n) {
	this->value = v->get();
}

NumericVariable::~NumericVariable() {

}

string NumericVariable::getName() {
	return this->name;
}

void NumericVariable::write(NumericExpression *v) {
	this->value = v->get();
}

int NumericVariable::get() {
	return this->value;
}

int NumericVariable::getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	return this->value;
}

bool NumericVariable::checkArrVar() {
	return false;
}

bool NumericVariable::checkBinary() {
	return false;
}

string NumericVariable::format() const {
    return this->name;
}

int NumericVariable::getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	return -1; // never called
}


	// ArrayVar

ArrayVariable::ArrayVariable(string n) : name(n) {
}

ArrayVariable::ArrayVariable(string n, NumericExpression *i) : name(n), index(i){

}

ArrayVariable::ArrayVariable(string n, NumericExpression *i, int v) : name(n), index(i) {

}

ArrayVariable::~ArrayVariable() {
	delete index;
}

string ArrayVariable::getName() {
	return this->name;
}

void ArrayVariable::write(NumericExpression *v) {
	
}

int ArrayVariable::get() {
	return -999; // should not be called since cannot get from ArrVar
}

int ArrayVariable::getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	return -1;
}

bool ArrayVariable::checkArrVar() {
	return true;
}

bool ArrayVariable::checkBinary() {
	return false;
}

string ArrayVariable::format() const {
    return this->name + "[" + this->index->format() + "]";
}

int ArrayVariable::getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	int i = 0;
	if (this->index->checkArrVar()) {			// Arr
		i += arrVarMap[this->index->getName()][this->index->getIndex(numVarMap, arrVarMap)];
	} else if (this->index->checkBinary()) {	// Bi
		i += this->index->getBinary(numVarMap, arrVarMap);
	} else {							// Num
		i += numVarMap[this->index->getName()];
	}
	return i;
}

	// BinaryExp


BinaryExpression::BinaryExpression(NumericExpression* left, string op, NumericExpression* right) : left(left), BiOperator(op), right(right) {

}

BinaryExpression::~BinaryExpression() {
    delete this->left;
    delete this->right;
}

string BinaryExpression::getName() {
	return this->left->getName() + this->BiOperator + this->right->getName();
}

void BinaryExpression::write(NumericExpression *v) {
	
}

int BinaryExpression::get() {
	return -111; // dont use this
}

int BinaryExpression::getBinary(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	int biL = 0;
	int biR = 0;

	if (this->left->checkArrVar()) {			// Arr
		biL += arrVarMap[this->left->getName()][this->left->getIndex(numVarMap, arrVarMap)];
	} else if (this->left->checkBinary()) {	// Bi
		biL += this->left->getBinary(numVarMap, arrVarMap);
	} else {							// Num
		biL += numVarMap[this->left->getName()];
	}

	if (this->right->checkArrVar()) {			// Arr
		biR += arrVarMap[this->right->getName()][this->right->getIndex(numVarMap, arrVarMap)];
	} else if (this->right->checkBinary()) {	// Bi
		biR += this->right->getBinary(numVarMap, arrVarMap);
	} else {							// Num
		biR += numVarMap[this->right->getName()];
	}


	if (this->BiOperator == "+") return biL + biR;			// +

	else if (this->BiOperator == "-") return biL - biR;	// -

	else if (this->BiOperator == "*") return biL * biR;	// *

	else if (this->BiOperator == "/") {													// /
		if (abs(biR) < 1) {	
			string errorMsg = "Division by 0: " + this->left->format() + " = " + to_string(biL) +
							", " + this->right->format() + " = " + to_string(biR);
			throw logic_error(errorMsg);
		} else {
			return floor(biL / biR);
		}
	} else {
		throw runtime_error("Binary Operator not recognized.");
	}

	return -9999; // never reached
}


bool BinaryExpression::checkArrVar() {
	return false;
}

bool BinaryExpression::checkBinary() {
	return true;
}

string BinaryExpression::format() const {
    return "(" + this->left->format() + " " + this->BiOperator + " " + this->right->format() + ")";
}

int BinaryExpression::getIndex(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
	return -1; // never called
}
