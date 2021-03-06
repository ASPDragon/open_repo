#pragma once

#include <tuple>
#include <optional>
#include <iostream>
#include <string>
#include <sstream>

#define ONE 1

class Person {
public:
    Person();

    // Person(std::string l_name, std::string f_name);

    Person(std::string l_name, std::string f_name, std::string patr);

    std::string GetFirstName() const;

    std::optional<std::string> GetPatronimic() const;

    std::string GetLastName() const;

    static Person ReadFromStream(std::istringstream& iss);

    void SetPerson(std::istringstream& iss);

    friend std::ostream& operator<< (std::ostream& out, const Person& person);

    friend bool operator< (const Person& p1, const Person& p2);

    friend bool operator== (const Person& p1, const Person& p2);

private:
    std::string last_name;
    std::string first_name;
    std::optional<std::string> patronimic;
};