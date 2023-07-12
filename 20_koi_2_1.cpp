#include<iostream>
#include<string>
using namespace std;
int main(){
    string str_1[4] = {"0 1 ","1 0 ","2 3 ","3 2 "};
    string str_2[4] = {"2 3 ","3 2 ","0 1 ","1 0 "};
    int k,h,n=1;
    cin >> k;
    const int K = k;
    char C[2*K];
    for(int i=2*k-1;i>=0;i--){
        cin >> C[i];
    }
    cin >> h;
    int r=0,c=0;
    for(int i=0;i<2*k;i++){
        if(r==0){
            if(C[i] == 'R'){
                switch (h)
                {
                case 0:
                    h = 1;
                    break;
                case 1:
                    h = 0;
                    break;
                case 2:
                    h = 3;
                    break;
                case 3:
                    h = 2;
                    break;
                }
                r++;
            }
            if(C[i] == 'L'){
                r++;
            }
        }
        if(c==0){
            if(C[i] == 'D'){
                h += 2;
                h = h%4;
                c++;
            }
            if(C[i] == 'U'){
                c++;
            }
        }
    }
    for(int i=0;i<k;i++){
        n = n*2;
    }
    for(int i=0;i<n/2;i++){
        for(int j=0;j<n/2;j++){
            cout << str_1[h];
        }
        cout << "\n";
        for(int j=0;j<n/2;j++){
            cout << str_2[h];
        }
        cout << "\n";
    }
}