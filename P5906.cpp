#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;

int N , M , Num[MAXN] , Ans[MAXN] , Bel[MAXN];
int Block_Size;
int Num2[MAXN];
int Last[MAXN];

int ToT , Should_Clear[MAXN] , First_Appear[MAXN] , Last_Appear[MAXN];

struct Query {
	int l , r , id;
	bool operator < (const Query &o) {
		return (Bel[l] != Bel[o.l]) ? Bel[l] < Bel[o.l] : r < o.r;
	}
} Ask[MAXN];

int Count(int l , int r) {
	for(int i = l; i <= r; i++) {
		Last[Num[i]] = 0;
	}
	
	int res = 0;
	
	for(int i = l; i <= r; i++) {
		if(!Last[Num[i]]) {
			Last[Num[i]] = i;
		}
		else {
			res = max(res , i - Last[Num[i]]);
		}
	}
	
	return res;
}

int main() {
	scanf("%d" ,&N);
	Block_Size = sqrt(N);
	for(int i = 1; i <= N; i++) {
		scanf("%d" ,Num + i);
		Num2[i] = Num[i];
		Bel[i] = (i - 1) / Block_Size + 1;
	}
	
	sort(Num2 + 1 , Num2 + 1 + N);
	int Size = unique(Num2 + 1 , Num2 + 1 + N) - Num2 - 1;
	
	for(int i = 1; i <= N; i++) {
		Num[i] = lower_bound(Num2 + 1 , Num2 + 1 + Size , Num[i]) - Num2;
	}
	
	scanf("%d" ,&M);
	
	for(int i = 1; i <= M; i++) {
		scanf("%d%d" ,&Ask[i].l ,&Ask[i].r);
		Ask[i].id = i;
	}
	
	sort(Ask + 1 , Ask + 1 + M);
	
	for(int i = 1 , j = 1; j <= Bel[N]; j++) {
		int Right = min(N , j * Block_Size);
		int l = Right + 1;
		int r = l - 1;
		int ans = 0;
		
		ToT = 0;
		
		for(; Bel[Ask[i].l] == j; i++) {
			if(Bel[Ask[i].r] == j) {
				Ans[Ask[i].id] = Count(Ask[i].l , Ask[i].r);
				continue;
			}
			while(r < Ask[i].r) {
				r++;
				Last_Appear[Num[r]] = r;
				if(!First_Appear[Num[r]]) {
					First_Appear[Num[r]] = r;
					Should_Clear[++ToT] = Num[r];
				}
				
				ans = max(ans , r - First_Appear[Num[r]]);
			}
			
			int Ans_Right = ans;
			
			while(l > Ask[i].l) {
				l--;
				if(Last_Appear[Num[l]]) {
					ans = max(ans , Last_Appear[Num[l]] - l);
				}
				else {
					Last_Appear[Num[l]] = l;
				}
			}
			
			Ans[Ask[i].id] = ans;
			
			while(l <= Right) {
				if(Last_Appear[Num[l]] == l) Last_Appear[Num[l]] = 0;
				l++;
			}
			
			ans = Ans_Right;
		}
		
		for(int i = 1; i <= ToT; i++) {
			Last_Appear[Should_Clear[i]] = First_Appear[Should_Clear[i]] = 0;
		}
		
		ToT = 0;
	}
	
	for(int i = 1; i <= M; i++) {
		printf("%d\n" ,Ans[i]);
	}
	return 0;
}