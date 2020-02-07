#pragma once
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <cmath>
#include <cstdint>
#include <queue>
#include <cstdlib>
#include "StackRPN.h"


class Parser {
public:

	template <class Iterator>
	std::shared_ptr<Node> Parse(Iterator token, Iterator end) {
		if (token == end) {
			return std::make_shared<Value>(0);
		}
		StackRPN st = StackRPN();
		std::queue<std::shared_ptr<Node>> output;

		auto IsOperator = [](const auto& ops) {
			if (ops == '+' || ops == '-' || ops == '*' || ops == '/' || ops == '^' || ops == '(' || ops == ')') {
				return true;
			}
			return false;
		};

		auto Priority = [](const auto& ops) {
			if (ops == '^') {
				return 4;
			}
			else if (ops == '*' || ops == '/') {
				return 3;
			}
			else if (ops == '+' || ops == '-') {
				return 2;
			}
			else if (ops == '(' || ops == ')') {
				return 1;
			}
		};

		auto PopOps = [&](const auto& oper) {
			if (!st.stack_op.empty() && st.stack_op.top()->precedence >= oper->precedence && oper->GetOp() != '(') {
				auto value1 = st.stack_op.top();
				output.push(value1);
				st.stack_op.pop();
				st.push(oper, output);
			}
			else {
				st.push(oper, output);
			}
		};

		auto AllPopOps = [&]() {
			while (!st.stack_op.empty()) {
				auto value1 = st.stack_op.top();
				output.push(value1);
				st.stack_op.pop();
			}
		};

		while (token != end) {
			auto &value = *token;
			if (value >= '0' && value <= '9') {
				std::string number = "";
				number += value;
				++token;
				while (token != end) {
					auto &temp_value = *token;
					if (temp_value >= '0' && temp_value <= '9') {
						number += temp_value;
						++token;
					}
					else {
						break;
					}
				}
				output.push(std::make_shared<Value>(atoi(number.c_str())));
				continue;
			}
			else if (IsOperator(value)) {
				PopOps(std::make_shared<Op>(value));
			}
			else {
				std::cout << "не известный токен" << std::endl;
			}

			++token;
		}

		while (!st.stack_op.empty()) {
			AllPopOps();
		}
		return Calculate(output);
	}

	std::shared_ptr<Value> Calculate(std::queue<std::shared_ptr<Node>> input);

};

