//
// Created by aspdr on 10/16/2021.
//

#pragma once

#include <cstdlib>
#include <tuple>
#include <fstream>
#include <string>
#include <vector>
#include "IRepository.h"
#include "IMethods.h"


class StudentsGroup : public IRepository, public IMethods {
public:
    void Open(std::string filename) override;
    void Save() override;
    void Push(foo::bar::Student&& student);
    double GetAverageScore(const foo::bar::FullName& rhs) override;
    std::string GetAllInfo(const foo::bar::FullName& rhs) override;
    std::string GetAllInfo() override;
    std::vector<foo::bar::Student> GetStudents() const { return _students; }
private:
    std::vector<foo::bar::Student> _students;
};