#pragma once
#include "Node.h"

class Value : public Node {
public:
	Value(int number);

	int Evaluate() const override;

private:
	const int value;
};
