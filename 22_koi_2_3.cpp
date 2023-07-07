#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

using lint = long long;

const int maxn = 1 << 17; // 쉬프트 연산 2^17이다.
const lint inf = 1e17; // 1 * 10^17


int N, a[maxn], cp[maxn];

struct segt { //
    lint t[maxn*2], lz[maxn*2];
    bool ilz[maxn*2];
    void init() {
    	ilz[1] = true;
    	t[1] = lz[1] = inf;
    }
    void propagate(int s, int e, int x) {
    	if (s < e) {
    		if (ilz[x]) {
    			ilz[2*x] = true;
    			t[2*x] = lz[2*x] = inf;
    			ilz[2*x+1] = true;
    			t[2*x+1] = lz[2*x+1] = inf;
    			ilz[x] = false;
    		}
    		if (lz[x] < inf) {
	    		lz[2*x] = min(lz[2*x], lz[x]);
	    		t[2*x] = min(t[2*x], lz[x]);
	    		lz[2*x+1] = min(lz[2*x+1], lz[x]);
	    		t[2*x+1] = min(t[2*x+1], lz[x]);
    			lz[x] = inf;
	    	}
    	}
    }
    lint merge(lint a, lint b) { return min(a, b); }
    void update(int s, int e, int x, int l, int r, lint v) {
    	propagate(s, e, x);
    	if (l <= s and e <= r) {
    		lz[x] = min(lz[x], v);
    		t[x] = min(t[x], v);
    	} else if (l <= e and s <= r) {
    		int m = (s+e) / 2;
    		update(s, m, 2*x, l, r, v);
    		update(m+1, e, 2*x+1, l, r, v);
    		t[x] = merge(t[2*x], t[2*x+1]);
    	}
    }
    void update(int l, int r, lint v) { return update(0, maxn-1, 1, l, r, v); }
    lint query(int s, int e, int x, int p) {
    	propagate(s, e, x);
    	if (s == e) return t[x];
    	else {
    		int m = (s+e) / 2;
    		if (p <= m) return query(s, m, 2*x, p);
    		else return query(m+1, e, 2*x+1, p);
    	}
    }
    lint query(int p) { return query(0, maxn-1, 1, p); }
} t1, t2;

lint query(int x) {
	return min(t1.query(x) - x, t2.query(x) + x);
}

int main() {
	cin >> N;
	for (int i=0; i<N; i++) cin >> a[i]; // 입력

	for (int i=0; i<N; i++) cp[i] = a[i];// cp에 복사
	sort(cp, cp+N); // cp를 정렬

	for (int i=0; i<N; i++) a[i] = lower_bound(cp, cp+N, a[i]) - cp; // cp가 정렬되어있기 때문에 a[i]원소가 몇 번째로 큰지 저장한다 (좌표압축)

	vector<int> idx[100004];

	for (int i=0; i<N; i++) idx[a[i]].push_back(i+1); // idx[a[i]] 에 a[i]라는 번호의 차를 가진 칸의 번째수를 저장한다.

	bool init = true;
	for (int h=N-1; h>=0; h--) if (!idx[h].empty()) { // 만약 i라는 번호를 가진 차가 있다면
		vector<lint> val; // long long을 저장하는 벡터를 선언

		if (init) { // 만약 init 함수가 true라면 
			for (int k : idx[h]) val.push_back(0ll); // idx[h]를 순회하면서 val에 0ll을 pushback한다
			init = false;
		} else { //아니면
			for (int k : idx[h]) val.push_back(query(k)); // 
		}

		t1.init();
		t2.init();

		int K = idx[h].size();

		{
			int x = 0, y = K-1;
			int L = idx[h][x], R = idx[h][y];
			// start -(cw)-> R -> L
			t1.update(1, R, 2 * R - L + val[x]);
			t1.update(R+1, N, N + 2 * R - L + val[x]);
			// start -(ccw)-> R -> L
			t2.update(1, R-1, N - L + val[x]);
			t2.update(R, N, - L + val[x]);
			// start -(ccw)-> L -> R
			t1.update(1, L, R + val[y]);
			t1.update(L+1, N, N + R + val[y]);
			// start -(cw)-> L -> R
			t2.update(1, L-1, N + R - 2 * L + val[y]);
			t2.update(L, N, R - 2 * L + val[y]);
		}

		for (int i=0; i+1<K; i++) {
			int x = i, y = i+1;
			int L = idx[h][x], R = idx[h][y];
			// start -(cw)-> R -> N -> 1 -> L
			t1.update(1, R, N + L + val[x]);
			t1.update(R+1, N, 2 * N + L + val[x]);
			// start -(ccw)-> R -> N -> 1 -> L
			t2.update(1, R-1, 2 * N + L - 2 * R + val[x]);
			t2.update(R, N, N + L - 2 * R + val[x]);
			// start -(ccw)-> L -> 1 -> N -> R
			t2.update(1, L-1, 2 * N - R + val[y]);
			t2.update(L, N, N - R + val[y]);
			// start -(cw)-> L -> 1 -> N -> R
			t1.update(1, L, N + 2 * L - R + val[y]);
			t1.update(L+1, N, 2 * N + 2 * L - R + val[y]);
		}
	}

	cout << query(1) << '\n';
}