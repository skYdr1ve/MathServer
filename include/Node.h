#pragma once
#include <string>

class Node {
public:
	Node();
	Node(std::string _type);

	virtual int Evaluate() const = 0;
	std::string type;
};

