#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 1000010;

long long Fa[MAXN] , Num[MAXN] , Tree[MAXN] , N , M , t;

void Add(long long x , long long d) {
	while(x <= N) {
		Tree[x] += d;
		x += (x & -x); 
	}
}

long long Ask(int x) {
	long long res = 0;
	while(x) {
		res += Tree[x];
		x -= (x & -x);
	}
	return res;
}

int Find(int x) {
	if(x == Fa[x]) return x;
	else return Fa[x] = Find(Fa[x]);
}


int main() {
	scanf("%lld" ,&N);
	for(int i = 1; i <= N; i++) 
	scanf("%lld" ,&Num[i]) , Add(i , Num[i]) , Fa[i] = i;
	scanf("%lld" ,&M);
	Fa[N + 1] = N + 1;
	while(M--) {
		long long op , x , y;
		scanf("%lld%lld%lld" ,&op ,&x ,&y);
		if(x > y) swap(x , y);
		if(op == 1) printf("%lld\n" ,Ask(y) - Ask(x - 1));
		else {
			for(int i = x; i <= y; Add(i , (t = (int)sqrt(Num[i])) - Num[i]), Num[i] = t, Fa[i] = (Num[i] <= 1) ? i + 1 : i, i = (Find(i) == i) ? i + 1 : Fa[i]);
		}
	}
	return 0;
}