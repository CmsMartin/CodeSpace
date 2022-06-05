#include <bits/stdc++.h>
using namespace std;

char gc() {
    static char now[1 << 20], *S, *T;
    if (T == S) {
        T = (S = now) + std::fread(now, 1, 1 << 20, stdin);
        if (T == S) return EOF;
    }
    return *S++;
}
template <typename T>
void read(T &x) {
    x = 0;
    char c = gc();
    while (c < '0' || c > '9') c = gc();
    x = c - '0';
    while ((c = gc()) >= '0' && c <= '9') x = x * 10 + c - '0';
}
template <typename T, typename... Args>
void read(T &x, Args &...args) {
    read(x);
    read(args...);
}

const int MAXN = 20010;

int Num[MAXN] , Temp[MAXN] , N , M , Num2[MAXN] , l , r , Block;

long long Sum;

int Cnt1[600][600];
int Cnt2[600][MAXN];

int Left[600] , Right[600] , Bel[MAXN];

void Merge(int l1 , int r1 , int l2 , int r2) {
	int ToT = 0;
	while(l1 <= r1 && l2 <= r2) {
		if(Num[l1] <= Num[l2]) {
			Temp[++ToT] = Num[l1++];
		}
		else {
			Temp[++ToT] = Num[l2++];
			Sum += r1 - l1 + 1;
		}
	}
	while(l1 <= r1) Temp[++ToT] = Num[l1++];
	while(l2 <= r2) Temp[++ToT] = Num[l2++];
	
	for(int i = ToT , j = r2; i >= 1; i--, j--) {
        Num[j] = Temp[i];
    }
}

void MergeSort(int l , int r) {
	if(l < r) {
		int Mid = l + r >> 1;
		MergeSort(l , Mid);
		MergeSort(Mid + 1 , r);
		Merge(l , Mid , Mid + 1 , r);
	}
}

int Query1(int l , int r , int k) { //查找 < k 的数的个数 
	int Bel_R = Bel[r] , Bel_L = Bel[l];
	
	if(Bel_L == Bel_R) {
		int res = 0;
		
		for(int i = l; i <= r; i++) {
			if(Num2[i] < k) res++;
		}
		
		return res;
	}
	else {
		int res = 0;
		
		for(int i = l; i <= Right[Bel_L]; i++) {
			if(Num2[i] < k) res++;
		}
		
		for(int i = 0; i < Bel[k]; i++) {
			res += Cnt1[Bel_R - 1][i] - Cnt1[Bel_L][i];
		}
		for(int i = (Bel[k] - 1) * Block + 1; i < k; i++) {
			res += Cnt2[Bel_R - 1][i] - Cnt2[Bel_L][i];
		}
		
		for(int i = Left[Bel_R]; i <= r; i++) {
			if(Num2[i] < k) res++;
		}
		
		return res;
	}
}

int Query2(int l , int r , int k) { //查找 > k 的数的个数 
	int Bel_R = Bel[r] , Bel_L = Bel[l];
	
	if(Bel_L == Bel_R) {
		int res = 0;
		
		for(int i = l; i <= r; i++) {
			if(Num2[i] > k) res++;
		}
		
		return res;
	}
	else {
		int res = 0;
		
		for(int i = l; i <= Right[Bel_L]; i++) {
			if(Num2[i] > k) res++;
		}
		
		for(int i = Bel[N]; i > Bel[k]; i--) {
			res += Cnt1[Bel_R - 1][i] - Cnt1[Bel_L][i];
		}
		for(int i = min(Bel[k] * Block , 20000); i > k; i--) {
			res += Cnt2[Bel_R - 1][i] - Cnt2[Bel_L][i];
		}
		
		for(int i = Left[Bel_R]; i <= r; i++) {
			if(Num2[i] > k) res++;
		}
		
		return res;
	}
}

void Swap(int l , int r) {
	int x = Num2[l] , y = Num2[r];
	
	int Bel_R = Bel[r] , Bel_L = Bel[l];
	
	for(int i = Bel_R; i >= Bel_L; i--) {
		Cnt1[i][Bel[x]] -= Cnt1[i - 1][Bel[x]];
		Cnt1[i][Bel[y]] -= Cnt1[i - 1][Bel[y]];
		Cnt2[i][x] -= Cnt2[i - 1][x];
		Cnt2[i][y] -= Cnt2[i - 1][y];
	}
	
	Cnt1[Bel_L][Bel[y]]++;
	Cnt1[Bel_L][Bel[x]]--;
	Cnt2[Bel_L][y]++;
	Cnt2[Bel_L][x]--;
	
	Cnt1[Bel_R][Bel[y]]--;
	Cnt1[Bel_R][Bel[x]]++;
	Cnt2[Bel_R][y]--;
	Cnt2[Bel_R][x]++;
	
	for(int i = Bel_L; i <= Bel_R; i++) {
		Cnt1[i][Bel[x]] += Cnt1[i - 1][Bel[x]];
		Cnt1[i][Bel[y]] += Cnt1[i - 1][Bel[y]];
		Cnt2[i][x] += Cnt2[i - 1][x];
		Cnt2[i][y] += Cnt2[i - 1][y];
	}
	
	swap(Num2[l] , Num2[r]);
}

int main() {
	scanf("%d" ,&N);
	
	Block = sqrt(N * 1.25);
	
	for(int i = 1; i <= N; i++) {
		scanf("%d" ,&Num[i]);
		Num2[i] = Num[i];
	}
	
	for(int i = 1; i <= 20000; i++) {
		Bel[i] = (i - 1) / Block + 1;
	}
	MergeSort(1 , N);
	
	int Size = unique(Num + 1 , Num + 1 + N) - Num - 1;
	
	for(int i = 1; i <= N; i++) {
		Num2[i] = lower_bound(Num + 1 , Num + 1 + Size , Num2[i]) - Num;
	}
	
	for(int i = 1; i <= Bel[N]; i++) {
		Left[i] = Right[i - 1] + 1;
		Right[i] = i * Block;
	}

	Right[Bel[N]] = N;
	
	for(int i = 1; i <= Bel[N]; i++) {
		for(int j = 1; j <= Bel[N]; j++) {
			Cnt1[i][j] = Cnt1[i - 1][j];
		}
		
		for(int j = 1; j <= N; j++) {
			Cnt2[i][j] = Cnt2[i - 1][j];
		}
		
		for(int j = Left[i]; j <= Right[i]; j++) {
			Cnt1[i][Bel[Num2[j]]]++;
			Cnt2[i][Num2[j]]++;
		}
	}
	
	scanf("%d" ,&M);
	
	printf("%lld\n" ,Sum);
	

	while(M--) {
		scanf("%d%d" ,&l ,&r);
		
		if(l > r) swap(l , r);
		
		Sum = Sum - Query1(l + 1 , r - 1 , Num2[l]) + Query2(l + 1 , r - 1 , Num2[l]) + Query1(l + 1 , r - 1 , Num2[r]) - Query2(l + 1 , r - 1 , Num2[r]);
		if(Num2[r] > Num2[l]) Sum++;
		if(Num2[r] < Num2[l]) Sum--;
		
		Swap(l , r);
		
		printf("%lld\n" ,Sum);
	}
	return 0;
}