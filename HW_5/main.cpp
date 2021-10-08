#include "cmake-build-debug/tasks.h"
#include <vector>
#include <list>
#include <deque>
#include <iterator>

void TaskOne() {
    std::cout << "\tTask#1:" << std::endl;
    std::cout << "vector_iterator: " << std::endl;
    std::vector<std::string> vocabulary;
    std::sort(vocabulary.begin(), vocabulary.end());
    vocabulary.push_back("the");
    vocabulary.push_back("the");
    vocabulary.push_back("red");
    vocabulary.push_back("banana");
    vocabulary.push_back("cat");
    vocabulary.push_back("Pepe");
    PrintUniqueSet(vocabulary.begin(), vocabulary.end());

    std::cout << "\nlist_iterator: " << std::endl;
    std::list<std::string> vocabulary2{ {"C", "plus", "plus", "has", "at", "least", "two", "pluses"} };
    PrintUniqueSet(vocabulary2.begin(), vocabulary2.end());

    std::cout << "\ndeque_iterator: " << std::endl;
    std::deque<std::string> vocabulary3;
    vocabulary3.push_front("C");
    vocabulary3.push_front("plus");
    vocabulary3.push_front("plus");
    vocabulary3.push_front("has");
    vocabulary3.push_front("quite");
    vocabulary3.push_front("a");
    vocabulary3.push_front("complex");
    vocabulary3.push_front("syntax");
    PrintUniqueSet(vocabulary3.begin(), vocabulary3.end());
}

void TaskTwo() {
    std::cout << "\n\tTask#2:" << std::endl;
    std::string str;
    std::multimap<int, std::string> sentences;
    std::cout << "Please, enter some text: ";
//    solution 1 (less elegant):
//    getline(std::cin, str);
//    std::multimap<int, std::string> sentences = StringToMap(str);
//    std::cout << std::endl;
//    for_each(sentences.begin(), sentences.end(), [](std::pair<int, std::string> item) {
//        std::cout << item.first << " " << item.second << std::endl;
//    });
// solution 2 (more elegant):
    sentences = StringToMap2();
    for_each(sentences.begin(), sentences.end(), [](std::pair<int, std::string> item) {
        std::cout << item.first << " " << item.second << std::endl;
    });
}

int main() {
    TaskOne();
    TaskTwo();
    return 0;
}
