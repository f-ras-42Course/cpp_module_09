#include "RPN.hpp"

RPN::RPN() {}

void RPN::makeItHappen(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;
    while (iss >> token) {
        if (std::isdigit(token[0])) {
            operands.push(std::stof(token));
        } else if (token.length() == 1) {
            processOperator(token[0]);
        } else {
            throw std::invalid_argument(std::string("Invalid token: '") + token + "' — give some proper input.");
        }
    }
}
void RPN::processOperator(char op) {
    if (operands.size() < 2) {
        throw std::runtime_error(std::string("Insufficient operands for '") + std::string(1, op) + "' — not enough numbers to perform this trick.");
    }
    float right = operands.top(); operands.pop();
    float left = operands.top(); operands.pop();
    float result;
    switch (op) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/':
            if (right == 0) {
                throw std::runtime_error("Division by zero — attempting to split by nothing is frowned upon.");
            }
            result = left / right;
            break;
        default:
            throw std::invalid_argument(std::string("Invalid operator: '") + std::string(1, op) + "' — this symbol isn't invited to the party.");
    }
    operands.push(result);
	#ifdef VERBOSE
		std::cout << "Processed operator '" << op << "': " << left << " " << op << " " << right << " = " << result << std::endl;
	#endif
}

float RPN::getResult() const {
    if (operands.size() != 1) {
        throw std::runtime_error(std::string("Invalid RPN expression — expected 1 result on the stack, found ") + std::to_string(operands.size()) + ". The stack is confused.");
    }
    return operands.top();
}