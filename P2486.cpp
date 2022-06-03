#include <bits/stdc++.h>
using namespace std;

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
    ODT.erase(itl , itr);
    ODT.insert(Node(l , r , v));
}

int Top[100010];
int Dfn[100010];
int Dep[100010];
int Id[100010];
int Fa[100010];
int Val[100010];
int Son[100010];
int Num[100010];
int Size[100010];

vector<int> G[100010];

void Dfs1(int u) {
	Size[u] = 1;
	for(int v : G[u]) {
		if(v == Fa[u]) continue;
		Dep[v] = Dep[u] + 1;
		Fa[v] = u;
		Dfs1(v);
		Size[u] += Size[v];
		if(Size[v] > Size[Son[u]]) Son[u] = v;
	}
}

int Cnt;

void Dfs2(int u , int e) {
	Id[u] = ++Cnt;
	Val[Cnt] = Num[u];
	Top[u] = e;
	if(Son[u] != 0) Dfs2(Son[u] , e);
	for(int v : G[u]) {
		if(v == Fa[u] || v == Son[u]) continue;
		Dfs2(v , v);
	}
}

void Change(int x , int y , int z) {
	while(Top[x] != Top[y]) {
		if(Dep[Top[x]] > Dep[Top[y]]) {
			Assign(Id[Top[x]] , Id[x] , z);
			x = Fa[Top[x]];
		}
		else {
			Assign(Id[Top[y]] , Id[y] , z);
			y = Fa[Top[y]];
		}
	}
	if(Dep[x] > Dep[y]) {
		Assign(Id[y] , Id[x] , z);
	}
	else {
		Assign(Id[x] , Id[y] , z);
	}
}

int Query(int x , int y) {
	int Ans = 0;
	sit itl , itr , it;
	int Last_x = 0;
	int Last_y = 0;
	while(Top[x] != Top[y]) {
		if(Dep[Top[x]] > Dep[Top[y]]) {
			itr = Split(Id[x] + 1);
			itl = Split(Id[Top[x]]);
			for(it = --itr; ; it--) {
				if(Last_x != it -> Val) {
					Last_x = it -> Val;
					Ans++;
				}
				if(it == itl) break;
			}
			x = Fa[Top[x]];
		}
		else {
			itr = Split(Id[y] + 1);
			itl = Split(Id[Top[y]]);
			for(it = --itr; ; it--) {
				if(Last_y != it -> Val) {
					Last_y = it -> Val;
					Ans++;
				}
				if(it == itl) break;
			}
			y = Fa[Top[y]];
		}
	}	
	if(Dep[x] > Dep[y]) {
		itr = Split(Id[x] + 1);
		itl = Split(Id[y]);
		for(it = --itr; ; it--) {
			if(Last_x != it -> Val) {
				Last_x = it -> Val;
				Ans++;
			}
			if(it == itl) break;
		}
	}
	else {
		itr = Split(Id[y] + 1);
		itl = Split(Id[x]);
		for(it = --itr; ; it--) {
			if(Last_y != it -> Val) {
				Last_y = it -> Val;
				Ans++;
			}
			if(it == itl) break;
		}
	}
	return Ans - (Last_x == Last_y); 
}

int N , M;
char op;

int main() {
	scanf("%d%d" ,&N ,&M);
	for(int i = 1; i <= N; i++) {
		scanf("%d" ,Num + i);
	}
	for(int i = 1 , u , v; i < N; i++) {
		scanf("%d%d" ,&u ,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	Dfs1(1);
	Dfs2(1 , 1);
	for(int i = 1; i <= N; i++) {
		ODT.insert(Node(i , i , Val[i]));
	}
	for(int i = 1 , x , y , z; i <= M; i++) {
		scanf(" %c %d %d" ,&op ,&x ,&y);
		if(op == 'C') {
			scanf("%d" ,&z); 
			Change(x , y , z);
		}
		else {
			printf("%d\n" ,Query(x , y));
		}
	}
	return 0;
}