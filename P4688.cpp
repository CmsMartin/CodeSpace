#include <bits/stdc++.h>
using namespace std;

bitset<100010> Sum[33346] , Now;
int Unit;
int N , M , Num[100010] , Ans[100010]  ,Cnt[100010];

struct Query {
	int l , r , id;
	bool operator < (const Query &o) const {
		if(l / Unit == o.l / Unit) return r < o.r;
		return l < o.l;
	}
} Ask[100010];

void Add(int i) {
	Now.set(i + Cnt[i]);
	Cnt[i]++;
}

void Del(int i) {
	Cnt[i]--;
	Now.reset(i + Cnt[i]);
}

void Solve() {
	Now.reset();
	int m = 0, tot = 0;
	for(tot = 0; tot <= 100000 / 3 && M; tot++) {
		M--;
		Ans[tot] = 0;
		Sum[tot].set();
		for(int j = 0; j < 3; j++) {
			cin >> Ask[m].l >> Ask[m].r;
			Ask[m].id = tot;
			Ans[tot] += Ask[m].r - Ask[m].l + 1;
			m++;
		}
	}
	sort(Ask , Ask + m);
	for(int i = 0 , l = 1 , r = 0; i < m; i++) {
		while(l > Ask[i].l) Add(Num[--l]);
		while(r < Ask[i].r) Add(Num[++r]);
		while(l < Ask[i].l) Del(Num[l++]);
		while(r > Ask[i].r) Del(Num[r--]);
		Sum[Ask[i].id] &= Now;
	}
	for(int i = 0; i < tot; i++) {
		Ans[i] -= Sum[i].count() * 3;
	}
	for(int i = 0; i < tot; i++) {
		cout << Ans[i] << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	Unit = sqrt(N);
	for(int i = 1; i <= N; i++) {
		cin >> Ans[i];
		Num[i] = Ans[i];
	}
	sort(Ans + 1 , Ans + 1 + N);
	for(int i = 1; i <= N; i++) {
		Num[i] = lower_bound(Ans + 1 , Ans + 1 + N , Num[i]) - Ans;
	}
	memset(Ans , 0 , sizeof Ans);
	Solve();
	memset(Cnt , 0 , sizeof Cnt);
	Solve();
	memset(Cnt , 0 , sizeof Cnt);
	Solve();
	return 0;
}