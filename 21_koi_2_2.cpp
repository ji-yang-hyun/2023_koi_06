#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

long long int mg_X[200005] = {};
long long int mg_A[200005] = {};
long long int X[200005] = {};
long long int A[200005] = {};
long long int S_A[200005] = {};
long long int S_AX[200005] = {};
vector<int> r;

void merge(int l,int mid,int r){
    int i=l,j=mid+1,k=l;
    while(i <= mid && j <= r){
        if(X[i] < X[j]){
            mg_X[k] = X[i];
            mg_A[k] = A[i];
            i++; k++;
        }
        else{
            mg_X[k] = X[j];
            mg_A[k] = A[j];
            j++; k++;
        }
    }
    if(i <= mid){
        for(int m=i;m<=mid;m++){
            mg_X[k] = X[m];
            mg_A[k] = A[m];
            k++;
        }
    }
    else{
        for(int m=j;m<=r;m++){
            mg_X[k] = X[m];
            mg_A[k] = A[m];
            k++;
        }
    }
    for(int m=l;m<=r;m++){
        X[m] = mg_X[m];
        A[m] = mg_A[m];
    }
}

void merge_sorting(int l,int r){
    if(r == l){
        return;
    }
    int mid = (l+r)/2;
    merge_sorting(l,mid);
    merge_sorting(mid+1,r);
    merge(l,mid,r);
}

int b_serch(int s,int e,int t){
    int mid = (s+e) / 2;
    if(s == e){
        return 0;
    }
    if(s+1 == e){
        return s;
    }
    if(X[mid] == t){
        return mid;
    }
    if(X[mid] > t){
        return b_serch(s,mid,t);
    }
    if(X[mid] < t){
        return b_serch(mid,e,t);
    }
    return 0;
}

int main(){
    int N,x,a,Q,q,t_idx;
    long long int sum_a=0,sum_ax=0,m;
    cin >> N >> Q;
    for(int i=0;i<N;i++){
        cin >> A[i] >> X[i];
    }
    merge_sorting(0,N-1);
    for(int i=0;i<N;i++){
        sum_a += A[i];
        sum_ax += A[i]*X[i];
        S_A[i] = sum_a;
        S_AX[i] = sum_ax;
    }
    for(int i=0;i<Q;i++){
        cin >> q;
        t_idx = b_serch(0,N-1,q);
        if(q < X[0]){
            m = -(S_A[N-1])*q + S_AX[N-1];
        }
        else if(q > X[N-1]){
            m = (S_A[N-1])*q - S_AX[N-1];
        }
        else{
            m = (S_A[t_idx]*2 - S_A[N-1])*q - (S_AX[t_idx]*2 - S_AX[N-1]);
        }
        cout << m << "\n";
    }
    return 0;
}