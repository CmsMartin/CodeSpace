#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e6 + 10;

int Num[MAXN] , Num2[MAXN];
int Tree[MAXN * 4] , LeftTree[MAXN * 4] , RightTree[MAXN * 4] , Sum[MAXN * 4];
int Cnt , Len , N , M;

int Build(int l , int r) {
	int rt = ++Cnt;
	if(l >= r) return rt;
	LeftTree[rt] = Build(l , l + r >> 1);
	RightTree[rt] = Build((l + r >> 1) + 1 , r);
	return rt;
}

int UpDate(int p , int l , int r , int x) {
	int rt = ++Cnt;
	Sum[rt] = Sum[p] + 1;
	LeftTree[rt] = LeftTree[p];
	RightTree[rt] = RightTree[p];
	if(l < r) {
        if (x <= l + r >> 1) LeftTree[rt] = UpDate(LeftTree[p] , l , l + r >> 1 , x);
        else  RightTree[rt] = UpDate(RightTree[p], (l + r >> 1) + 1 , r , x);
    }
    return rt;
}

int Query(int p , int q , int l , int r , int k) {
	if(l == r) {
		return Num2[l];	
	}
	int SHW;
	int Sum_x = Sum[LeftTree[q]] - Sum[LeftTree[p]];
	int Sum_y = Sum[RightTree[q]] - Sum[RightTree[p]];
	if(Sum_x > k) {
		SHW = Query(LeftTree[p] , LeftTree[q] , l , l + r >> 1 , k);
		if(SHW > 0) {
			return SHW;
		}
	}
	if(Sum_y > k) {
		SHW = Query(RightTree[p] , RightTree[q] , (l + r >> 1) + 1 , r , k);
		if(SHW > 0) {
			return SHW;
		}
	}
	return -1;
}

int main() {
	scanf("%d%d" ,&N ,&M);
	for(int i = 1; i <= N; i++) {
		scanf("%d" ,Num + i);
		Num2[i] = Num[i];
	}
	sort(Num2 + 1 , Num2 + 1 + N	);
	Len = unique(Num2 + 1 , Num2 + 1 + N) - Num2 - 1;
	Tree[0] = Build(1 , Len);
	for(int i = 1; i <= N; i++) {
		Tree[i] = UpDate(Tree[i - 1] , 1 , Len , lower_bound(Num2 + 1 , Num2 + 1 + Len , Num[i]) - Num2);
	}
	for(int i = 1 , l , r , k; i <= M; i++) {
		scanf("%d%d%d" ,&l ,&r ,&k);
		printf("%d\n" ,Query(Tree[l - 1] , Tree[r] , 1 , Len , (r - l + 1) / k));
	}
	return 0;
}