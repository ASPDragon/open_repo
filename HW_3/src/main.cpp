#include "libs/Matrix.hpp"
#include "libs/ArrayInt.hpp"
#include "libs/Templates.hpp"

void TaskOne() {
    std::cout << "Task 1: Pushing an average of an integer sequence at the end of this sequence." << std::endl;
    std::list<float> list { { -10.0f, - 5.0f, -1.0f, 0.0f, 2.0f, 7.0f, 11.0f, 3.0f, 25.0f } };
    list.push_back(average(list));
    printlist(list);
}

void TaskTwo() {
    std::cout << "Task 2: Create class Matrix and implement a method that calculates a determinant." << std::endl;
    std::vector<int> matrix { 6, 1, 1, 4, -2, 5, 2, 8, 7 };
    Matrix matr(std::move(matrix));
    matr.PrintMatrix();
    matr.PrintResult();
}

void TaskThree() {
    std::cout << "Task 3: Create class Iterator and traverse the sequence with ranged for." << std::endl;
    m_vector<int> vec;
    vec.push_Back(0);
    vec.push_Back(1);
    vec.push_Back(2);
    vec.push_Back(3);
    vec.push_Back(4);
    vec.push_Back(5);
    for (int& it : vec) {
        std::cout << it << std::endl;
    }
}

int main() {
    TaskOne();
    TaskTwo();
    TaskThree();
}
