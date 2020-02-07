#include "Op.h"

Op::Op(char value)
	: precedence([value] {
	if (value == '^') {
		return 4;
	}
	else if (value == '*' || value == '/') {
		return 3;
	}
	else if (value == '+' || value == '-') {
		return 2;
	}
	else if (value == '(' || value == ')') {
		return 1;
	}
}()),
op(value), Node("op") {}

void Op::SetNods(Value& _left, Value& _right) {
	left = &_left;
	right = &_right;

}

int Op::Evaluate() const {
	if (op == '*') {
		return 0;
	}
	else if (op == '/') {
		return 1;
	}
	else if (op == '+') {
		return 2;
	}
	else if (op == '-') {
		return 3;
	}
	else if (op == '^') {
		return 4;
	}
	return 0;
}

const char Op::GetOp() const {
	return op;
}