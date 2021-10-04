#include "Matrix.hpp"

Matrix::Matrix(std::vector<int>&& matr)
    : matrix(std::move(matr)) {}

void Matrix::PrintMatrix() {
    for (int y { 0 }; y < SIZE; ++y) {
        for (int x{ 0 }; x < SIZE; ++x) {
            std::cout << matrix[y * sqrt(matrix.size()) + x] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Matrix::GetElement(std::vector<int>&& matr, Coords coord) const {
    return matr[coord.y * sqrt(matr.size()) + coord.x];
}

void Matrix::GetCoFact(std::vector<int>&& matr, std::vector<int>&& temp, Coords coord, int n) {
    int i { 0 }, j { 0 };

    for (int row { 1 }; row < n; ++row) { // traverse through the matrix, writing elements that not from
        for (int col { 0 }; col < n; ++col) { // y-row and x-col to the temporary matrix
            if (row != coord.y && col != coord.x) {
                temp[i * (n - 1) + j] = matr[row * n + col];
                j++;
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int Matrix::CalcDeterminant(std::vector<int>&& matr, int n) {
    int D { 0 };

    if (n == 1)
        return GetElement(std::move(matr), { 0, 0 });

    std::vector<int> temp;
    temp.resize(pow(n, 2));

    for (int iter { 0 }; iter < n; ++iter) {
        GetCoFact(std::move(matr), std::move(temp), { 0, iter }, n);
        D += pow(-1, iter) * matr[iter] * CalcDeterminant(std::move(temp), n - 1); // Laplace recursive function. pow(-1 , 1) == -1, pow(-1, 2) == 1 etc
    }
    return D;
}

void Matrix::PrintResult() {
    std::cout << "The determinant of the matrix is: " << CalcDeterminant(std::move(matrix), SIZE) << std::endl;
}
