//부분문제 4
#include<iostream>
using namespace std;
int N,A,a,d,cnt=0;
int MIN = 500;
int arr[500];
int main(){
    cin >> N;
    for(int i=0;i<N;i++){
        cin >> arr[i];
    }
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            d = (arr[i] - arr[j]) / (i-j);
            a = arr[i] - d*i;
            cnt = 0;
            for(int k=0;k<N;k++){
                if(arr[k] != a + d*k){
                    cnt ++;
                }
            }
            if(MIN > cnt){
                MIN = cnt;
            }
        }
    }
    cout << MIN;
}