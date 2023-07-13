#include<iostream>
#include<vector>
using namespace std;

vector<int> mt[300001];
int parents[300001] = {};
int check[300001] = {};
long long int cnt = 0;

void dfs(int n,int p){
    if(check[n] == 0){
        check[n] = 1;
        parents[n] = p;
        for(int i=0;i<mt[n].size();i++){
            dfs(mt[n][i],n);
        }
    }
    return;
}

void road(int n,int check_road[300001]){
    if(n == 1){
        return;
    }
    if(check_road[n] == 0){
        cnt++;
        check_road[n] = 1;
    }
    road(parents[n],check_road);
}

int main(){
    int N,a,b,r = 0;
    cin >> N;
    
    for(int i=0;i<N-1;i++){
        cin >> a >> b;
        mt[a].push_back(b);
        mt[b].push_back(a);
    }
    dfs(1,1);
    for(int i=1;i<=N;i++){
        for(int j=i+1;j<=N;j++){
            int check_road[300001] = {};
            road(i,check_road);
            road(j,check_road);
        }
    }

    cout << cnt;
}