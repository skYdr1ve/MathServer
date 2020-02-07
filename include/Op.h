#pragma once
#include "Node.h"
#include "Value.h"

class Op : public Node {
public:
	Op(char value);

	const int precedence;

	int Evaluate() const override;

	void SetNods(Value& _left, Value& _right);

	const char GetOp() const;

private:
	const char op;
	Value* left;
	Value* right;
};
