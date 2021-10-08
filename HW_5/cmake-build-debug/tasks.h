//
// Created by aspdr on 10/7/2021.
//

#pragma once

#include <iterator>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <map>
#include <algorithm>

// task one function: create a template function that takes begin and end of sequence iterators
// and prints the list of all unique words in this sequence
// solution 1:
template<typename iter>
void PrintUnique(const iter& begin, const iter& end) {
    auto new_end = std::unique(begin, end);
    auto print = [&](auto val) {
        std::cout << val << std::endl;
    };
    std::for_each(begin, new_end, print);
}
// solution 2:
template<typename iter>
void PrintUniqueSet(const iter& begin, const iter& end) {
    std::unordered_set<typename std::iterator_traits<iter>::value_type> sorted_words {begin, end};
    auto print = [&](auto const& item) {
        std::cout << item << " ";
    };
    for_each(sorted_words.begin(), sorted_words.end(), print);
}

// task two function:
// solution 1:
//std::multimap<int, std::string> StringToMap(std::string s) {
//    std::multimap<int, std::string> sentences;
//    std::string buf;
//    auto it {s.begin()};
//    while (*std::next(it++) != EOF) {
//        int words = 0;
//        size_t pos = s.find_first_of('.');
//        buf = s.substr(0, pos);
//        s.erase(0, pos + 1);
//        for_each(buf.begin(), buf.end(), [&](char& c) {
//            if (c == ' ' || c == ',' || c == '\n' || c == '\0')
//                ++words;
//        });
//        sentences.insert({words, buf});
//    }
//    return sentences;
//}

std::multimap<int, std::string> StringToMap2() {
    std::string word;
    std::string sentence;
    std::multimap<int, std::string> sentences;
    while (std::cin >> word) {
        if (word.back() != '.' || word.back() != '!' || word.back() != '?') {
            sentence.append(word);
            sentence.push_back(' ');
        }
        if (*(sentence.end() - 2) == '.' || *(sentence.end() - 2) == '!' ||
            *(sentence.end() - 2) == '?') {
            sentence.pop_back();
            int words = count(sentence.begin(), sentence.end(), ' ') + 1;
            sentences.insert({words, sentence});
            sentence.clear();
        }
    }
    return sentences;
}