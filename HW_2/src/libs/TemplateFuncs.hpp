#pragma once

#include <vector>
#include <algorithm>

// Task One
template<typename T>
void Swap(T* val1, T* val2) {
    T temp = std::move(*val1);
    *val1 = std::move(*val2);
    *val2 = std::move(temp);
}

// Task Two
template<typename T>
void SortPointers(std::vector<T*>& vect) {
    for (auto& iter : vect) {
    bool atLeastOneSwapped = false;
        for (size_t j = 0; j < vect.size() - 1; ++j) {
            if (*vect[j] > *vect[j + 1]) {
                Swap(vect[j], vect[j + 1]);
                atLeastOneSwapped = true;
            }
            else
                continue;
        }
        if (!atLeastOneSwapped)
            break;
    }
}

// STL sort attempt
template<typename T>
void SortPointSTL(std::vector<T*>& vect) {
    std::sort(vect.begin(), vect.end(), [](T* a, T* b) {return a > b;});
}