#pragma once
#ifndef _MATRIX_H
#define _MATRIX_H

#include <iostream>

using namespace std;

class MatrixException {};

class Matrix
{
private:
    double** matrix;
    int Mn;

public:
    Matrix(int n);

    Matrix(int n, double* arr);

    Matrix(const Matrix& mat);

    ~Matrix() {
        for (int i = 0; i < Mn; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }


    double det();
    bool isInvertible();
    Matrix transp();
    Matrix invert();
    double* findSolutions(double* costValArr);

    Matrix operator * (const Matrix& num) const;
    Matrix operator * (const double& num) const;
    Matrix operator + (const Matrix& num) const;
    Matrix operator -() const;
    Matrix operator - (const Matrix& num) const;

    friend ostream& operator <<(ostream& out, const Matrix& mat);

};

#endif

