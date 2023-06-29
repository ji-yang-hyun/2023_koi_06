//내 풀이
#include<iostream>
#include<vector>
using namespace std;

int N,Q,K,C = 0;
int s_arr[250001] = {}; // 갔던곳 체크
int k_arr[250001] = {}; // 체크된곳 서치 x
int k_arr_2[250001] = {};
vector<int> v[250001];
vector<int> k;
vector<int> s; // 탐색용 벡터

void serch(int n){
    if(s_arr[n] != 0){
        return;
    }
    s.push_back(n);
    s_arr[n] = 1;
    k_arr[n] = 1;
    for(int i=0;i<v[n].size();i++){
        if(k_arr_2[v[n][i]] != 0){
            serch(v[n][i]);
        }
    }
}

int main(){
    cin >> N;
    int A,B,len_s=0,len;
    for(int i=0;i<(N-1);i++){
        cin >> A >> B;
        v[A].push_back(B);
        v[B].push_back(A);
    }
    cin >> Q;
    for(int j=0;j<Q;j++){
        cin >> K;
        for(int i=0;i<K;i++){
            cin >> A;
            k.push_back(A);
            k_arr_2[A] = 1;
        }
        for(int i=0;i<K;i++){
            if(k_arr[k[i]] == 0){
                serch(k[i]);
                len = s.size();
                if(len - len_s > 1){
                    C += ((len-len_s) * (len - 1 - len_s) / 2);
                }
                len_s = len;
            }
        }
        cout << C << "\n";

        s.clear();
        k.clear();
        C = 0;
        len_s = 0;
        for(int i=0;i<250001;i++){
            s_arr[i] = 0;
            k_arr[i] = 0;
            k_arr_2[i] = 0;
        }
    }
    return 0;
}


///////////////////////////////////////

//부분문제 1 : N = 3 예외처리

//부분문제 4 : union find기법
#include<iostream>
#include<vector>
using namespace std;

int N,Q,K,C = 0;
int s_arr[250001] = {}; // 갔던곳 체크
int p_arr[250001] = {}; // 부모 표시 rts(index) = index의 부모
int k_arr[250001] = {};
int ps_arr[250001] = {};

vector<int> v[250001];
vector<int> k;


void serch(int n,int p){
    if(s_arr[n] != 0){
        return;
    }
    // cout << n;
    s_arr[n] = 1;
    p_arr[n] = p;
    for(int i=0;i<v[n].size();i++){
        serch(v[n][i],n);
    }
}

void uni(int n){
    if(k_arr[p_arr[n]] == 1 && n != 1){
        uni(p_arr[n]);
    }
    else{
        ps_arr[n]++;
    }
}

int main(){
    cin >> N;
    int A,B,len_s=0,len;
    for(int i=0;i<(N-1);i++){
        cin >> A >> B;
        v[A].push_back(B);
        v[B].push_back(A);
    }
    serch(1,1);
    cin >> Q;
    for(int j=0;j<Q;j++){
        cin >> K;
        for(int i=0;i<K;i++){
            cin >> A;
            k.push_back(A);
            k_arr[A] = 1;
        }
        for(int i=0;i<K;i++){
            uni(k[i]);
        }
        for(int i=0;i<=N;i++){
            C += ps_arr[i] * (ps_arr[i]-1)/2;
            // cout << ps_arr[i] << " ";
            ps_arr[i] = 0;
            k_arr[i] = 0;
        }
        k.clear();
        cout << C << endl;
        C = 0;
    }
    // serch(1,1);
    return 0;
}

/*
ps에서 0이 아닌것들만 조회



uni함수에서 가장 아래쪽에 있는 노드부터 조회하지 않아도 되는 노드를 걸러내기

구현 방법 : 
1.dfs함수(serch함수) 에서 최하단에 위치한 노드를 구하기

2-1. 1에서 구한 노드들을 union 해서 최상단 부모노드를 구하고 그 사이에 있는 노드들의 개수만큼 ps[최상단 부모노드] 에 추가한다.

2-2. 서로 다른 최 하단 노드들이 같은 부모를 가질때 일부 부모노드들이 중복되게 추가될 수 있으므로 pu배열을 만들고 2-1에서 구한 최하단 노드 ~ 최상단 부모 노드 사이의 노드들의 부모를 최상단 부모노드로 업데이트 시켜준다
(업데이트는 k가 바뀔때마다 초기화 해야하므로 불변하는 p(parent)배열 업데이트용 pu(parent_union)배열을 개별적으로 만든다.)(union 우선순위는 pu가 우선이고 pu가 0일때(최상단 부모노드는 0이 될 수 잆음을 이용) p배열을 참조한다)

3. 최하단 부모노드들을 끝냈다면 그 위에 다시 k에 포함되는 노드를 찾기 위해 r_uni(reverse_union)을 하고 찾은 노드를 최하단 노드들의 집합에 추가하기. 이 때 k값에 따라 최하단 노드들의 집합도 바뀌기 때문에 k값에 영향을 받지 않는 1에서 구한 집합을 
세이브하는 벡터를 따로 만든다.
(업데이트하는 최하단 노드의 집합 bottom, 1에서 구한 부분 세이브용인 bottom_save)

알고리즘 순서
1 -> 2-1 -> 2-2 -> 3 -> 2-1 -> 2-2 -> 3(반복)

참고
bool 자료형 
True = 1;
False = 0;
*/


