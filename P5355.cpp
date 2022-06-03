#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

int N , M , Unit;
int Cnt[MAXN] , Num[MAXN] , Bel[MAXN];
int Ans[MAXN];
bitset<MAXN> S1;
bitset<MAXN> S2;
int Min[MAXN] , Pre[MAXN];

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

struct Query {
	int l , r , id;
};

vector<Query> Ask_4[500];

struct Query2 {
	int opt , l , r , id , which , x;
	friend bool operator < (const Query2 &a , const Query2 &b) {
		return a.which ^ b.which ? a.l < b.l : ((a.which & 1) ? a.r < b.r : a.r > b.r);
	}
} Ask[MAXN];

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) {
		cin >> Num[i];
	}
	Unit = sqrt(N);
	for(int i = 1; i <= N; i++) {
		Bel[i] = (i - 1) / Unit + 1;
	}
	int tot = 0;
	for(int i = 1 , opt , l , r , x; i <= M; i++) {
		cin >> opt >> l >> r >> x;
		if(opt == 4 && x < Unit) {
			Ask_4[x].push_back({l , r , i});
		}
		else {
			Ask[++tot] = (Query2) {opt , l , r , i , Bel[l] , x};
		}
	}
	sort(Ask + 1 , Ask + 1 + tot);
	int L = 1 , R = 0;
	for(int i = 1; i <= tot; i++) {
		while(L < Ask[i].l) Del(Num[L++]);
		while(L > Ask[i].l) Add(Num[--L]);
		while(R < Ask[i].r) Add(Num[++R]);
		while(R > Ask[i].r) Del(Num[R--]);
		if(Ask[i].opt == 1) {
			Ans[Ask[i].id] = (S1 & (S1 >> Ask[i].x)).any();
		}
		if(Ask[i].opt == 2) {
			Ans[Ask[i].id] = (S1 & (S2 >> (N - Ask[i].x))).any();
		}
		if(Ask[i].opt == 3) {
			for(int j = 1; j * j <= Ask[i].x; j++) {
				if(Ask[i].x % j == 0) {
					if(S1[j] && S1[Ask[i].x / j]) {
						Ans[Ask[i].id] = 1;
						break;
					}
				}
			}
		}
		if(Ask[i].opt == 4) {
			for(int j = 1; j * Ask[i].x <= N; j++) {
				if(S1[j] && S1[j * Ask[i].x]) {
					Ans[Ask[i].id] = 1;
					break;
				}
			}
		}
	}
	for(int i = 1; i < Unit; i++) {
		if(Ask_4[i].empty()) continue;
		memset(Pre , 0 , sizeof Pre);
		memset(Min , 0 , sizeof Min);
		int l = 0;
		for(int j = 1; j <= N; j++) {
			Pre[Num[j]] = j;
			if(Num[j] * i <= N) l = max(l , Pre[Num[j] * i]);
			if(Num[j] % i == 0) l = max(l , Pre[Num[j] / i]);
			Min[j] = l;
		}
		for(int j = 0; j < Ask_4[i].size(); j++) {
            Ans[Ask_4[i][j].id] = Ask_4[i][j].l <= Min[Ask_4[i][j].r];
        }
	}	
	for(int i = 1; i <= M; i++) {
		if(Ans[i] == 1) cout << "yuno" << endl;
		else cout << "yumi" << endl;
	}
	return 0;
}