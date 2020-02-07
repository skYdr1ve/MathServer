
#include "Parser.h"
#include "test_runner.h"

void TestParser() {
	Parser parser;
	std::string expr1 = "3+4*2/(1-5)^2^3";
	std::string expr1 = "2*(-2)";
	std::string expr1 = "1+1^2";
	std::string expr1 = "((6))-(((5)))";
	std::string expr1 = "2/2+3*2";
	std::string expr1 = "1";
	AssertEqual(parser.Parse(begin(expr1), end(expr1))->Evaluate(), 3);
	AssertEqual(parser.Parse(begin(expr1), end(expr1))->Evaluate(), -4);
	AssertEqual(parser.Parse(begin(expr1), end(expr1))->Evaluate(), 2);
	AssertEqual(parser.Parse(begin(expr1), end(expr1))->Evaluate(), 1);
	AssertEqual(parser.Parse(begin(expr1), end(expr1))->Evaluate(), 7);
	AssertEqual(parser.Parse(begin(expr1), end(expr1))->Evaluate(), 1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestParser);
}