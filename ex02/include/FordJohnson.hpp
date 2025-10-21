#ifndef FORDJOHNSON_HPP
#define FORDJOHNSON_HPP

#include <vector>
#include <deque>
#include <algorithm>

// ================== Binary Insertion ==================

template <typename Container, typename Value>
void binaryInsert(Container& sorted, const Value& value) {
    sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), value), value);
}

// ================== Core Implementation ==================

template <typename Container, typename Iterator>
void fordJohnsonSortImpl(Iterator first, Iterator last) {
    size_t size = std::distance(first, last);
    
    if (size <= 1) return;
    if (size == 2) {
        if (*(first + 1) < *first)
            std::iter_swap(first, first + 1);
        return;
    }
    
    Container larger, smaller;
    if constexpr (std::is_same<Container, std::vector<typename Container::value_type>>::value) {
        larger.reserve(size / 2);
        smaller.reserve(size / 2);
    }
    
    for (auto it = first; it + 1 < last; it += 2) {
        if (*it < *(it + 1)) {
            smaller.push_back(*it);
            larger.push_back(*(it + 1));
        } else {
            smaller.push_back(*(it + 1));
            larger.push_back(*it);
        }
    }
    
    fordJohnsonSortImpl<Container>(larger.begin(), larger.end());
    
    Container result(larger.begin(), larger.end());
    if constexpr (std::is_same<Container, std::vector<typename Container::value_type>>::value) {
        result.reserve(size);
    }
    
    for (const auto& elem : smaller) {
        binaryInsert(result, elem);
    }
    
    if (size % 2 != 0) {
        binaryInsert(result, *(last - 1));
    }
    
    std::copy(result.begin(), result.end(), first);
}

// ================== Public Interface ==================

template <typename T>
void fordJohnsonSort(std::vector<T>& container) {
    fordJohnsonSortImpl<std::vector<T>>(container.begin(), container.end());
}

template <typename T>
void fordJohnsonSort(std::deque<T>& container) {
    fordJohnsonSortImpl<std::deque<T>>(container.begin(), container.end());
}

#endif