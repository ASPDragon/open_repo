#pragma once
#include <iostream>
#include <random>

template<typename T>
void fillRandT(T& container) {
    std::random_device random;
    std::mt19937_64 mt {random()};
    std::uniform_int_distribution<int> dist {0, 100};
    auto gen = [&]() {return dist(mt); };
    std::generate(container.begin(), container.end(), gen);
}

template<typename T>
void fillRandTDbl(T& container) {
    std::random_device random;
    std::mt19937_64 mt {random()};
    std::uniform_real_distribution dist {0.0, 1000.0};
    auto gen = [&]() {return dist(mt); };
    std::generate(container.begin(), container.end(), gen);
}

template<typename T>
void insert_sorted(T& container, typename T::value_type const&& val) {
    auto iter = lower_bound(container.begin(), container.end(), val);
    container.insert(iter, val);
}

template<typename T>
void printContainerT(T const& container) {
    for (auto& iter : container) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}
