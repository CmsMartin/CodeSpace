#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1e5 + 5;

int Num[SIZE] , N , M;

struct STree {
	unsigned long long l , r;
	unsigned long long sum , add;
}Tree[4 * SIZE];

void build(int x , int l , int r) {
	Tree[x].l = l;
	Tree[x].r = r;
	if(l == r) {
		Tree[x].sum = Num[l];
		return;
	}
	build(x * 2 , l , l + r >> 1);
	build(x * 2 + 1 , (l + r >> 1) + 1 , r);
	Tree[x].sum = Tree[x * 2].sum + Tree[x * 2 + 1].sum;
}

void spread(int p) {
	if(Tree[p].add) {
		Tree[p * 2].sum  += Tree[p].add * (Tree[p * 2].r - Tree[p * 2].l + 1);
		Tree[p * 2 + 1].sum += Tree[p].add * (Tree[p * 2 + 1].r - Tree[p * 2 + 1].l + 1);
		Tree[p * 2].add += Tree[p].add;
		Tree[p * 2 + 1].add += Tree[p].add;
		Tree[p].add = 0;
	}
}

unsigned long long ask(int x , int l , int r) {
	if(l <= Tree[x].l && r >= Tree[x].r) return Tree[x].sum;
	spread(x);
	int mid = Tree[x].l + Tree[x].r >> 1;
	unsigned long long val = 0;
	if(l <= mid) val += ask(x * 2 , l , r);
	if(r > mid) val += ask(x * 2 + 1 , l , r);
	return val;
}

void change(int x , int l , int r , int d) {
	if(l <= Tree[x].l && r >= Tree[x].r) {
		Tree[x].sum += (long long)d * (Tree[x].r - Tree[x].l + 1);
		Tree[x].add += d;
		return;
	}
	spread(x);
	int mid = Tree[x].l + Tree[x].r >> 1;
	if(l <= mid) change(x * 2 , l , r , d);
	if(r > mid) change(x * 2 + 1 , l , r , d);
	Tree[x].sum = Tree[x * 2].sum + Tree[x * 2 + 1].sum;
}

int main() {
	cin >> N >> M;
	for(int i = 1;i <= N;i++)
		cin >> Num[i];
	build(1 , 1 , N);
	while(M--) {
		int op;
		int l , r , d;
		cin >> op >> l >> r;
		if(op == 1) {
			cin >> d;
			change(1 , l , r , d);
		}
		else {
			cout << ask(1 , l , r) << endl;
		}
	}
	return 0;
}