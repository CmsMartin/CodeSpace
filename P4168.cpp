#include <bits/stdc++.h>
using namespace std;

#define L(a) (((a) - 1) * Block_Size + 1)
#define R(a) ((a) * Block_Size)

const int MAXN = 4e4 + 10;

int N , M;
int Block_Size;

int Num1[MAXN] , Num2[MAXN] , Tong[MAXN];

int Sum[210][MAXN] , Size;
int Ans[210][210];

int main() {
	scanf("%d%d" ,&N ,&M);
	Block_Size = sqrt(N);
	for(int i = 1; i <= N; i++) {
		scanf("%d" ,Num1 + i);
		Num2[i] = Num1[i];
	}
	Size = (N - 1) / Block_Size + 1;
	sort(Num2 + 1 , Num2 + 1 + N);
	int size = unique(Num2 + 1 , Num2 + 1 + N) - Num2 - 1;
	for(int i = 1; i <= N; i++) {
		Num1[i] = lower_bound(Num2 + 1 , Num2 + 1 + size , Num1[i]) - Num2;
	}
	for(int i = 1; i <= Size; i++) {
		for(int j = L(i); j <= min(R(i) , N); j++) {
			Sum[i][Num1[j]]++;
		}
		for(int j = 1; j <= size; j++) {
			Sum[i][j] += Sum[i - 1][j];
		}
	}
	for(int i = 1; i <= Size; i++) {
		for(int j = i; j <= Size; j++) {
			int MAX = Ans[i][j - 1];
			for(int k = R(j - 1); k <= min(R(j) , N); k++) {
				if((Sum[j][Num1[k]] - Sum[i - 1][Num1[k]] > Sum[j][MAX] - Sum[i - 1][MAX]) || (Sum[j][Num1[k]] - Sum[i - 1][Num1[k]] == Sum[j][MAX] - Sum[i - 1][MAX] && Num1[k] < MAX)) {
					MAX = Num1[k];	
				}
			}
			Ans[i][j] = MAX;
		}
	}
	int x = 0;
	while(M--) {
		int l , r;
		scanf("%d%d" ,&l ,&r);
		l = (l + x - 1) % N + 1;
		r = (r + x - 1) % N + 1;
		if(l > r) swap(l , r);
		int Bel_l = (l - 1)	/ Block_Size + 1;
		int Bel_r = (r - 1) / Block_Size + 1;
		int MAX = 0;
		if(Bel_r - Bel_l <= 1) {
			for(int i = l; i <= r; i++) {
				Tong[Num1[i]]++;
			}
			for(int i = l; i <= r; i++) {
				if(Tong[Num1[i]] > Tong[MAX] || (Tong[Num1[i]] == Tong[MAX] && Num1[i] < MAX)) {
					MAX = Num1[i];
				}
			}
			
			for(int i = l; i <= r; i++) Tong[Num1[i]] = 0;
		}
		else {
			for(int i = l; i <= R(Bel_l); i++) {
				Tong[Num1[i]]++;
			}
			for(int i = L(Bel_r); i <= r; i++) {
				Tong[Num1[i]]++;
			}
			
			MAX = Ans[Bel_l + 1][Bel_r - 1];
			
			for(int i = l; i <= R(Bel_l); i++) {
				int Pre = Tong[MAX] + Sum[Bel_r - 1][MAX] - Sum[Bel_l][MAX];
				int Now = Tong[Num1[i]] + Sum[Bel_r - 1][Num1[i]] - Sum[Bel_l][Num1[i]];
				if(Now > Pre || (Now == Pre && MAX > Num1[i])) {
					MAX = Num1[i];
				}
			}
			
			for(int i = L(Bel_r); i <= r; i++) {
				int Pre = Tong[MAX] + Sum[Bel_r - 1][MAX] - Sum[Bel_l][MAX];
				int Now = Tong[Num1[i]] + Sum[Bel_r - 1][Num1[i]] - Sum[Bel_l][Num1[i]];
				if(Now > Pre || (Now == Pre && MAX > Num1[i])) {
					MAX = Num1[i];
				}
			}
			
			for(int i = l; i <= R(Bel_l); i++) Tong[Num1[i]] = 0;
			for(int i = L(Bel_r); i <= r; i++) Tong[Num1[i]] = 0;
		}
		x = Num2[MAX];
			
		printf("%d\n" ,x);
	}	
	return 0;
}