// 구현방법 1.dfs함수(serch함수) 에서 최하단에 위치한 노드를 구하기
vector<int> bottom;

void serch(int n,int p){ 
    int is_bottom = 1; // true에서 시작
    if(s_arr[n] != 0){
        return;
    }
    // cout << n;
    s_arr[n] = 1;
    p_arr[n] = p;
    for(int i=0;i<v[n].size();i++){
        if(s_arr[n] == 0){
            is_bottom = 0; // 해당 노드 아래에 노드가 있을 때 is_bottom 변수를 false로 업데이트
            serch(v[n][i],n);
        }
    }
    if(is_bottom == 1){ // 만약 해당 노드 아래에 노드가 없을 때
        bottom.push_back(n); // 헤당 노드를 bottom에 추가
    }
}

// 구현방법 2-1. 1에서 구한 노드들을 union 해서 최상단 부모노드를 구하고 그 사이에 있는 노드들의 개수만큼 ps[최상단 부모노드] 에 추가한다.

int cnt=0;

void uni(int n){ 
    cnt += 1; //최하단 노드에서부터 최상단 노드까지 거치는 노드의 개수 새기
    if(k_arr[p_arr[n]] == 1 && n != 1){
        uni(p_arr[n]);
    }
    else{
        ps_arr[n]+=cnt; //ps[최상단 부모노드에 카운팅한 노드의 개수 추가하기
    }
}

int main(){
    cin >> N;
    int A,B,len_s=0,len;
    for(int i=0;i<(N-1);i++){
        cin >> A >> B;
        v[A].push_back(B);
        v[B].push_back(A);
    }
    serch(1,1);
    cin >> Q;
    for(int j=0;j<Q;j++){
        cin >> K;
        for(int i=0;i<K;i++){
            cin >> A;
            k.push_back(A);
            k_arr[A] = 1;
        }
        for(int i=0;i<bottom.size();i++){ //1에서 구한 최하단 노드들을 union하기
            cnt = 0; //개수 초기화
            uni(bottom[i]);
        }
        for(int i=0;i<=N;i++){
            C += ps_arr[i] * (ps_arr[i]-1)/2;

            ps_arr[i] = 0;
            k_arr[i] = 0;
        }
        k.clear();
        cout << C << endl;
        C = 0;
    }
    return 0;
}

/*
구현방법 2-2. 서로 다른 최 하단 노드들이 같은 부모를 가질때 일부 부모노드들이 중복되게 추가될 수 있으므로 pu배열을 만들고 2-1에서 구한 최하단 노드 ~ 최상단 부모 노드 사이의 노드들의 부모를 최상단 부모노드로 업데이트 시켜준다
(업데이트는 k가 바뀔때마다 초기화 해야하므로 불변하는 p(parent)배열 업데이트용 pu(parent_union)배열을 개별적으로 만든다.)(union 우선순위는 pu가 우선이고 pu가 0일때(노드는 0이 될 수 잆음을 이용) p배열을 참조한다)
*/

int pu_arr[250001] = {}; //pu배열 생성
int top; // 최상단 부모노드 저장

