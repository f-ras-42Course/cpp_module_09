#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const std::string& dataFile) {
	loadExchangeRates(dataFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	exchangeRates = other.exchangeRates;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		exchangeRates = other.exchangeRates;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::loadExchangeRates(const std::string& dataFile) {
	std::ifstream file(dataFile.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open data file.");
	}
	
	std::string line;
	std::getline(file, line); // Skip header line
	
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date, rateStr;
		
		if (std::getline(iss, date, ',') && std::getline(iss, rateStr)) {
			float rate = std::atof(rateStr.c_str());
			exchangeRates[date] = rate;
		}
	}
	file.close();
}

void BitcoinExchange::processInputFile(const std::string& inputFile) {
	std::ifstream file(inputFile.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open input file." << std::endl;
		return;
	}
	
	std::string line;
	std::getline(file, line); // Skip header line
	
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date, valueStr;

		if (std::getline(iss, date, '|') && std::getline(iss, valueStr)) {
			trimWhitespace(date);
			trimWhitespace(valueStr);

			if (!isValidDate(date)) {
				std::cerr << "Error: bad input => " << date << std::endl;
				continue;
			}

			float value;
			if (!isValidValue(valueStr, value)) {
				continue;
			}

			try {
				float rate = getExchangeRate(date);
				float result = value * rate;
				std::cout << date << " => " << value << " = " << result << std::endl;
			} catch (const std::runtime_error& e) {
				std::cerr << "Error: no exchange rate available for " << date << std::endl;
			}

		} else {
			std::cerr << "Error: bad input => " << line << std::endl;
		}
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
		return false;
	}

	int year, month, day;
	parseDate(date, year, month, day);

	if (!isValidMonth(month)) {
		return false;
	}

	return day <= daysInMonth(year, month);
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) {
	char* endptr;
	errno = 0;
	value = std::strtof(valueStr.c_str(), &endptr);
	
	if (errno != 0 || *endptr != '\0' || endptr == valueStr.c_str()) {
		std::cerr << "Error: not a number." << std::endl;
		return false;
	}
	
	if (value < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	
	if (value > 1000) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	
	return true;
}

float BitcoinExchange::getExchangeRate(const std::string& date) {
    auto it = exchangeRates.find(date);
    if (it != exchangeRates.end()) {
        return it->second;
    }
    return findClosestEarlierRate(date);
}

float BitcoinExchange::findClosestEarlierRate(const std::string& date) {
    auto it = exchangeRates.lower_bound(date);
    if (it == exchangeRates.begin()) {
		throw std::runtime_error("No earlier date available");
    }
    --it;
    return it->second;
}

// - Utils -

void trimWhitespace(std::string& str) {
	str.erase(0, str.find_first_not_of(" \t"));
	str.erase(str.find_last_not_of(" \t") + 1);
}

bool isLeapYear(int year) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysInMonth(int year, int month) {
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (isLeapYear(year)) {
		daysInMonth[1] = LEAP_YEAR_FEBRUARY;
	}
	return daysInMonth[month - 1];
}

bool isValidMonth(int month) {
	return month >= 1 && month <= 12;
}

void parseDate(const std::string& date, int& year, int& month, int& day) {
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
}