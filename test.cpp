#include<iostream>
using namespace std;
int main(){
    int a[100] = {};
    a[2] = 5;
    cout << a[a+2];
}