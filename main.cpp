#include <iostream>
#include <cmath>
#include "Class.cpp"

using namespace std;

int main(void)
{
    int arr[16] = {1,3,7,9,1,4,8,3,3,3,4,5,5,5,7,8};
    Matrix mat(4,arr);
    cout<<mat<<endl;
    int det = mat.det();
    cout<<det<<endl;
    mat = mat.transp();
    cout<<mat<<endl;
    return 0;
}

