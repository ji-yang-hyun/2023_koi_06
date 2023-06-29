#include<iostream>
#include<algorithm>
#include<math.h>

using namespace std;

int N,A,B,C=0;
pair<int,int> p[100000];//value, index
pair<int,int> s;//교환용

void f(int a,int b){
    // cout << p[i].first << " " << p[i].second << endl;
    A = abs((a - b)); // 시계방향
    // 반시계방향
    if(a > b){
        B = abs(b + N - a);
    }
    else{
        B = abs(a + N - b);
    }
        
    if(A>B){
        C += B;
    }
    else{
        C += A;
    }
    return;
}

int main(){
    cin >> N;
    for(int i=0;i<N;i++){
        cin >> A;
        p[i].first = A;
        p[i].second = i+1;
    }
    for(int j=0;j<N;j++){
        for(int i=0;i<N-1;i++){
            if(p[i].first > p[i+1].first){
                s = p[i];
                p[i] = p[i+1];
                p[i+1] = s;
            }
        }
    }
    f(1,p[0].second);
    for(int i=0;i<N-1;i++){
        f(p[i].second,p[i+1].second);
    }
    cout << N-1 << endl;
    return 0;
}