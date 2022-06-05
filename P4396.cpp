#include <bits/stdc++.h>
using namespace std;

struct Query {
	int l , r , a , b , id;
} Ask[100010];

struct Answer {
	int a , b;
} Ans[100010];

int N , M , Num[100010];
int unit;
int Cnt[100010];

int C[100010][3];

void Add(int x , int t , int Val) {
	while(x <= N) {
		C[x][t] += Val;
		x += x & -x;
	}
}

int Sum(int x , int t) {
	int res = 0;
	while(x) {
		res += C[x][t];
		x -= x & -x;
	}
	return res;
}

int UpDate(int x , int i) {
	Cnt[Num[x]] += i;
	Add(Num[x] , 1 , i);
	if(i == 1)
		if(Cnt[Num[x]] == 1)
			Add(Num[x] , 2 , 1);
	if(i == -1)
		if(Cnt[Num[x]] == 0)
			Add(Num[x] , 2 , -1);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> M;
	unit = sqrt(N);
	for(int i = 1; i <= N; i++) {
		cin >> Num[i];
	}
	for(int i = 1; i <= M; i++) {
		cin >> Ask[i].l >> Ask[i].r >> Ask[i].a >> Ask[i].b;
		Ask[i].id = i;
	}
	sort(Ask + 1 , Ask + 1 + M , [=](Query x , Query y) { if(x.l / unit == y.l / unit) return x.r < y.r; return x.l < y.l; });
	int l = 1 , r = 0;
	for(int i = 1; i <= M; i++) {
		while(r < Ask[i].r) UpDate(++r , 1);
		while(r > Ask[i].r) UpDate(r-- , -1);
		while(l < Ask[i].l) UpDate(l++ , -1);
		while(l > Ask[i].l) UpDate(--l , 1);
		Ans[Ask[i].id].a = Sum(Ask[i].b , 1) - Sum(Ask[i].a - 1 , 1);
		Ans[Ask[i].id].b = Sum(Ask[i].b , 2) - Sum(Ask[i].a - 1 , 2);
	}
	for(int i = 1; i <= M; i++) {
		cout << Ans[i].a << " " << Ans[i].b << endl;
	}
	return 0;
}