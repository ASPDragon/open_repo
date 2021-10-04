#pragma once

#include <vector>
#include <iostream>
#include <cmath>

typedef struct {
    int y;
    int x;
} Coords;

constexpr int SIZE = 3;

class Matrix {
public:
    Matrix(std::vector<int>&& matr);

    void PrintMatrix();

    int GetElement(std::vector<int>&& matr, Coords coord) const;

    void GetCoFact(std::vector<int>&& matr, std::vector<int>&& temp, Coords coord, int n);

    int CalcDeterminant(std::vector<int>&& matr, int n);

    void PrintResult();

private:
    std::vector<int> matrix;
    Coords coord;
};
