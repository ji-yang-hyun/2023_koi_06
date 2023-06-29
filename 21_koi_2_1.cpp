#include<iostream>
#include<string>
using namespace std;
int N,M;

int max(int a,int b, int c){
    if(a >= b && a >= c) return a;
    if(b >= a && b >= c) return b;
    if(c >= a && c >= b) return c;
    return 0;
}

int main(){
    cin >> M >> N;
    const int LEN = M;
    string str[LEN];
    int L_1[2000];
    int L_2[2000];
    int a,r=0,b;
    for(int i=0;i<M;i++){
        cin >> str[i];
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(i == 0){
                b = str[j][i] - 48;
                L_1[j] = b;
                a = 0;
            }
            else{
                if(i%2 != 0){
                    if(j > 0 && j < M-1){
                        a = max(L_1[j+1], L_1[j], L_1[j-1]);
                    }
                    else if(j > 0){
                        a = max(0, L_1[j], L_1[j-1]);
                    }
                    else if(j < M-1){
                        a = max(L_1[j+1], L_1[j], 0);
                    }
                    else{
                        a = L_1[j];
                    }
                    b = str[j][i] - 48;
                    L_2[j] = b + a;
                }
                else if(i%2 == 0){
                    if(j > 0 && j < M-1){
                        a = max(L_2[j+1], L_2[j], L_2[j-1]);
                    }
                    else if(j > 0){
                        a = max(0, L_2[j], L_2[j-1]);
                    }
                    else if(j < M-1){
                        a = max(L_2[j+1], L_2[j], 0);
                    }
                    else{
                        a = L_2[j];
                    }
                    b = str[j][i] - 48;
                    L_1[j] = b + a;
                }
    
            }
            if(r < a){
                r = a;
            }
        }
    }
    cout << r;
    return 0;
}