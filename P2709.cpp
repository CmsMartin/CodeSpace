#include <bits/stdc++.h>
using namespace std;

long long N , M , K , Unit;
long long Num[50010];
long long res = 0;
long long Cnt[50010];
long long Ans[50010];

struct Query {
	long long l , r;
	long long id;
	bool operator < (const Query &o) const {
		if(l / Unit == o.l / Unit) return r < o.r;
		else return l < o.l;
	}
} Ask[100010];

void Add(int Pos) {
	Cnt[Num[Pos]]++;
	res += Cnt[Num[Pos]] * 2 - 1;
}

void Del(int Pos) {
	Cnt[Num[Pos]]--;
	res -= Cnt[Num[Pos]] * 2 + 1;
}

int main() {
	scanf("%lld%lld%lld" ,&N ,&M ,&K);
	Unit = pow(N , 0.667);
	for(int i = 1; i <= N; i++) {
		scanf("%lld" ,Num + i);
	}
	for(int i = 1; i <= M; i++) {
		scanf("%lld%lld" ,&Ask[i].l ,&Ask[i].r);
		Ask[i].id = i;
	}
	sort(Ask + 1 , Ask + 1 + M);
	for(int i = 1 , l = 1 , r = 0; i <= M; i++) {
		while(l > Ask[i].l) Add(--l);
		while(r < Ask[i].r) Add(++r);
		while(l < Ask[i].l) Del(l++);
		while(r > Ask[i].r) Del(r--);
		Ans[Ask[i].id] = res;
	}
	for(int i = 1; i <= M; i++) {
		printf("%d\n" ,Ans[i]);
	}
	return 0;
}