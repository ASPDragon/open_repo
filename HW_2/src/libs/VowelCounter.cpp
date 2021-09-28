#include "VowelCounter.hpp"

VowelCounter::VowelCounter(std::ifstream& file) {
    vowels1 = vowels2 = vowels3 = vowels4 = 0;
    str = "The number of vowels in this book is: ";
    Timer timer1("std::string::find + std::count_if");
    while (!file.eof()) {
        std::getline(file, Book);
        vowels1 += CountVow1(Book);
    }
    timer1.print();
    getVow1();
    Book.clear();
    file.seekg(0, file.beg);

    Timer timer2("for + count_if");
    while (!file.eof()) {
        std::getline(file, Book);
        vowels2 += CountVow2(Book);
    }
    timer2.print();
    getVow2();
    Book.clear();
    file.seekg(0, file.beg);

    Timer timer3("find + for");
    while (!file.eof()) {
        std::getline(file, Book);
        vowels3 += CountVow3(Book);
    }
    timer3.print();
    getVow3();
    Book.clear();
    file.seekg(0, file.beg);

    Timer timer4("double for");
    while (!file.eof()) {
        std::getline(file, Book);
        vowels4 += CountVow4(Book);
    }
    timer4.print();
    getVow4();
    Book.clear();
    file.seekg(0, file.beg);

    Timer timer5("WTF?");
    while (!file.eof()) {
        std::getline(file, Book);
        vowels5 += CountVow5(Book);
    }
    timer5.print();
    getVow5();
    Book.clear();
}

void VowelCounter::getVow1() {
    std::cout << str << vowels1 << std::endl;
}

void VowelCounter::getVow2() {
    std::cout << str << vowels2 << std::endl;
}

void VowelCounter::getVow3() {
    std::cout << str << vowels3 << std::endl;
}

void VowelCounter::getVow4() {
    std::cout << str << vowels4 << std::endl;
}

void VowelCounter::getVow5() {
    std::cout << str << vowels5 << std::endl;
}

int VowelCounter::CountVow1(std::string& str) {
    std::string vowels = "AEIOUaeiou";
    auto isVowel = [&vowels](const char character) {
        return vowels.find(character) != std::string::npos;
    };
    return count_if(str.cbegin(), str.cend(), isVowel);
}

int VowelCounter::CountVow2(std::string& str) {
    std::string vowels = "AEIOUaeiou";
    auto isVowel = [&vowels](const char character) {
        for (auto& item : vowels)
            if (character == item) {
                return true;
            }
        return false;
    };
    return count_if(str.cbegin(), str.cend(), isVowel);
}

int VowelCounter::CountVow3(std::string& str) {
    std::string vowels = "AEIOUaeiou";
    auto isVowel = [&vowels](const char character) {
        return vowels.find(character) != std::string::npos;
    };
    int count = 0;
    for (auto& item : str)
        if (isVowel(item)) count++;
    return count;
}

int VowelCounter::CountVow4(std::string& str) {
    std::string vowels = "AEIOUaeiou";
    auto isVowel = [&vowels](const char character) {
        for (auto& item : vowels)
            if (character == item) {
                return true;
            }
        return false;
    };
    int count = 0;
    for (auto item : str)
        if (isVowel(item)) count++;
    return count;
}

int VowelCounter::CountVow5(const std::string& str) {
    auto isVowel = [](const char character) {
        return character == 'A' || character == 'E' || character == 'I' ||
               character == 'O' || character == 'U' || character == 'a' ||
               character == 'e' || character == 'i' || character == 'o' ||
               character == 'u';
    };
    int count = 0;
    for (int i = 0; i < str.size(); ++i)
        if (isVowel(str[i])) count++;
    return count;
}