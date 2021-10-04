#pragma once

#include <list>
#include <iostream>

// calcualting the average of the sequence
template<typename T>
T average(std::list<T>& sequence) {
    T avg = 0;
    for (auto& iter : sequence)
        avg += iter;
    avg /= sequence.size();
    return avg;
}

// auxilary function for printing the sequence
template<typename T>
void printlist(std::list<T>& seq) {
    for (auto& iter : seq)
        std::cout << iter << " ";
    std::cout << std::endl;
}
