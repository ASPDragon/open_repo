//
// Created by aspdr on 10/16/2021.
//

#include "StudentsGroup.h"

void StudentsGroup::Open(std::string filename) {
    std::ifstream in(filename, std::ios_base::binary);
    size_t size = 0;

    while (size--) {
        foo::bar::Student student;
        student.ParseFromIstream(&in);
        _students.push_back(std::move(student));
    }
    in.close();
}

void StudentsGroup::Save() {
    std::ofstream out("students_something2.bin", std::ios_base::binary);

    for (auto& student : _students) {
        student.SerializePartialToOstream(&out);
    }
    out.close();
}

void StudentsGroup::Push(foo::bar::Student&& student) {
    _students.push_back(student);
}

double StudentsGroup::GetAverageScore(const foo::bar::FullName& rhs) {
    auto student = [&](const foo::bar::Student& lhs) {
        return std::tie(lhs.full_name().name(), lhs.full_name().surname(), lhs.full_name().patronimic()) ==
               std::tie(rhs.name(), rhs.surname(), rhs.patronimic());
    };
    auto iter { std::find_if(_students.begin(), _students.end(), student) };
    return iter->gpa();
}

std::string StudentsGroup::GetAllInfo(const foo::bar::FullName& rhs) {
    std::string information;
    auto student = [&](const foo::bar::Student& lhs) {
        return std::tie(lhs.full_name().name(), lhs.full_name().surname(), lhs.full_name().patronimic()) ==
               std::tie(rhs.name(), rhs.surname(), rhs.patronimic());
    };
    auto iter = std::find_if(_students.begin(), _students.end(), student);
    information.append(iter->full_name().name());
    information.push_back(' ');
    information.append((iter->full_name().has_patronimic() ? iter->full_name().patronimic() : ""));
    information.push_back(' ');
    information.append(iter->full_name().surname());
    information.push_back('\t');
    for (const auto& g : iter->grades()) {
        information.append(std::to_string(g));
        information.push_back(' ');
    }
    information.push_back('\t');
    information.append(std::to_string(iter->gpa()));
    return information;
}

std::string StudentsGroup::GetAllInfo() {
    std::string information;
    auto iter { _students.begin() };
    while (iter != _students.end()) {
        information.append(GetAllInfo(iter->full_name()));
        information.push_back('\n');
        iter++;
    }
    return information;
}