#pragma once

#include <fstream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include "Person.hpp"
#include "PhoneNumber.hpp"

class PhoneBook {
public:
    PhoneBook(std::ifstream& file);

    ~PhoneBook();

    void FileToObj(std::ifstream& file);

    bool ComparePersons(std::pair<Person, PhoneNumber> person1, std::pair<Person, PhoneNumber> person2);

    void SortByName();

    void SortByPhone();

    std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& surname);

    void ChangePhoneNumber(const Person& person, PhoneNumber number);

    friend std::ostream& operator<< (std::ostream& out, PhoneBook& book);

    

private:
    std::string string;
    std::vector<std::pair<Person, PhoneNumber>> phone_book;
};