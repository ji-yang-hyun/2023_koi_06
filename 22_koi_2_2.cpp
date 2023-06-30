/*
 * KOI 2022 Model Solution
 *
 * Gyojun Youn
 * youngyojun@gmail.com
 *
 */

#include <cstdio>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;

const int MAXN = 250055;

vector<int> G[MAXN];

int ud[MAXN], uc[MAXN];

int P[MAXN];
int S[MAXN];
bool inS[MAXN];

int N, Q, K;

int uf(int i) {
	return i == ud[i] ? i : (ud[i] = uf(ud[i])); // 만약 i번째 노드가 uf를 한번 했다면 ud[i]를 uf(ud[i])로 바꾸고 return 아니면 i return
	//만약 처음에 만난곳이 최상단이 아니라면 나중에 처음에 만난곳이 uf를 하면서 최상단으로 갈것이기 때문에 unionfind가 된다
}

void uf(int a, int b) { // union find 함수 b는 현재노드 a는 현재 노드의 부모노드
	a = uf(a); b = uf(b);
	if(a == b) return; // 현재 노드의 부모노드가 현재노드일때 (현재 노드가 루트일때) 종료
	uc[a] += uc[b]; // a의 자식노드 개수에 b의 자식노드를 추가
	ud[b] = a; // K값이 바뀐 상황에서의 부모노드를 저장
}

void f(int i) { //dfs 함수
	for(int v : G[i]) if(v != P[i]) { //v가 현재 노드의 부모노드가 아닐때
		P[v] = i; // v노드의 부모를 현재 노드로 설정하고
		f(v); // 그 녿로 넘어간다
	}
}
/*
내 코드와 차이점
이미 갔던 정점은 다시 갈 일이 없기때문에 체크하지 않아도 되지만 나는 그걸 몰라서 체크했었고 이 코드에서는 체크하지 않는다 
*/

int main() {
	scanf("%d", &N);
	for(int i = N-1; i--;) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[a].emplace_back(b);
		G[b].emplace_back(a); // 쌍방향 트리
	}

	f(1); // 모든 노드가 연결되어있음을 이용

	iota(ud, ud+N+1, 0);
	fill_n(uc, N+1, 1);

	scanf("%d", &Q);

	while(Q--) {
		scanf("%d", &K);
		for(int i = K; i--;) {
			int v;
			scanf("%d", &v);
			S[i] = v;
			inS[v] = true; // 내 코드에서의 K-_arr의 역할
		}

		for(int i = K; i--;) { // 갈 수 있는 모든 노드를 다 탐색
			int v = S[i];
			int p = P[v];
			if(inS[p]) uf(p, v); // 만약 현재 노드의 부모노드가 K에 포함될때 uf함수 호출
		}

		ll r = 0;
		for(int i = K; i--;) {
			int v = S[i];
			if(uf(v) != v) // v가 자기자신을 부모노드로 가질 때 
				continue;
			int n = uc[v];
			r += ll(n) * (n-1); // 쌍의 개수 세기
		}

		printf("%lld\n", r >> 1); // 출력

		for(int i = K; i--;) { // 배열 초기화
			int v = S[i];
			ud[v] = v;
			uc[v] = 1;
			inS[v] = false;
		}
	}

	return 0;
}