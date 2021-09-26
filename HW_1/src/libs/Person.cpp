#include "Person.hpp"

Person::Person()
:last_name(""), first_name(""), patronimic(std::nullopt) {}

// Person::Person(std::string l_name, std::string f_name) 
//     : last_name(l_name), first_name(f_name), patronimic(std::nullopt) {}

Person::Person(std::string l_name, std::string f_name, std::string patr)
: last_name{std::move(l_name)}, first_name{std::move(f_name)},patronimic{std::move(patr)} {}

std::string Person::GetFirstName() const {return first_name;}

std::optional<std::string> Person::GetPatronimic() const {return patronimic;}

std::string Person::GetLastName() const {return last_name;}

Person Person::ReadFromStream(std::istringstream& iss) {
    Person person;
    std::string temp;
    if (iss.peek() == ' ')
        iss.ignore(ONE);
    iss >> person.last_name >> person.first_name >> temp;
    if (temp != "-")
        person.patronimic.emplace(temp);
    return person;
}

void Person::SetPerson(std::istringstream& iss) {
    std::string temp;
    iss >> last_name >> first_name >> temp;
    if (temp == "-")
        return;
    else
        patronimic.emplace(temp);
}

std::ostream& operator<< (std::ostream& out, const Person& person) {
    out << person.last_name << ' ' << person.first_name;
    if (person.patronimic.has_value())
        out << ' ' << person.patronimic.value();
    return out;
}

bool operator< (const Person& p1, const Person& p2) {
    return std::tie(p1.last_name, p1.first_name, p1.patronimic) <
           std::tie(p2.last_name, p2.first_name, p2.patronimic);
}

bool operator== (const Person& p1, const Person& p2) {
    return std::tie(p1.last_name, p1.first_name, p1.patronimic) == 
           std::tie(p2.last_name, p2.first_name, p2.patronimic);
}