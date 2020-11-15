#include <iostream>
#include <iomanip>  

#include "Matrix.h"

using namespace std;


Matrix::Matrix(int n) {
    if (n < 2) throw MatrixException();
    this->Mn = n;
    matrix = new double* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(int n, double* arr) {
    if (n < 2) throw MatrixException();
    this->Mn = n;
    matrix = new double* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = arr[i * Mn + j];
        }
    }
}

Matrix::Matrix(const Matrix& mat) {
    this->Mn = mat.Mn;
    matrix = new double* [Mn];
    for (int i = 0; i < Mn; ++i) {
        matrix[i] = new double[Mn];
        for (int j = 0; j < Mn; ++j) {
            matrix[i][j] = mat.matrix[i][j];
        }
    }
}

Matrix Matrix::operator * (const Matrix& mat) const {
    Matrix multMatrix(this->Mn);
    for (int i = 0; i < this->Mn; i++) {
        for (int j = 0; j < this->Mn; j++) {
            int newVal = 0;
            for (int k = 0; k < this->Mn; k++) {
                newVal += this->matrix[i][k] * mat.matrix[k][j];
            }
            multMatrix.matrix[i][j] = newVal;
        }
    }
    return multMatrix;
}

Matrix Matrix::operator * (const double& num) const {
    Matrix multMatrix(this->Mn);
    for (int i = 0; i < this->Mn; i++) {
        for (int j = 0; j < this->Mn; j++) {
            multMatrix.matrix[i][j] = this->matrix[i][j]*num;
        }
    }
    return multMatrix;
}

Matrix Matrix::operator + (const Matrix& mat) const {
    Matrix addMatrix(this->Mn);
    for (int i = 0; i < this->Mn; i++) {
        for (int j = 0; j < this->Mn; j++) {
            addMatrix.matrix[i][j] = mat.matrix[i][j] + this->matrix[i][j];
        }
    }
    return addMatrix;
}

Matrix Matrix::operator -() const {
    Matrix negMatrix(this->Mn);
    for (int i = 0; i < this->Mn; i++) {
        for (int j = 0; j < this->Mn; j++) {
            negMatrix.matrix[i][j] = -this->matrix[i][j];
        }
    }
    return negMatrix;
}

Matrix Matrix::operator - (const Matrix& mat) const {
    return *this + -mat;
}



ostream& operator <<(ostream& out, const Matrix& mat)
{
    for (int i = 0; i < mat.Mn; i++) {
        for (int j = 0; j < mat.Mn; j++) {
            cout << setw(3) << mat.matrix[i][j] << " ";
        }
        cout << endl;
    }
    return out;
}

double Matrix::det() {
    double det = 0;
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < this->Mn; j++) {
            if (this->Mn > 2) {
                double* arr = new double[this->Mn * this->Mn - 2 * this->Mn + 1];
                for (int k = 1; k < this->Mn; k++) {
                    int arrCounter = 0;
                    for (int l = 0; l < this->Mn; l++) {
                        if (l != j) {
                            arr[(k - 1) * (this->Mn - 1) + arrCounter] = matrix[k][l];
                            arrCounter++;
                        }
                    }
                }
                Matrix a(this->Mn - 1, arr);
                det = j % 2 == 0 ? det + matrix[i][j] * a.det() : det - matrix[i][j] * a.det();
                delete[] arr;
            }
            else if (this->Mn == 2){
                det += matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
                return det;
            }
        }
    }
    return det;
}

Matrix Matrix::transp() {
    Matrix tMatrix(this->Mn);
    for (int i = 0; i < this->Mn; i++) {
        for (int j = 0; j < this->Mn; j++) {
            tMatrix.matrix[j][i] = this->matrix[i][j];
        }
    }
    return tMatrix;
}

Matrix Matrix::invert() {
    Matrix minorMatrix(this->Mn);
    double det = this->det();
    double mDet;
    if (det) {
        for (int i = 0; i < this->Mn; i++) {
            for (int j = 0; j < this->Mn; j++) {
                if (this->Mn > 2) {
                    double* arr = new double[this->Mn * this->Mn - 2 * this->Mn + 1];
                    int row = 0;
                    for (int k = 0; k < this->Mn; k++) {
                        int col = 0;
                        for (int l = 0; l < this->Mn; l++) {
                            if (l != j && k != i) {
                                arr[row * (this->Mn - 1) + col] = matrix[k][l];
                                col++;
                            }
                        }
                        row += col / int(this->Mn - 1);
                    }
                    Matrix a(this->Mn - 1, arr);
                    mDet = (j + i) % 2 == 0 ? a.det() : -a.det();
                    minorMatrix.matrix[i][j] = mDet/det;
                    delete[] arr;
                }
                else {
                    mDet = (j + i) % 2 == 0 ? matrix[(i + 1) % 2][(j + 1) % 2] : -matrix[(i + 1) % 2][(j + 1) % 2];
                    minorMatrix.matrix[i][j] = mDet / det;
                }
            }
        }
        return minorMatrix.transp();
    }
    else throw MatrixException();
}

bool Matrix::isInvertible() {
    if (this->det() == 0) return false;
    else return true;
}

double* Matrix::findSolutions(double* constValArr) {
    double* solutions = new double[this->Mn];
    double solution;
    for (int i = 0; i < this->Mn; i++) {
        solution = 0;
        for (int j = 0; j < this->Mn; j++) {
            solution += this->matrix[i][j]*constValArr[j];
        }
        solutions[i] = solution;
    }
    return solutions;
}