void uni(int n){ 
    cnt += 1; 
    if(pu_arr[n] == 0){ // pu가 0일때 p를 참조
        if(k_arr[p_arr[n]] == 1 && n != 1){
            uni(p_arr[n]);
            pu_arr[n] = top; // 재귀함수가 풀리면서 최상단 노드로 부모노드가 업데이트 된다
        }
        else{
            if(ps_arr[n] == 0){ // 이미 union한 부분과 그렇지 않은 부분의 연결점을 카운팅하지 않기 위해 union한 부분이 없는 경우를 예외처리
                ps_arr[n]+=cnt; 
            }
            else{ // 이미 union 한 부분이 있는 경우 연결점을 카운팅에서 제외하기 위해 cnt-1
                ps_arr[n]+=cnt-1;
            }
            top = n;
        }
    }
    else{ // pu가 0이 아닐 때 pu를 참조
        if(k_arr[pu_arr[n]] == 1 && n != 1){
            uni(pu_arr[n]);
            pu_arr[n] = top; // 재귀함수가 풀리면서 최상단 노드로 부모노드가 업데이트 된다
        }
        else{
            if(ps_arr[n] == 0){
                ps_arr[n]+=cnt; 
            }
            else{
                ps_arr[n]+=cnt-1;
            }
            top = n;
        }
    }
}

int main(){
    cin >> N;
    int A,B,len_s=0,len;
    for(int i=0;i<(N-1);i++){
        cin >> A >> B;
        v[A].push_back(B);
        v[B].push_back(A);
    }
    serch(1,1);
    cin >> Q;
    for(int j=0;j<Q;j++){
        cin >> K;
        for(int i=0;i<K;i++){
            cin >> A;
            k.push_back(A);
            k_arr[A] = 1;
        }
        for(int i=0;i<bottom.size();i++){ 
            cnt = 0;
            top = 0; // top 초기화
            uni(bottom[i]);

        }
        for(int i=0;i<=N;i++){
            C += ps_arr[i] * (ps_arr[i]-1)/2;

            ps_arr[i] = 0;
            pu_arr[i] = 0; // pu배열은 k값에 따라 변하기 때문에 초기화
            k_arr[i] = 0;
        }
        k.clear();
        cout << C << endl;
        C = 0;
    }
    return 0;
}

/*
3. 최하단 부모노드들을 끝냈다면 그 위에 다시 k에 포함되는 노드를 찾기 위해 r_uni(reverse_union)을 하고 찾은 노드를 최하단 노드들의 집합에 추가하기. 이 때 k값에 따라 최하단 노드들의 집합도 바뀌기 때문에 k값에 영향을 받지 않는 1에서 구한 집합을 
세이브하는 벡터를 따로 만든다.
(업데이트하는 최하단 노드의 집합 bottom, 1에서 구한 부분 세이브용인 bottom_save)
*/


vector<int> bottom_save; //bottom_save 선언

void serch(int n,int p){ 
    int is_bottom = 1;
    if(s_arr[n] != 0){
        return;
    }
    s_arr[n] = 1;
    p_arr[n] = p;
    for(int i=0;i<v[n].size();i++){
        if(s_arr[n] == 0){
            is_bottom = 0; // 해당 노드 아래에 노드가 있을 때 is_bottom 변수를 false로 업데이트
            serch(v[n][i],n);
        }
    }
    if(is_bottom == 1){
        bottom.push_back(n);
        bottom_save.push_back(n); // 최하단 노드들을 bottom_save에 저장하기
    }
}

void uni(int n){ 
    cnt += 1; 
    if(pu_arr[n] == 0){ 
        if(k_arr[p_arr[n]] == 1 && n != 1){
            uni(p_arr[n]);
            pu_arr[n] = top;
        }
        else{
            if(ps_arr[n] == 0){ 
                ps_arr[n]+=cnt; 
            }
            else{ 
                ps_arr[n]+=cnt-1;
            }
            top = n;
        }
    }
    else{ 
        if(k_arr[pu_arr[n]] == 1 && n != 1){
            uni(pu_arr[n]);
            pu_arr[n] = top; 
        }
        else{
            if(ps_arr[n] == 0){
                ps_arr[n]+=cnt; 
            }
            else{
                ps_arr[n]+=cnt-1;
            }
            top = n;
        }
    }
}

void r_uni(int n){ 
    if(k_arr[p_arr[n]] == 1){ // k에 포함되는 노드를 찾으면 bottom에 추가하기
        bottom.push_back(p_arr[n]);
    }
    else{ // k에 포함되지 않는 노드부터 올라가며 k에 포함되는 노드를 찾기
        r_uni(p_arr[n]);
    }
}

