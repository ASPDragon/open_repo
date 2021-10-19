#include <numeric>
#include "cmake-build-debug/StudentsGroup.h"

void PrintGroup(foo::bar::StudentsGroup group) {
    for (size_t ind = 0; ind < group.student_size(); ++ind) {
        std::cout << group.student(ind).full_name().name() << ' ' << (group.student(ind).full_name().has_patronimic() ?
        group.student(ind).full_name().patronimic() : "") << ' ' << group.student(ind).full_name().surname() <<
        ". The student's gpa is: " << group.student(ind).gpa() << std::endl;
    }
}

void PrintGroup(StudentsGroup group) {
    for (const auto& student : group.GetStudents()) {
        std::cout << student.full_name().name() << ' ' << (student.full_name().has_patronimic() ?
        student.full_name().patronimic() : "") << ' ' << student.full_name().surname() <<
        ". The student's gpa is: " << student.gpa() << std::endl;
    }
}

void TaskTwo() {
    foo::bar::FullName studname1;
    studname1.set_name("Sergei");
    studname1.set_surname("Avdoshkin");
    studname1.set_patronimic("Petrovich");

    foo::bar::Student student;
    *student.mutable_full_name() = studname1;
    student.add_grades(3);
    student.add_grades(4);
    student.add_grades(5);
    student.add_grades(5);
    student.add_grades(5);
    student.add_grades(5);
    double avg = std::accumulate(student.grades().begin(), student.grades().end(), 0.0) / student.grades().size();
    student.set_gpa(avg);

    foo::bar::FullName studname2;
    studname2.set_name("Jane");
    studname2.set_surname("Doe");

    foo::bar::Student student1;
    *student1.mutable_full_name() = studname2;
    student1.add_grades(5);
    student1.add_grades(4);
    student1.add_grades(5);
    student1.add_grades(4);
    student1.add_grades(5);
    student1.add_grades(5);
    avg = std::accumulate(student1.grades().begin(), student1.grades().end(), 0.0) / student1.grades().size();
    student1.set_gpa(avg);

    foo::bar::StudentsGroup group1;
    *group1.add_student() = student;
    *group1.add_student() = student1;

    std::ofstream out("students_something.bin", std::ios_base::binary);
    group1.SerializeToOstream(&out);
    out.close();
    std::ifstream in("students_something.bin", std::ios_base::binary);
    foo::bar::StudentsGroup group2;
    group2.ParseFromIstream(&in);
    in.close();
    PrintGroup(group2);
}

void TaskThree() {
    foo::bar::FullName studname1;
    studname1.set_name("Sergei");
    studname1.set_surname("Avdoshkin");
    studname1.set_patronimic("Petrovich");

    foo::bar::Student student;
    *student.mutable_full_name() = studname1;
    student.add_grades(3);
    student.add_grades(4);
    student.add_grades(5);
    student.add_grades(5);
    student.add_grades(5);
    student.add_grades(5);
    double avg = std::accumulate(student.grades().begin(), student.grades().end(), 0.0) / student.grades().size();
    student.set_gpa(avg);

    foo::bar::FullName studname2;
    studname2.set_name("Jane");
    studname2.set_surname("Doe");

    foo::bar::Student student1;
    *student1.mutable_full_name() = studname2;
    student1.add_grades(5);
    student1.add_grades(4);
    student1.add_grades(5);
    student1.add_grades(4);
    student1.add_grades(5);
    student1.add_grades(5);
    avg = std::accumulate(student1.grades().begin(), student1.grades().end(), 0.0) / student1.grades().size();
    student1.set_gpa(avg);

    StudentsGroup studentg;
    studentg.Push(std::move(student));
    studentg.Push(std::move(student1));
    studentg.Save();

    double gpa { studentg.GetAverageScore(studname1) };
    std::string a_student { studentg.GetAllInfo(studname1) };
    std::string b_student { studentg.GetAllInfo(studname2) };
    std::string students { studentg.GetAllInfo() };

    std::cout << "The students' gpa is " << gpa << std::endl;
    double gpa2 { studentg.GetAverageScore(studname2) };
    std::cout << "The students' gpa is " << gpa2 << std::endl;
    std::cout << a_student << std::endl;
    std::cout << std::endl;
    std::cout << b_student << std::endl;
    std::cout << std::endl;
    std::cout << students << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    studentg.Open("students_something2.bin");
    std::string students2 { studentg.GetAllInfo() };
    std::cout << students2 << std::endl;
    PrintGroup(studentg);
}

int main() {
    TaskTwo();
    std::cout << std::endl;
    TaskThree();
    return 0;
}
