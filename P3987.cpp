#include <bits/stdc++.h>
using namespace std;

#define int long long 

const int MAXN = 4e7 + 10;
const int INF = 1e6 + 10;

int N , M , Num[INF] , Temp[INF] , Len;

long long Bit[INF];
int op , l , r , x;

inline int LowBit(int x) {
	return x & -x;
}

inline void Add(int x , long long d) {
	while(x <= N) {
		Bit[x] += d;
		x += LowBit(x);
	}
}

inline int Ask(int p) {
	int res = 0;
	while(p) {
		res += Bit[p];
		p -= LowBit(p);
	}
	return res;
}

vector<int> Value[INF];
int Left[MAXN] , Right[MAXN] , Id[MAXN] , Heap[MAXN] , Size[MAXN] , Root[INF] , Cnt; 

int New_Node(int i) {
	Size[++Cnt] = 1;
	Id[Cnt] = i;
	Heap[Cnt] = rand();
	return Cnt;
}

void Push_Up(int i){
	Size[i] = 1 + Size[Left[i]] + Size[Right[i]];
}

int Build(int l , int r) {
	if(l > r) return 0;
	int Mid = l + r >> 1; 
	int i = New_Node(Temp[Mid]);
	Left[i] = Build(l , Mid - 1);
	Right[i] = Build(Mid + 1 , r);
	Push_Up(i);
	return i; 
}

int Merge(int x , int y) {
	if(!x || !y) return x | y;
	if(Heap[x] < Heap[y]) {
		Right[x] = Merge(Right[x] , y);
		Push_Up(x);
		return x;
	}
	else {
		Left[y] = Merge(x , Left[y]);
		Push_Up(y);
		return y;
	}
}

void Split(int i ,int k , int& x , int& y) {
	if(!i) x = y = 0;
	else {
		if(Id[i] <= k) {
			x = i;
			Split(Right[i] , k , Right[i] , y);
		}
		else {
			y = i;
			Split(Left[i] , k , x , Left[i]); 
		}
	}
}

void Dfs(int p , int x) {
	if(!p) return;
	Dfs(Left[p] , x);
	if(Num[Id[p]] % x == 0) {
		Add(Id[p] , -Num[Id[p]]);
		Num[Id[p]] /= x;
		Add(Id[p] , Num[Id[p]]);
	}
	if(Num[Id[p]] % x == 0) {
		Temp[++Len] = Id[p];
	}
	Dfs(Right[p] , x);
}

void UpDate(int l , int r , int a) {
	int x , y , z;
	Split(Root[a] , r , x , z);
	Split(x , l - 1 , x , y);
	Len = 0;
	Dfs(y , a);
	int k = Build(1 , Len);
	Root[a] = Merge(Merge(x , k) , z);
}

signed main() {
	srand(time(NULL));
	scanf("%lld%lld" ,&N ,&M);
	for(int i = 1; i <= N; i++) {
		scanf("%lld" ,Num + i);
		Add(i , Num[i]);
		for(int j = 1; j * j <= Num[i]; j++) {
			if(Num[i] % j == 0) {
				Value[j].push_back(i);
				if(j * j != Num[i]) {
					Value[Num[i] / j].push_back(i);
				} 
			}
		}
	}
	for(int i = 1; i <= 5e5; i++) {
		Len = 0;
		for(int j = 0; j < Value[i].size(); j++) {
			Temp[++Len] = Value[i][j];
		}
		Root[i] = Build(1 , Len);
	}
	while(M--) {
		scanf("%lld%lld%lld" ,&op ,&l ,&r);
		if(op == 1) {
			scanf("%lld" ,&x);
			if(x != 1) UpDate(l  , r , x);
		}
		else {
			printf("%lld\n" ,Ask(r) - Ask(l - 1));
		}
	}
	return 0;
}