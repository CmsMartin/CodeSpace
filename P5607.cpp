#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4 + 10;

struct LB {
	int P[40];
	LB() { memset(P , 0 , sizeof P); }
	void Insert(int k) {
		for(int i = 29; i >= 0; i--) {
			if(!(k & (1 << i))) continue;
			if(!P[i]) {
				P[i] = k;
				return;
			}
			k ^= P[i];
		}
	}
	int Query(int res) {
		for(int i = 29; i >= 0; i--) res = max(res , (res ^ P[i]));
		return res;
	}
};

LB Merge(LB x , LB y) {
	for (int i = 31; i >= 0; i--) {
		if(y.P[i]) 
			x.Insert(y.P[i]);
	}
	return x;
}

struct SegmentTree {
	int LeftTree;
	int RightTree;
	LB Value; 
} Tree[MAXN * 4];

int Num[MAXN] , N , M , Bit[MAXN];

void Build(int p , int l , int r) {
	Tree[p].LeftTree = l;
	Tree[p].RightTree = r;
	for(int i = l; i <= r; i++) Tree[p].Value.Insert(Num[i]);
	if(l == r) return;
	int Mid = l + r >> 1;
	Build(p * 2 , l , Mid);
	Build(p * 2 + 1 , Mid + 1 , r);
	Tree[p].Value = Merge(Tree[p * 2].Value , Tree[p * 2 + 1].Value);
}

void UpDate(int p , int pos , int v) {
	if(Tree[p].LeftTree == Tree[p].RightTree) {
		memset(Tree[p].Value.P , 0 , sizeof Tree[p].Value.P);
		Tree[p].Value.Insert(Num[Tree[p].LeftTree] ^= v);
		return;
	}
	int Mid = Tree[p].LeftTree + Tree[p].RightTree >> 1;
	if(pos <= Mid) UpDate(p * 2 , pos , v);
	else UpDate(p * 2 + 1 , pos , v);
	Tree[p].Value = Merge(Tree[p * 2].Value , Tree[p * 2 + 1].Value);
}

LB Query(int p , int l , int r) {
	if(l <= Tree[p].LeftTree && Tree[p].RightTree <= r) {
		return Tree[p].Value;
	}
	LB res;
	int Mid = Tree[p].LeftTree + Tree[p].RightTree >> 1;
	if(l <= Mid) res = Merge(res , Query(p * 2 , l , r));
	if(r > Mid)  res = Merge(res , Query(p * 2 + 1 , l , r));
	return res;
}

int LowBit(int x) {
	return x & -x;
}

void Add(int x , int d) {
	while(x <= N) {
		Bit[x] ^= d;
		x += LowBit(x);
	}
}

int Ask(int p) {
	int res = 0;
	while(p) {
		res ^= Bit[p];
		p -= LowBit(p);
	}
	return res;
}

int main() {
    scanf("%d%d" ,&N ,&M);
    for(int i = 1; i <= N; i++) {
    	scanf("%d" ,Num + i);
	}
	for(int i = N; i >= 2; i--) {
		Num[i] ^= Num[i - 1];
	}
	for(int i = 1; i <= N; i++) {
		Add(i , Num[i]);
	}
	Build(1 , 1 , N);
	for(int i = 1 , op , l , r , v; i <= M; i++) {
		scanf("%d%d%d%d" ,&op ,&l ,&r ,&v);
		if(op == 1) {
			Add(l , v);
			UpDate(1 , l , v);
			if(r + 1 <= N) {
				UpDate(1 , r + 1 , v);
				Add(r + 1 , v);
			}
		}
		else {
			int k = Ask(l);
			if(l == r) {
				printf("%d\n" ,max(k ^ v , v));
			}
			else {
				LB res = Query(1 , l + 1 , r);
				res.Insert(k);
				printf("%d\n" ,res.Query(v));
			}
		}
	}
    return 0;
}