#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <stdexcept>
class RPN {
public:
	RPN();
	void makeItHappen(const std::string& expression);
	float getResult() const;
private:
	std::stack<float> operands;
	void processOperator(char op);
};
#endif