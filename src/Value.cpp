#include "Value.h"

Value::Value(int number) : value(number), Node("value") {}

int Value::Evaluate() const { 
	return value; 
}

