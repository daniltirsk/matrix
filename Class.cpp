#pragma once
#ifndef _MATRIX_H
#define _MATRIX_H

using namespace std;

class MatrixException {};

class Matrix
{
private:

public:
    int** matrix;
    int Mn;

    int det();
    Matrix transp();

    Matrix(int n){
        this->Mn = n;
        matrix = new int*[n];
        for(int i = 0; i < n; ++i) {
            matrix[i] = new int[n];
            for(int j = 0; j < n; ++j){
                matrix[i][j] = 0;
            }
        }
    }

    Matrix(int n, int* arr){
        this->Mn = n;
        matrix = new int*[n];
        for(int i = 0; i < n; ++i) {
            matrix[i] = new int[n];
            for(int j = 0; j < n; ++j){
                matrix[i][j] = arr[i*Mn+j];
            }
        }
    }

    ~Matrix(){
        for(int i = 0; i < Mn; ++i) {
            delete [] matrix[i];
        }
        delete [] matrix;
    }

    friend ostream& operator <<(ostream& out, const Matrix& mat);
    friend istream& operator >>(istream& in, Matrix& mat);

};


ostream& operator <<(ostream& out, const Matrix& mat)
{
 for (int i=0; i<mat.Mn; i++){
    for (int j=0; j<mat.Mn; j++){
        cout<<mat.matrix[i][j]<<" ";
    }
    cout<<endl;
 }
 return out;
}

int Matrix::det(){
    int det = 0;
    for (int i=0; i<1; i++){
        for (int j=0; j<this->Mn; j++){
            if (this->Mn > 2){
                int arr[Mn*Mn-2*Mn+1];
                for (int k=1; k<this->Mn; k++){
                    int arrCounter = 0;
                    for (int l=0; l<this->Mn; l++){
                        if (l!=j) {
                            arr[(k-1)*(Mn-1)+arrCounter] = matrix[k][l];
                            arrCounter++;
                        }
                    }
                }
                Matrix a(Mn-1,arr);
                cout<<a<<endl;
                det = j%2==0 ? det + matrix[i][j]*a.det(): det-matrix[i][j]*a.det();
            } else {
                det += matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
                cout<<det<<endl;
                return det;
            }
        }
    }
    return det;
}

Matrix Matrix::transp(){
        Matrix tMatrix(this->Mn);
        for (int i=0; i<this->Mn; i++){
            for (int j=0; j<this->Mn; j++){
                tMatrix.matrix[j][i] = matrix[i][j];
            }
        }
        return tMatrix;
}

#endif
