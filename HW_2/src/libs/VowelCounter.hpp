#pragma once

#include <algorithm>
#include <fstream>
#include <sstream>
#include "Timer.hpp"

class VowelCounter {
public:
    VowelCounter(std::ifstream& file);

    int CountVow1(std::string& str);

    int CountVow2(std::string& str);

    int CountVow3(std::string& str);

    int CountVow4(std::string& str);

    int CountVow5(const std::string& str);

    void getVow1();

    void getVow2();

    void getVow3();

    void getVow4();

    void getVow5();
    
private:
    std::string Book;
    std::string str;
    int counter;
    int vowels1;
    int vowels2;
    int vowels3;
    int vowels4;
    int vowels5;
};