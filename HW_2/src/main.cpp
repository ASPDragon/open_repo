#include <iostream>
#include "libs/TemplateFuncs.hpp"
#include "libs/VowelCounter.hpp"

void taskOneAndTwo() {
    int a = 10;
    int b = 3;
    int c = 125;
    int d = 0;
    int e = 42;
    int* p1 = &a;
    int* p2 = &b;
    int* p3 = &c;
    int* p4 = &d;
    int* p5 = &e;
    std::vector<int*> vec1;
    std::vector<int*> vec2;
    vec1.push_back(p1);
    vec1.push_back(p2);
    vec1.push_back(p3);
    vec1.push_back(p4);
    vec1.push_back(p5);
    vec2.push_back(p1);
    vec2.push_back(p2);
    vec2.push_back(p3);
    vec2.push_back(p4);
    vec2.push_back(p5);
    SortPointers(vec1);
    for (auto& iter : vec1) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    SortPointSTL(vec2);
    for (auto& iter : vec2) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
    for (auto& iter : vec2) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    for (auto& iter : vec2) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

void taskThree() {
    std::ifstream file("War_and_Piece.txt");
    VowelCounter vowels(file);
}

int main() {
    taskOneAndTwo();
    std::cout << "Task 3"  << std::endl;
    taskThree();
}