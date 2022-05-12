#include "command.h"

using namespace std;

	// PRINT

Print::Print(Line* l, NumericExpression *n) : line(l), nexp(n) {

}

Print::~Print() {
	delete this->line;
	delete this->nexp;
}

void Print::Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s) {
	if (this->nexp->checkArrVar()) {		// ArrVar
		if ( arrVarMap.find(this->nexp->getName()) == arrVarMap.end() ) {	// NOT found and insert
			cout << 0 << endl;
		} else {	// found 
			cout << arrVarMap[this->nexp->getName()][this->nexp->getIndex(numVarMap, arrVarMap)] << endl;
		}
		
	} else if (this->nexp->checkBinary()) {// Binary
		cout << this->nexp->getBinary(numVarMap, arrVarMap) << endl;

	} else {								// NumVar
		if ( numVarMap.find(this->nexp->getName()) == numVarMap.end() ) {	// NOT found and insert
			cout << 0 << endl;
		} else {	// found 
			cout << numVarMap[this->nexp->getName()] << endl;
		}
	}
}

int Print::getLine() {
	return this->line->get();
}

int Print::getJline() {
	return -1;
}

string Print::format() const {
    return this->line->format() + " PRINT " + this->nexp->format() + "\n";
}

	// LET

Let::Let(Line *l, NumericExpression *n1, NumericExpression *n2) : line(l), nexp1(n1), nexp2(n2) {

}

Let::~Let() {
	delete this->line;
	delete this->nexp1;
	delete this->nexp2;
}

void Let::Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s) {
	int rVal;
	if (this->nexp2->checkArrVar()) {	// ArrVar
		rVal = arrVarMap[this->nexp2->getName()][this->nexp2->getIndex(numVarMap, arrVarMap)];
	} else if (this->nexp2->checkBinary()) {
		rVal = this->nexp2->getBinary(numVarMap, arrVarMap);
	} else {							// NUmVar
		rVal = this->nexp2->get();
	}

	if (this->nexp1->checkArrVar()) {	// ArrVar
		if ( arrVarMap.find(this->nexp1->getName()) == arrVarMap.end() ) {	// NOT found and insert

			arrVarMap[this->nexp1->getName()][this->nexp1->getIndex(numVarMap, arrVarMap)] = rVal;

		} else {	// found 

			arrVarMap[this->nexp1->getName()][this->nexp1->getIndex(numVarMap, arrVarMap)] = rVal;
			//cerr << "arrVarmap = " << arrVarMap["A"]->getByIndex(10);		
		}
	} else {							// NUmVar
		if ( numVarMap.find(this->nexp1->getName()) == numVarMap.end() ) {	// NOT found and insert

			numVarMap.insert({this->nexp1->getName(), rVal});

		} else {	// found 
			numVarMap[this->nexp1->getName()] = rVal;
		}
	}
}

int Let::getLine() {
	return this->line->get();
}

int Let::getJline() {
	return -1;
}

string Let::format() const {
    return this->line->format() + " LET " + this->nexp1->format() + " " + this->nexp2->format() + "\n";
}


	// Goto

Goto::Goto(Line *l, Line *j) : line(l), jline(j) {

}

Goto::~Goto() {
	delete this->line;
	delete this->jline;
}

void Goto::Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s) {
	// check error if no jline
	// then start executing at jline
	if ( cmdMap.find(this->jline->get()) == cmdMap.end() ) {	// NOT found and throw error
		throw invalid_argument("GOTO to non-existent line");
	} else {	// found 
		map<int, Command*>::iterator tempIt = cmdMap.begin();
		while(tempIt != cmdMap.end()) {
			if(tempIt->second->getLine() == this->jline->get()) {
				tempIt--;
				it = tempIt; // this is bc the FOR loop in EXECUTE! part increaments it at the end.
				return;
			}

			tempIt++;
		}
	}
}


int Goto::getLine() {
	return this->line->get();
}

int Goto::getJline() {
	return this->jline->get();
}

