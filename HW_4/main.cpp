#include <iostream>
#include <list>
#include <algorithm>
#include "DigitalSignalErr.hpp"

void TaskOne() {
    std::cout << "\n\tTask #1" << std::endl;
    size_t SZ = 30;
    std::cout << "std::list test: \n";
    std::list<int> lst;
    lst.resize(SZ);
    fillRandT(lst);
    lst.sort();
    printContainerT(lst);
    insert_sorted(lst, std::move(30));
    printContainerT(lst);
    std::cout << "std::vector test: \n";
    std::vector<int> vec;
    vec.resize(SZ);
    fillRandT(vec);
    std::sort(vec.begin(), vec.end());
    printContainerT(vec);
    insert_sorted(vec, std::move(30));
    printContainerT(vec);
}

void TaskTwo() {
    std::cout << "\n\tTask #2" << std::endl;
    std::vector<double> signal {10.5, 11.2, 25.1, 7.8, 3.6};
    printContainerT(signal);
    std::cout << "The error of a signal is: " << DigitalSignalErr(signal) << std::endl;
}

int main() {
    TaskOne();
    TaskTwo();
    return 0;
}
