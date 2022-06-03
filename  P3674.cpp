#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

int N , M;
int Cnt[MAXN] , Num[MAXN];
int Ans[MAXN] , unit;
bitset<MAXN> S1;
bitset<MAXN> S2;

struct Query {
	int Opt , L , R , X , id;
	bool operator < (const Query &o) const {
		if(L / unit == o.L / unit) return R < o.R;
		else return L < o.L;
	}
} Ask[MAXN];

void Add(int i) {
	Cnt[i]++;
	if(Cnt[i] == 1) {
		S1[i] = true;
		S2[N - i] = true;
	}
}

void Del(int i) {
	Cnt[i]--;
	if(!Cnt[i]) {
		S1[i] = false;
		S2[N - i] = false;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	unit = sqrt(N);
	for(int i = 1; i <= N; i++) {
		cin >> Num[i];
	}
	for(int i = 1 , op , l , r , x; i <= M; i++) {
		cin >> Ask[i].Opt >> Ask[i].L >> Ask[i].R >> Ask[i].X;
		Ask[i].id = i;
	}
	sort(Ask + 1 , Ask + 1 + M);
	int l = 1 , r = 0;
	for(int i = 1; i <= M; i++) {
		while(l < Ask[i].L) Del(Num[l++]);
		while(l > Ask[i].L) Add(Num[--l]);
		while(r < Ask[i].R) Add(Num[++r]);
		while(r > Ask[i].R) Del(Num[r--]);
		if(Ask[i].Opt == 1) {
			Ans[Ask[i].id] = (S1 & (S1 >> Ask[i].X)).any();
		}
		if(Ask[i].Opt == 2) {
			Ans[Ask[i].id] = (S1 & (S2 >> (N - Ask[i].X))).any();
		}
		if(Ask[i].Opt == 3) {
			for(int j = 1; j * j <= Ask[i].X; j++) {
				if(Ask[i].X % j == 0) {
					if(S1[j] && S1[Ask[i].X / j]) {
						Ans[Ask[i].id] = 1;
						break;
					}
				}
			}
		}
	}
	for(int i = 1; i <= M; i++) {
		if(Ans[i] == 1) cout << "hana" << endl;
		else cout << "bi" << endl;
	}
	return 0;
}