string Goto::format() const {
    return this->line->format() + " GOTO <" + this->jline->format() + ">" + "\n";
}

	// IfThen <LINE> IF <BEXP> THEN <JLINE>

IfThen::IfThen(Line *l, BooleanExpression *b, Line *j) : line(l), boolExp(b), jline(j) {

}

IfThen::~IfThen() {
	delete this->line;
	delete this->boolExp;
	delete this->jline;
}

void IfThen::Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s) {
	if (this->boolExp->compare(numVarMap, arrVarMap)) {	// true
		// check error if no jline
		// start executing at jline
		if ( cmdMap.find(this->jline->get()) == cmdMap.end() ) {	// NOT found and throw error
			throw invalid_argument("IF jump to non-existent line");
		} else {	// found 
			map<int, Command*>::iterator tempIt = cmdMap.begin();
			while(tempIt != cmdMap.end()) {
				if(tempIt->second->getLine() == this->jline->get()) {
					tempIt--;
					it = tempIt; // this is bc the FOR loop in EXECUTE! part increaments it at the end.
					return;
				}

				tempIt++;
			}
		}
	} else {
		// boolExp is flase, do nothing and continue execute next line
	}
}

int IfThen::getLine() {
	return this->line->get();
}

int IfThen::getJline() {
	return this->jline->get();
}


string IfThen::format() const {
    return this->line->format() + " IF " + this->boolExp->format() + " THEN <" + this->jline->format() + ">" + "\n";
}

	// GOSUB

Gosub::Gosub(Line *l, Line *j) : line(l), jline(j) {

}

Gosub::~Gosub() {
	delete this->line;
	delete this->jline;
}

void Gosub::Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s) {
	// check error if no jline
	// remember line and start executing at jline
	if ( cmdMap.find(this->jline->get()) == cmdMap.end() ) {	// NOT found and throw error
			throw invalid_argument("GOSUB to non-existent line");
	} else {	// found 
		s.push(this->line->get());
		map<int, Command*>::iterator tempIt = cmdMap.begin();
			while(tempIt != cmdMap.end()) {
				if(tempIt->second->getLine() == this->jline->get()) {
					tempIt--;
					it = tempIt; // this is bc the FOR loop in EXECUTE! part increaments it at the end.
					return;
				}

				tempIt++;
			}
	}
	// assign bline for RETURN

	// it->second->bline->write(this->line->get());
}

int Gosub::getLine() {
	return this->line->get();
}

int Gosub::getJline() {
	return this->jline->get();
}

string Gosub::format() const {
    return this->line->format() + " GOSUB <" + this->jline->format() + ">" + "\n";
}


	// RETURN

Return::Return(Line *l) : line(l) {
	
}

Return::~Return() {
	delete this->line;
	delete this->bline;
}

void Return::Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s) {
	// check error if no gosub
	// start executing from bline
	if(s.empty()) {
		throw out_of_range("No matching GOSUB for RETURN.");
	} else {
		int b = s.top();
		s.pop();
		map<int, Command*>::iterator tempIt = cmdMap.begin();

		while(tempIt != cmdMap.end()) {
			if(b == tempIt->first) {	// found back line b
				it = tempIt; // this is bc the FOR loop in EXECUTE! part increaments it at the end.
				return;
			}

			tempIt++;
		}
	}	
}

int Return::getLine() {
	return this->line->get();
}

int Return::getJline() {
	return -1;
}

string Return::format() const {
    return this->line->format() + " RETURN" + "\n";
}

	// END


End::End(Line *l) : line(l) {

}

End::~End() {
	delete this->line;
}

void End::Do(map<int, Command*> &cmdMap, map<int, Command*>::iterator &it,
		map<string, int> &numVarMap, map<string, map<int, int>> &arrVarMap, stack<int> &s) {
	exit(0);
}

int End::getLine() {
	return this->line->get();
}

int End::getJline() {
	return -1;
}

string End::format() const {
    return this->line->format() + " END" + "\n";
}
