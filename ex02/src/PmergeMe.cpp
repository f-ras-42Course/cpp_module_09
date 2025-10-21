#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char** argv) : vecTime(0), deqTime(0) {
    parseInput(argc, argv);
}

void PmergeMe::sort() {
    // Sort vector and measure time
    auto start = std::chrono::high_resolution_clock::now();
    fordJohnsonSort(vec);
    auto end = std::chrono::high_resolution_clock::now();
    vecTime = std::chrono::duration<double, std::micro>(end - start).count();
    
    // Sort deque and measure time
    start = std::chrono::high_resolution_clock::now();
    fordJohnsonSort(deq);
    end = std::chrono::high_resolution_clock::now();
    deqTime = std::chrono::duration<double, std::micro>(end - start).count();
}

void PmergeMe::printResults() const {
    printUnsorted();
    printSorted();
    printTimes();
}

void PmergeMe::printUnsorted() const {
    std::cout << "Before: ";
    printContainer(vec);
    std::cout << std::endl;
}

void PmergeMe::printSorted() const {
    std::cout << "After:  ";
    printContainer(vec);
    std::cout << std::endl;
}

void PmergeMe::printTimes() const {
    std::cout << "Time to process a range of " << vec.size() 
              << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() 
              << " elements with std::deque  : " << deqTime << " us" << std::endl;
}

void PmergeMe::parseInput(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        int num = validateAndConvert(argv[i]);
        vec.push_back(num);
        deq.push_back(num);
    }
}

int PmergeMe::validateAndConvert(const char* str) const {
    char* end;
    long num = std::strtol(str, &end, 10);
    
    // Check if entire string was converted
    if (*end != '\0' || end == str) {
        throw std::invalid_argument("Error: Invalid number format '" + std::string(str) + "'");
    }
    
    // Check if value is a positive integer within range
    if (num <= 0 || num > INT_MAX) {
        throw std::invalid_argument("Error: Please use positive integers. No '" + std::string(str) + "' allowed.");
    }
    
    return static_cast<int>(num);
}

template <typename Container>
void PmergeMe::printContainer(const Container& container) const {
    for (const auto& elem : container) {
        std::cout << elem << " ";
    }
}