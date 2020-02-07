#pragma once
#include <stack>
#include <queue>
#include <memory>
#include "Op.h"

class StackRPN {
public:
	StackRPN();
	void push(std::shared_ptr<Op> _op, std::queue<std::shared_ptr<Node>>& output);
	std::stack<std::shared_ptr<Op>> stack_op;
	int bracket_count;
};

