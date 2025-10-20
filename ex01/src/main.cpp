#include "RPN.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <Some Polish Notation Expression>" << std::endl;
		return 1;
	}

	RPN magicMachine;
	try {
		magicMachine.makeItHappen(argv[1]);
		std::cout << "Result: " << magicMachine.getResult() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}