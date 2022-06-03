#include <bits/stdc++.h>
using namespace std;

int N , M , unit;
char op[5];
int L , R;
int Num[2400010];
int Sum , Cnt[2400010];
int Ans[2400010];
int ToT_q , ToT_r;

struct Query {
	int l , r , t , id;
	bool operator < (const Query o) const {
		if(l / unit == o.l / unit) {
			if(r / unit == o.r / unit) {
				return id < o.id;
			}
			else {
				return r < o.r;
			}
		}
		return l < o.l;
	}
} Ask_q[2400010] , Ask_r[2400010];

void Add(int x) {
	if(!Cnt[x]) Sum++;
	Cnt[x]++;
}

void Del(int x) {
	Cnt[x]--;
	if(!Cnt[x]) Sum--;
}

void Update(int x , int t) {
	if(Ask_q[x].l <= Ask_r[t].l && Ask_r[t].l <= Ask_q[x].r) {
		Del(Num[Ask_r[t].l]);
		Add(Ask_r[t].r);
	}
	swap(Num[Ask_r[t].l] , Ask_r[t].r);
}

int main() {
	ios::sync_with_stdio(false);
	cin >> N >> M;
	unit = pow(N , 0.666);
	for(int i = 1; i <= N; i++) {
		cin >> Num[i];
	}
	for(int i = 1; i <= M; i++) {
		cin >> op >> L >> R;
		if(op[0] == 'Q') {
			++ToT_q;
			Ask_q[ToT_q].id = ToT_q;
			Ask_q[ToT_q].l = L;
			Ask_q[ToT_q].r = R;
			Ask_q[ToT_q].t = ToT_r;
		}
		else {
			++ToT_r;
			Ask_r[ToT_r].l = L;
			Ask_r[ToT_r].r = R;
		}
	}
	sort(Ask_q + 1 , Ask_q + 1 + ToT_q);
	int l = 1 , r = 0 , t = 0;
	for(int i = 1; i <= ToT_q; i++) {
		while(l > Ask_q[i].l) Add(Num[--l]);
		while(l < Ask_q[i].l) Del(Num[l++]);
		while(r > Ask_q[i].r) Del(Num[r--]);
		while(r < Ask_q[i].r) Add(Num[++r]);
		while(t < Ask_q[i].t) Update(i , ++t);
		while(t > Ask_q[i].t) Update(i , t--);
		Ans[Ask_q[i].id] = Sum;
	}
	for(int i = 1; i <= ToT_q; i++) {
		cout << Ans[i] << endl;
	}
	return 0;
}