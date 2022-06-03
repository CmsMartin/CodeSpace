#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

int Root , ToT , Fa[MAXN] , Tree[MAXN][2] , Val[MAXN] , Cnt[MAXN] , Size[MAXN];

struct splay {
	void UpDate(int x) {
		Size[x] = Size[Tree[x][0]] + Size[Tree[x][1]] + Cnt[x];
	}
	bool Get(int x) {
		return x == Tree[Fa[x]][1];
	}
	void Rotate(int x) {
		int y = Fa[x];
		int z = Fa[Fa[x]];
		int Check = Get(x);
		Tree[y][Check] = Tree[x][Check ^ 1];
		if(Tree[x][Check ^ 1]) {
			Fa[Tree[x][Check ^ 1]] = y;
		}
		Tree[x][Check ^ 1] = y;
		Fa[y] = x;
		Fa[x] = z;
		if(z) {
			Tree[z][y == Tree[z][1]] = x;
		}
		UpDate(x);
		UpDate(y);
	}
	void Splay(int x) {
		for(int f = Fa[x]; f = Fa[x] , f; Rotate(x)) {
			if(Fa[f]) {
				Rotate(Get(x) == Get(f) ? f : x);
			}
		}
		Root = x;
	}
	void Insert(int k) {
		if(!Root) {
			Val[++ToT] = k;
			Cnt[ToT]++;
			Root = ToT;
			UpDate(Root);
			return;
		}
		int Cur = Root , f = 0;
		while(true) {
			if(Val[Cur] == k) {
				Cnt[Cur]++;
				UpDate(Cur);
				UpDate(f);
				Splay(Cur);
				return;
			}
			f = Cur;
			Cur = Tree[Cur][Val[Cur] < k];
			if(!Cur) {
				Val[++ToT] = k;
				Cnt[ToT]++;
				Fa[ToT] = f;
				Tree[f][Val[f] < k] = ToT;
				UpDate(ToT);
				UpDate(f);
				Splay(ToT);
				break;
			}
		}
	}
	int Rank(int k) {
		int res = 0;
		int Cur = Root;
		while(true) {
			if(k < Val[Cur]) {
				Cur = Tree[Cur][0];
			}
			else {
				res += Size[Tree[Cur][0]];
				if(k == Val[Cur]) {
					Splay(Cur);
					return res + 1;
				}
				res += Cnt[Cur];
				Cur = Tree[Cur][1];
			}
		}
	}
	int Kth(int k) {
		int Cur = Root;
		while(true) {
			if(Tree[Cur][0] && k <= Size[Tree[Cur][0]]) {
				Cur = Tree[Cur][0];
			}
			else {
				k -= Cnt[Cur] + Size[Tree[Cur][0]];
				if(k <= 0) {
					Splay(Cur);
					return Val[Cur];
				}
				Cur = Tree[Cur][1];
			}
		}
	}
	void Find(int x) {
		int Cur = Root;
		if(!Root) return;
		while(Val[Cur] != x) {
			if(Val[Cur] > x) {
				if(!Tree[Cur][0]) break;
				Cur = Tree[Cur][0];
			}
			else {
				if(!Tree[Cur][1]) break;
				Cur = Tree[Cur][1];
			}
		}
		Splay(Cur);
	}
	int Min() {
		int Cur = Tree[Root][0];
		if(!Cur) return Cur;
		while(Tree[Cur][1]) Cur = Tree[Cur][1];
		Splay(Cur);
		return Cur;
	}
	int Max() {
		int Cur = Tree[Root][1];
		if(!Cur) return Cur;
		while(Tree[Cur][0]) Cur = Tree[Cur][0];
		Splay(Cur);
		return Cur;
	}
	void Clear(int x) {
		Tree[x][0] = Tree[x][1] = Fa[x] = Val[x] = Size[x] = Cnt[x] = 0;
	}
	void Delete(int k) {
		Rank(k);
		if(Cnt[Root] > 1) {
			Cnt[Root]--;
			UpDate(Root);
			return;
		}
		if(!Tree[Root][0] && !Tree[Root][1]) {
			Clear(Root);
			Root = 0;
			return;
		}
		if(!Tree[Root][0]) {
			int Cur = Root;
			Root = Tree[Root][1];
			Fa[Root] = 0;
			Clear(Cur);
			return;
		}
		if(!Tree[Root][0]) {
			int Cur = Root;
			Root = Tree[Root][0];
			Fa[Root] = 0;
			Clear(Cur);
		}
		int Cur = Root;
		int x = Min();
		Fa[Tree[Cur][1]] = x;
		Tree[x][1] = Tree[Cur][1];
		Clear(Cur);
		UpDate(Root);
	}
	int GetPre(int x) {
		Insert(x);
		int ans = Val[Min()];
		Delete(x);
		return ans;
	}
	int GetNext(int x) {
		Insert(x);
		int ans = Val[Max()];
		Delete(x);
		return ans;
	}
} tree;

int N , Op , X , M;
string s;
int P[MAXN] , cnt;

int main() {
	cin >> N >> M;
	tree.Insert(0);
	tree.Insert(N + 1);
	while(M--) {
		cin >> s;
		if(s == "D") {
			cin >> X;
			tree.Insert(X);
			P[++cnt] = X;
		}
		else if(s == "R") {
			tree.Delete(P[cnt--]);
		}
		else {
			cin >> X;
			tree.Find(X);
			if(Val[Root] == X) {
				cout << 0 << endl;
			}
			else {
				int Next = tree.GetNext(X);
				int Pre = tree.GetPre(X);
				cout << Next - Pre - 1 << endl;
			}
		}
	}
	return 0;
}