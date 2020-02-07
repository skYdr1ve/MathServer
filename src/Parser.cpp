#include "Parser.h"

std::shared_ptr<Value> Parser::Calculate(std::queue<std::shared_ptr<Node>> input) {
	auto CalculateOp = [](int _op, std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
		if (_op == 0) {
			return std::make_shared<Value>(left->Evaluate() * right->Evaluate());
		}
		else if (_op == 1) {
			return std::make_shared<Value>(left->Evaluate() / right->Evaluate());
		}
		else if (_op == 2) {
			return std::make_shared<Value>(left->Evaluate() + right->Evaluate());
		}
		else if (_op == 3) {
			return std::make_shared<Value>(left->Evaluate() - right->Evaluate());
		}
		else if (_op == 4) {
			return std::make_shared<Value>(pow(left->Evaluate(), right->Evaluate()));
		}
		return std::make_shared<Value>(0);
	};

	auto SignInt = [](int sign) {
		if (sign == 0) {
			return "*";
		}
		else if (sign == 1) {
			return "/";
		}
		else if (sign == 2) {
			return "+";
		}
		else if (sign == 3) {
			return "-";
		}
		else if (sign == 4) {
			return "^";
		}
	};

	std::stack<std::shared_ptr<Value>> values;
	int result;
	while (!input.empty()) {
		auto el = input.front();

		input.pop();
		if (el->type == "value") {
			std::cout << el->Evaluate() << " ";
			values.push(std::make_shared<Value>(el->Evaluate()));
		}
		else if (el->type == "op") {
			std::cout << SignInt(el->Evaluate());
			auto v1 = values.top();
			values.pop();
			auto v2 = values.top();
			values.pop();
			values.push(CalculateOp(el->Evaluate(), v2, v1));
		}
	}
	std::cout << std::endl;
	return values.top();
}