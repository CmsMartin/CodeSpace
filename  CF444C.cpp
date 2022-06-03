#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e5 + 10;

int C1[MAXN] , C2[MAXN] , N , M;

int LowBit(int x) {
	return x & -x;
}

void Add(int x , int d) {
	int k = x;
	while(x <= N) {
		C1[x] += d;
		C2[x] += d * k;
		x += LowBit(x);
	}
}

int GetSum(int x) {
	int res = 0;
	int d = x;
	while(x) {
		res += C1[x] * (d + 1) - C2[x];
		x -= LowBit(x);
	}
	return res;
}

struct Node {
	int l , r;
	mutable int Val;
	Node(const int &il , const int &ir , const int &iv) : l(il) , r(ir) , Val(iv) { }
	const bool operator < (const Node &o) const { 
        return l < o.l; 
    }
};

set<Node> ODT;

typedef set<Node>::iterator sit;

sit Split(int Pos) {
	sit it = ODT.lower_bound(Node(Pos , 0 , 0));
	if(it != ODT.end() && it -> l == Pos) return it;
	it--;
	int l = it -> l;
	int r = it -> r;
	int v = it -> Val;
	ODT.erase(it);
	ODT.insert(Node(l , Pos - 1 , v));
	return ODT.insert(Node(Pos , r , v)).first;
}

void Assign(int l , int r , int v) {
    sit itr = Split(r + 1);
    sit itl = Split(l);
    sit itll = itl; 
    while(itl != itr) {
    	Add(itl -> l, abs(itl -> Val - v));
        Add(itl -> r + 1, -abs(itl -> Val - v));
		itl = ODT.erase(itl);
	}
    ODT.insert(Node(l , r , v));
}


signed main() {
	scanf("%lld%lld" ,&N ,&M);
	for(int i = 1; i <= N; i++) ODT.insert(Node(i , i , i));
	while(M--) {
		int op , l , r , v;
		scanf("%lld%lld%lld" ,&op ,&l ,&r);
		if(op == 1) {
			scanf("%lld" ,&v);
			Assign(l , r , v);
		}
		else {
			printf("%lld\n" ,GetSum(r) - GetSum(l - 1));
		}
	}
	return 0;
}