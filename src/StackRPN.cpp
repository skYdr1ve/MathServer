#include "StackRPN.h"

StackRPN::StackRPN() : bracket_count(0){}

void StackRPN::push(std::shared_ptr<Op> _op, std::queue<std::shared_ptr<Node>>& output) {
	if (_op->GetOp() == '(') {
		bracket_count++;
	}
	else if (_op->GetOp() == ')') {
		bracket_count--;
		if (bracket_count < 0) {
			return;
		}
		while (!stack_op.empty()) {
			if (stack_op.top()->GetOp() != '(') {
				output.push(stack_op.top());
				stack_op.pop();
			}
			else {
				stack_op.pop();
				break;
			}
		}
		return;
	}
	stack_op.push(_op);
}