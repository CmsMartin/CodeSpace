#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

struct SplayTree {
	int Tree[MAXN][2];
	int Fa[MAXN];
	int Tag[MAXN];
	
	void Clear(int x) {
		Tree[x][0] = Tree[x][1] = Fa[x] = Tag[x] = 0; 
	}
	
	int Which(int x) {
		return Tree[Fa[x]][1] == x;
	}
	
	int IsRoot(int x) {
		return Tree[Fa[x]][0] != x && Tree[Fa[x]][1] != x;
	} 
	
	void PushDown(int x) {
		if(Tag[x]) {
			if(Tree[x][0]) swap(Tree[Tree[x][0]][0] , Tree[Tree[x][0]][1]) , Tag[Tree[x][0]] ^= 1;
			if(Tree[x][1]) swap(Tree[Tree[x][1]][0] , Tree[Tree[x][1]][1]) , Tag[Tree[x][1]] ^= 1;
			Tag[x] = 0;
		}
	}
	
	void UpDate(int x) {
		if(!IsRoot(x)) UpDate(Fa[x]);
		PushDown(x);
	}
	
	void Rotate(int x) {
		int y = Fa[x];
		int z = Fa[y];
		int Checkx = Which(x);
		int Checky = Which(y);
		Fa[x] = z;
		if(!IsRoot(y)) Tree[z][Checky] = x;
		Tree[y][Checkx] = Tree[x][Checkx ^ 1];
		Fa[Tree[x][Checkx ^ 1]] = y;
		Tree[x][Checkx ^ 1] = y;
		Fa[y] = x;
	}
	
	void Splay(int x) {
		UpDate(x);
		for(int f = Fa[x]; f = Fa[x] , !IsRoot(x); Rotate(x)) {
			if(!IsRoot(f)) Rotate(Which(x) == Which(f) ? f : x);
		}
	}
	
	void Access(int x) {
		for(int f = 0; x; f = x , x = Fa[x]) {
			Splay(x);
			Tree[x][1] = f;
		}
	}
	
	void MakeRoot(int x) {
		Access(x);
		Splay(x);
		swap(Tree[x][0] , Tree[x][1]);
		Tag[x] ^= 1;
	}
	
	int Find(int x) {
		Access(x);
		Splay(x);
		while(Tree[x][0]) x = Tree[x][0];
		Splay(x);
		return x;
	}
} LCT;

int N , Q , X , Y;
string Op; 

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> Q;
	while(Q--) {
		cin >> Op >> X >> Y;
		if(Op[0] == 'Q') {
			cout << (LCT.Find(X) == LCT.Find(Y) ? "Yes" : "No") << endl;
		}
		if(Op[0] == 'C') {
			if(LCT.Find(X) != LCT.Find(Y)) {
				LCT.MakeRoot(X);
				LCT.Fa[X] = Y;
			}
		}
		if(Op[0] == 'D') {
			LCT.MakeRoot(X);
			LCT.Access(Y);
			LCT.Splay(Y);
			if(LCT.Tree[Y][0] == X && !LCT.Tree[X][1]) {
				LCT.Tree[Y][0] = LCT.Fa[X] = 0;
			}
		}
	}
	return 0;
} 