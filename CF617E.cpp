#include <bits/stdc++.h>
using namespace std;
//
#define int long long

int N , M , K , l , r;
int Num[2000010];
int unit;
int Xor[2000010];
int Ans[2000010];
int res;

struct Query {
	int l;
	int r;
	int id;
} Ask[2000010];

bool Cmp(Query a , Query b) {
	return a.l / unit == b.l / unit ? (a.r == b.r ? false : (a.l / unit) & 1 ^ (a.r < b.r)) : a.l < b.l;
}

void Add(int i) {
	res += Xor[(i ^ K)];
	Xor[i]++;
}

void Del(int i) {
	Xor[i]--;
	res -= Xor[(i ^ K)];
}


signed main() {
	ios::sync_with_stdio(false);
	cin >> N >> M >> K;
	unit = sqrt(N);
	for(int i = 1; i <= N; i++) {
		cin >> Num[i];
		Num[i] ^= Num[i - 1];
		
	}
	for(int i = 1; i <= M; i++) {
		cin >> Ask[i].l >> Ask[i].r;
		Ask[i].l--;
		Ask[i].id = i;
	}
	sort(Ask + 1 , Ask + 1 + M , Cmp);
	l = 1;
	r = 0;
	for(int i = 1; i <= M; i++) {
		while(l > Ask[i].l) Add(Num[--l]);
		while(l < Ask[i].l) Del(Num[l++]);
		while(r < Ask[i].r) Add(Num[++r]);
		while(r > Ask[i].r) Del(Num[r--]);
		Ans[Ask[i].id] = res;
	}
	for(int i = 1; i <= M; i++){
		cout << Ans[i] << endl;
	}
}