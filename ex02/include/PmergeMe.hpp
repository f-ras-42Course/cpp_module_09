#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include "FordJohnson.hpp"
#include <chrono>
#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <climits>

class PmergeMe {
private:
    std::vector<int> vec;
    std::deque<int> deq;
    double vecTime;
    double deqTime;
    
    void parseInput(int argc, char** argv);
    int validateAndConvert(const char* str) const;
    void printUnsorted() const;
    void printSorted() const;
    void printTimes() const;
    
    template <typename Container>
    void printContainer(const Container& container) const;

public:
    PmergeMe(int argc, char** argv);
    void sort();
    void printResults() const;
};

#endif