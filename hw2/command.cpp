#include "command.h"

using namespace std;

	// PRINT

Print::Print(Line* l, NumericExpression *n) : line(l), nexp(n) {

}

Print::~Print() {
	delete this->line;
	delete this->nexp;
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

string Goto::format() const {
    return this->line->format() + " GOTO <" + this->jline->format() + ">" + "\n";
}

	// IfThen <LINE> IF <BEXP> THEN <JLINE>

IfThen::IfThen(Line *l, BooleanExpression *b, Line *j) : line(l), boolean(b), jline(j) {

}

IfThen::~IfThen() {
	delete this->line;
	delete this->boolean;
	delete this->jline;
}

string IfThen::format() const {
    return this->line->format() + " IF " + this->boolean->format() + " THEN <" + this->jline->format() + ">" + "\n";
}

	// GOSUB

Gosub::Gosub(Line *l, Line *j) : line(l), jline(j) {

}

Gosub::~Gosub() {
	delete this->line;
	delete this->jline;
}

string Gosub::format() const {
    return this->line->format() + " GOSUB <" + this->jline->format() + ">" + "\n";
}


	// RETURN

Return::Return(Line *l) : line(l) {

}

Return::Return(Line *l, Line *r) : line(l), ret(r) {	// remember where it came

}

Return::~Return() {
	delete this->line;
	delete this->ret;
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

string End::format() const {
    return this->line->format() + " END" + "\n";
}
