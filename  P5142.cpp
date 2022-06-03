#include <bits/stdc++.h>
using namespace std;

#define int long long

const int Mod = 1e9 + 7 , MAXN = 1e5 + 10;

int BinPower(int a , int b = Mod - 2) {
	int res = 1;
	while(b) {
		if(b & 1) res = 1ll * res * a % Mod;
		a = 1ll * a * a % Mod;
		b >>= 1;
	}
	return res;
}

int N , M , Num[MAXN];

struct ST_Tree {
	int LeftTree , RightTree;
	int Sum , Prod;
}Tree[MAXN * 4];

void UpDate(int p) {
	Tree[p].Sum = Tree[p * 2].Sum + Tree[p * 2 + 1].Sum;
	Tree[p].Sum %= Mod;
	Tree[p].Prod = Tree[p * 2].Prod + Tree[p * 2 + 1].Prod;
	Tree[p].Prod %= Mod;
}

void Build(int p , int l , int r) {
	Tree[p].LeftTree = l;
	Tree[p].RightTree = r;
	if(l == r) {
		Tree[p].Sum = Num[l] % Mod;
		Tree[p].Prod = Num[l] * Num[l] % Mod;
		return;
	}
	int Mid = l + r >> 1;
	Build(p * 2 , l , Mid);
	Build(p * 2 + 1 , Mid + 1 , r);
	UpDate(p);
}

void Change(int p , int k , int v) {
	if(Tree[p].LeftTree == Tree[p].RightTree) {
		Tree[p].Sum = v % Mod;
		Tree[p].Prod = v * v % Mod;
		return;
	}
	int Mid = Tree[p].LeftTree + Tree[p].RightTree >> 1;
	if(k <= Mid) Change(p * 2 , k , v);
	else Change(p * 2 + 1 , k , v);
	UpDate(p);
}

int Query1(int p , int l , int r) {
	if(l <= Tree[p].LeftTree && Tree[p].RightTree <= r) {
		return Tree[p].Sum % Mod;
	}
	int Mid = Tree[p].LeftTree + Tree[p].RightTree >> 1;
	int res = 0;
	if(l <= Mid) res += Query1(p * 2 , l , r);
	if(r > Mid) res += Query1(p * 2 + 1 , l , r);
	return res;
}

int Query2(int p , int l , int r) {
	if(l <= Tree[p].LeftTree && Tree[p].RightTree <= r) {
		return Tree[p].Prod % Mod;
	}
	int Mid = Tree[p].LeftTree + Tree[p].RightTree >> 1;
	int res = 0;
	if(l <= Mid) res += Query2(p * 2 , l , r);
	if(r > Mid) res += Query2(p * 2 + 1 , l , r);
	return res;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) {
		cin >> Num[i];
	}
	Build(1 , 1 , N);
	int Sum1 , Sum2 , Inv , Ans , Ave;
	for(int i = 1 , op , x , y; i <= M; i++) {
		cin >> op >> x >> y;
		if(op == 1) {
			Change(1 , x , y);
		}
		else {
			Sum1 = Query1(1 , x , y) % Mod;
			Sum2 = Query2(1 , x , y) % Mod;
			Inv = BinPower(y - x + 1);
			Ave = Sum1 * Inv % Mod;
			Ans = Sum2 * Inv % Mod - Ave * Ave % Mod;
			Ans = (Ans % Mod + Mod) % Mod;
			cout << Ans << endl;
		}
	}
	return 0;
}