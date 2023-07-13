#include<iostream>
#include<vector>
using namespace std;

vector<int> tree[50001];
int check[50001];
int parents[50001];
int depth[50001];

void dfs(int n,int p,int d){ // node, parents, depth
    if(check[n] == 0){
        check[n] = 1;
        parents[n] = p;
        depth[n] = d;
        for(int i=0;i<tree[n].size();i++){
            dfs(tree[n][i],n,d+1);
        }
    }
    return;
}


int equalize_depth(int n,int m){
    int N = depth[m] - depth[n];
    for(int i=0;i<N;i++){
        m = parents[m];
    }
    return m;
}

int lca(int n,int m){ // node1, node2
/*
노드 N이 더 깊이가 작은 노드
*/
    if(depth[n] == depth[m]){
        
    }
    else if(depth[n] > depth[m]){
        int t = n;
        n = m;
        m = t;
    }
    else if(depth[n] < depth[m]){

    }
    
    m = equalize_depth(n,m);
    while (n != m){
        n = parents[n];
        m = parents[m];
    }
    
    return n;
}

int main(){
    int n,a,b,m;
    cin >> n;
    for(int i=0;i<n-1;i++){
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    dfs(1,1,1);
    cin >> m;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        cout << lca(a,b) << "\n";
    }
}