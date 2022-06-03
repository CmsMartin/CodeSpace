#include <bits/stdc++.h>
using namespace std; 

const int BELONG_SIZE = 316;
const int MAXN = 1e5 + 10;

int N , Q , Bel[MAXN] , Fa[MAXN] , Val[MAXN] , Num[MAXN] , Max[MAXN] , Laze_Tag[MAXN];

int Get_Bel_Left_Pos(int x) {
	return x * BELONG_SIZE - BELONG_SIZE + 1;
}

int Get_Bel_Right_Pos(int x) {
	return min(x * BELONG_SIZE , N);
}

struct Node {
	int Root , Size;
} Block[MAXN / BELONG_SIZE + 10][MAXN];

int GetFather(int x) {
	if(Fa[x] == x) return x;
	else return Fa[x] = GetFather(Fa[x]);
}

void Spread(int x) {
	int l =  Get_Bel_Left_Pos(x);
	int r =  Get_Bel_Right_Pos(x);
	for(; l <= r; l++) {
		Num[l] = Val[GetFather(l)];
		Block[x][Num[l]].Root = Block[x][Num[l]].Size = 0;
		Num[l] -= Laze_Tag[x];
	}
	Laze_Tag[x] = 0;
	l =  Get_Bel_Left_Pos(x);
	r =  Get_Bel_Right_Pos(x);	
	for(; l <= r; l++) {
		Fa[l] = 0;
	}
}

void InIt(int x) {
	Max[x] = 0;
	int l =  Get_Bel_Left_Pos(x);
	int r =  Get_Bel_Right_Pos(x);
	for(; l<= r; l++) {
		Max[x] = max(Max[x] , Num[l]);
		Block[x][Num[l]].Size++;
		if(Block[x][Num[l]].Root) {
			Fa[l] = Block[x][Num[l]].Root;
		}
		else {
			Val[l] = Num[l];
			Block[x][Num[l]].Root = Fa[l] = l;
		}
	}
}

void Merge(int x , int a , int b) {
	if(Block[x][b].Root) {
		Fa[Block[x][a].Root] = Block[x][b].Root;
	}
	else {
		Block[x][b].Root = Block[x][a].Root;
		Val[Block[x][a].Root] = b;
	}
	Block[x][b].Size += Block[x][a].Size;
	Block[x][a].Root = Block[x][a].Size = 0;
}

void UpDate_Tag(int x , int tag) {
	if(tag <= Max[x] - Laze_Tag[x] - tag) {
		for(int i = Laze_Tag[x] + 1; i <= Laze_Tag[x] + tag; i++) {
			if(Block[x][i].Root) {
				Merge(x , i , i + tag);
			}
		}
		Laze_Tag[x] += tag;
	}
	else {
		for(int i = Max[x]; i > Laze_Tag[x] + tag; i--) {
			if(Block[x][i].Root) {
				Merge(x , i , i - tag);
			}
		}
		Max[x] = min(Max[x] , Laze_Tag[x] + tag);
	}
}

void Change(int x , int l , int r) {
	int p = Bel[l];
	int q = Bel[r];
	Spread(p);
	if(p != q) Spread(q);
	if(p != q) {
		for(int i = l; i <= Get_Bel_Right_Pos(p); i++) {
			if(Num[i] > x) 
				Num[i] -= x; 
		}
		for(int i = Get_Bel_Left_Pos(q); i <= r; i++) {
			if(Num[i] > x) 
				Num[i] -= x; 
		}
		for(int i = p + 1; i <= q - 1; i++) {
			UpDate_Tag(i , x);
		}
		InIt(p);
		InIt(q); 
	}
	else {
		for(int i = l; i <= r; i++) {
			if(Num[i] > x) 
				Num[i] -= x; 
		}
		InIt(p);
	}
}

int Query(int x , int l , int r) {
	int p = Bel[l];
	int q = Bel[r];
	int ans = 0;
	if(p != q) {
		for(int i = l; i <= Get_Bel_Right_Pos(p); i++) {
			if(Val[GetFather(i)] - Laze_Tag[p] == x) 
				ans++;
		}
		for(int i = Get_Bel_Left_Pos(q); i <= r; i++) {
			if(Val[GetFather(i)] - Laze_Tag[q] == x) 
				ans++;
		}
		for(int i = p + 1; i <= q - 1; i++) {
			if(x + Laze_Tag[i] <= 100000)
				ans += Block[i][x + Laze_Tag[i]].Size;
		}
	}
	else {
		for(int i = l; i <= r; i++) {
			if(Val[GetFather(i)] - Laze_Tag[p] == x) 
				ans++;
		}
	}
	return ans;
}

int main() {
	scanf("%d%d" ,&N ,&Q);
	for(int i = 1; i <= N; i++) {
		scanf("%d" ,Num + i);
		Bel[i] = (i - 1) / BELONG_SIZE + 1; 
	}
	for(int i = Bel[1]; i <= Bel[N]; i++) {
		InIt(i);
	}
	while(Q--) {
		int op , l , r , x;
		scanf("%d%d%d%d" ,&op ,&l ,&r ,&x);
		if(op == 1) {
			Change(x , l , r);
		}
		else {
			printf("%d\n" ,Query(x , l , r));
		}
	}
	//123
	return 0;
} 