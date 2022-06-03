#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4 + 10;
int N , M;

struct LB {
	int P[40];
	LB() { memset(P , 0 , sizeof P); }
	void Insert(int k) {
		for(int i = 31; i >= 0; i--) {
			if(!(k & (1 << i))) continue;
			if(!P[i]) {
				P[i] = k;
				return;
			}
			k ^= P[i];
		}
	}
	int Query() {
		int res = 0;
		for(int i = 31; i >= 0; i--) res = max(res , (res ^ P[i]));
		return res;
	}
	void Merge(LB X) {
        for(int i = 31; i >= 0; i--)
            if(X.P[i])
				Insert(X.P[i]);
    }
};

struct Node {
	int l , r;
	LB v;
} Tree[MAXN * 4];
void PushDown(int p) {
	Tree[p].v.Merge(Tree[p * 2].v);
	Tree[p].v.Merge(Tree[p * 2 + 1].v);
}
void Build(int p , int l , int r) {
	Tree[p].l = l;
	Tree[p].r = r;
	if(l == r) return;
	int Mid = l + r >> 1;
	Build(p * 2 , l , Mid);
	Build(p * 2 + 1 , Mid + 1 , r);
	PushDown(p);
}
void UpDate(int p , int pos , int k) {
	if(Tree[p].l == pos && Tree[p].r == pos) {
		Tree[p].v.Insert(k);
		return;
	}
	int Mid = (Tree[p].l + Tree[p].r) >> 1;
	if(pos <= Mid) UpDate(p * 2 , pos , k);
	else UpDate(p * 2 + 1 , pos , k);
	PushDown(p);
	return; 
}
LB Query(int p , int l , int r) {
	if(l <= Tree[p].l && Tree[p].r <= r) {
		return Tree[p].v;
	}
	LB res;
	int Mid = (Tree[p].l + Tree[p].r) >> 1;
	if(l <= Mid) res.Merge(Query(p * 2 , l , r));
	if(r > Mid)  res.Merge(Query(p * 2 + 1 , l , r));
	return res;
}


signed main() {
	ios::sync_with_stdio(false);
	cin >> N >> M;
	Build(1 , 1 , M);
	for(int i = 1 , op , l , r; i <= N; i++) {
		cin >> op >> l >> r;
		if(op == 1) {
			UpDate(1 , l , r);
		}
		else {
			cout << Query(1 , l , r).Query() << endl;
		}
	}
	return 0;
}