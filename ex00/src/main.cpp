#include "BitcoinExchange.hpp"

int main()
{
	try {
		BitcoinExchange exchange("data.csv");
		exchange.processInputFile("input.txt");
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return 0;
}
