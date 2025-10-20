#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define LEAP_YEAR_FEBRUARY 29

class BitcoinExchange {
public:
	BitcoinExchange();
	BitcoinExchange(const std::string& dataFile);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();
	void processInputFile(const std::string& inputFile);

private:
	std::map<std::string, float> exchangeRates;
	void loadExchangeRates(const std::string& dataFile);
	bool isValidDate(const std::string& date);
	bool isValidValue(const std::string& valueStr, float& value);
	float getExchangeRate(const std::string& date);
	float findClosestEarlierRate(const std::string& date);
};

// - Utils -

// Trims leading and trailing whitespace from a string
void trimWhitespace(std::string& str);

// Returns true if year is a leap year
bool isLeapYear(int year);

// Returns number of days in a given month of a given year
int daysInMonth(int year, int month);

// Returns true if date is in YYYY-MM-DD format and is a valid date
bool isValidDate(const std::string& date);

// Returns true if month is out of range (1-12)
bool isValidMonth(int month);

// Parses date string in YYYY-MM-DD format into year, month, and day integers
void parseDate(const std::string& date, int& year, int& month, int& day);


#endif
