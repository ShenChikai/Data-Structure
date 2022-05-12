#include "boolean.h"

using namespace std;

// NumExp bool

NumericBooleanExpression::NumericBooleanExpression(NumericExpression* left, string op, NumericExpression* right) : left(left), CompOperator(op), right(right) {

}

NumericBooleanExpression::~NumericBooleanExpression() {
    delete this->left;
    delete this->right;
}

bool NumericBooleanExpression::compare(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
    int biL = 0;
    int biR = 0;

    if (this->left->checkArrVar()) {            // Arr
        biL += arrVarMap[this->left->getName()][this->left->getIndex(numVarMap, arrVarMap)];
    } else if (this->left->checkBinary()) { // Bi
        biL += this->left->getBinary(numVarMap, arrVarMap);
    } else {                            // Num
        biL += numVarMap[this->left->getName()];
    }

    if (this->right->checkArrVar()) {           // Arr
        biR += arrVarMap[this->right->getName()][this->right->getIndex(numVarMap, arrVarMap)];
    } else if (this->right->checkBinary()) {    // Bi
        biR += this->right->getBinary(numVarMap, arrVarMap);
    } else {                            // Num
        biR += numVarMap[this->right->getName()];
    }

     if (this->CompOperator == "=") return (biL == biR);         // =

    else if (this->CompOperator == ">") return (biL > biR);    // >

    else if (this->CompOperator == "<") return (biL < biR);    // <

    else return -9998; // Never Reached
}

string NumericBooleanExpression::format() const {
    return "[" + this->left->format() + ' ' + CompOperator + ' ' + this->right->format() + "]";
}

// Const bool

ConstBooleanExpression::ConstBooleanExpression(int left, string op, int right) : left(left), CompOperator(op), right(right) {

}

ConstBooleanExpression::~ConstBooleanExpression() {

}

bool ConstBooleanExpression::compare(map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap) {
    if (this->CompOperator == "=") return (this->left == this->right);         // =

    else if (this->CompOperator == ">") return (this->left > this->right);    // >

    else if (this->CompOperator == "<") return (this->left < this->right);    // <

    else return -9997; // Never Reached
}

string ConstBooleanExpression::format() const {
    return "[" + to_string(left) + ' ' + CompOperator + ' ' + to_string(right) + "]";
}
