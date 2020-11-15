#include <iostream>
#include <string>
#include <iomanip>  
#include "Matrix.h"

using namespace std;

int main(void)
{
    int n;
    cout << "Enter the size of the matrix: " << endl;
    cin >> n;
    cin.ignore();
    double* input = new double[n * n];

    string inp;
    string delimiter = " ";
    size_t pos = 0;
    string token;

    for (int i = 0; i < n; i++) {
        cout << "Enter row " << i + 1 <<": "<< endl;
        getline(cin, inp);
        for (int j = 0; j < n;j++) {
            pos = inp.find(delimiter);
            token = inp.substr(0, pos);
            input[i*n+j] = stod(token);
            inp.erase(0, pos + delimiter.length());
            if (pos == string::npos) break;
        }   
    }

    cout << endl;

    Matrix mat(n, input);

    cout << mat << endl;


    pos = 0;
    string constVals;
    double* constValsArr = new double[n];
    cout << "Enter the constant vector: " << endl;
    getline(cin, constVals);
    for (int j = 0; j < n; j++) {
        pos = constVals.find(delimiter);
        token = constVals.substr(0, pos);
        constValsArr[j] = stod(token);
        constVals.erase(0, pos + delimiter.length());
        if (pos == string::npos) break;
    }

    cout << endl;

    if (mat.isInvertible()) {
        Matrix matInv(mat.invert());
        double* solutions = matInv.findSolutions(constValsArr);
        cout << "Solutions: ";
        for (int i = 0; i < n; i++) cout << setw(3) << setprecision(4) << *(solutions + i) << " ";
    }
    else cout <<"The system has no solutions" << endl;
    
    return 0;
}