int main(){
    cin >> N;
    int A,B,len_s=0,len;
    for(int i=0;i<(N-1);i++){
        cin >> A >> B;
        v[A].push_back(B);
        v[B].push_back(A);
    }
    serch(1,1);
    cin >> Q;
    for(int j=0;j<Q;j++){
        cin >> K;
        for(int i=0;i<K;i++){
            cin >> A;
            k.push_back(A);
            k_arr[A] = 1;
        }
        for(int i=0;i<bottom.size();i++){ 
            cnt = 0;
            top = 0;
            uni(bottom[i]);
            r_uni(top); // 최상단 노드의 부모노드부터 탐색하기
        }
        bottom.clear(); // bottom은 k값의 영향을 받기 때문에 k값이 바뀔 때 초기화하기
        for(int i=0;i<=N;i++){
            C += ps_arr[i] * (ps_arr[i]-1)/2;

            ps_arr[i] = 0;
            pu_arr[i] = 0; 
            k_arr[i] = 0;
            if(i < bottom_save.size()){
                bottom.push_back(bottom_save[i]); // bottom을 bottom_save로 만들기
            }
        }
        k.clear();
        cout << C << endl;
        C = 0;
    }
    return 0;
}



/////////////////////////////////////////////
#include<iostream>
#include<vector>
using namespace std;

int N,Q,K,C = 0;
int s_arr[250001] = {}; // 갔던곳 체크
int p_arr[250001] = {}; // 부모 표시 rts(index) = index의 부모


vector<int> v[250001];
vector<int> bottom;
vector<int> bottom_save; //bottom_save 선언
vector<int> rc;

int cnt=0;

int top; // 최상단 부모노드 저장

void serch(int n,int p){ 
    int is_bottom = 1;
    if(s_arr[n] != 0){
        return;
    }
    s_arr[n] = 1;
    p_arr[n] = p;
    for(int i=0;i<v[n].size();i++){
        if(s_arr[v[n][i]] == 0){
            is_bottom = 0; // 해당 노드 아래에 노드가 있을 때 is_bottom 변수를 false로 업데이트
            serch(v[n][i],n);
        }
    }
    if(is_bottom == 1){
        bottom.push_back(n);
        bottom_save.push_back(n); // 최하단 노드들을 bottom_save에 저장하기
    }
}

void uni(int n, int k_arr[250001], int pu_arr[250001], int ps_arr[250001], int zh_arr[250001]){
    if(k_arr[n] == 0){
        return;
    }
    cnt += 1; 
    if(pu_arr[n] == 0){ 
        if(k_arr[p_arr[n]] == 1 && n != 1){
            uni(p_arr[n], k_arr, pu_arr, ps_arr, zh_arr);
            pu_arr[n] = top;
        }
        else{
            ps_arr[n]+=cnt-1;
            top = n;
            if(zh_arr[n] == 0){
                rc.push_back(n);
                zh_arr[n] = 1;
            }
        }
    }
    else{
        top = pu_arr[n];
        ps_arr[top]+=cnt-1;
        pu_arr[n] = top;
    }
}

void r_uni(int n,int k_arr[250001]){ 
    if(n == 1){
        return;
    }
    if(k_arr[n] == 1){ // k에 포함되는 노드를 찾으면 bottom에 추가하기
        bottom.push_back(n);
    }
    else{ // k에 포함되지 않는 노드부터 올라가며 k에 포함되는 노드를 찾기
        r_uni(p_arr[n], k_arr);
    }
}

int main(){
    cin >> N;
    int A,B,len_s=0,len;
    for(int i=0;i<(N-1);i++){
        cin >> A >> B;
        v[A].push_back(B);
        v[B].push_back(A);
    }
    serch(1,1);
    cin >> Q;
    for(int j=0;j<Q;j++){
        int k_arr[250001] = {};
        int ps_arr[250001] = {};
        int pu_arr[250001] = {}; //pu배열 생성
        int zh_arr[250001] = {};
        cin >> K;
        for(int i=0;i<K;i++){
            cin >> A;
            k_arr[A] = 1;
        }
        for(int i=0;i<bottom.size();i++){ 
            cnt = 0;
            top = bottom[i];
            uni(bottom[i],k_arr,pu_arr,ps_arr,zh_arr);
            r_uni(p_arr[top],k_arr); // 최상단 노드의 부모노드부터 탐색하기
        }

        for(int i=0;i<rc.size();i++){
            C += ps_arr[rc[i]] * (ps_arr[rc[i]]+1)/2;
        }
        bottom.clear();
        for(int i=0;i<bottom_save.size();i++){
            bottom.push_back(bottom_save[i]);
        }
        cout << C << endl;
        C = 0;
        // bottom.assign(bottom_save.begin(),bottom_save.end());// bottom은 k값의 영향을 받기 때문에 k값이 바뀔 때 초기화하기
        rc.clear();
    }
    return 0;
}

//모범코드 보고 비교하고 이해하기




