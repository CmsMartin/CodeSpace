#include <bits/stdc++.h>
using namespace std;

namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a signed integer
	template <class I>
	inline void read (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	// print a signed integer
	template <class I>
	inline void print (I x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: putc;
using io :: print;
using io :: read;

long long N , M , K , Bel[100010] , Size , Num[100010] , T[100010] , Pre[100010] , Ans[100010];

struct Query {
	int  l , r , Id;
	long long Ans;
	
	bool operator < (const Query &x) const {
		return Bel[l] == Bel[x.l] ? r < x.r : l < x.l;
	}
} Ask[100010];

vector<int> Buc;
vector<tuple<int , int , int , int> > V[100010];

int main () {
	read(N);
	read(M);
	read(K);

	if(K > 14) {
		for(int i = 1; i <= M; i++) puts("0");
		return 0;
	}
	
	Size = sqrt(N);
	
	for(int i = 1; i <= N; i++) {
		read(Num[i]);
		Bel[i] = (i - 1) / Size + 1;
	}
	
	for(int i = 1; i <= M; i++) {
		read(Ask[i].l);
		read(Ask[i].r);
		Ask[i].Id = i;
	}

	for(int i = 0; i < 16384; i++) {
		if(__builtin_popcount(i) == K) {
			Buc.push_back(i);
		}
	}
	
	sort(Ask + 1 , Ask + 1 + M);
	for(int i = 1; i <= N; i++) {
		Pre[i] = T[Num[i]];
		for(const auto &x : Buc) ++T[Num[i] ^ x];
	}
	
	memset(T , 0 , sizeof T);
	
	for(int i = 1 , l = 1 , r = 0; i <= M; i++) {
		if(l > Ask[i].l) V[r].emplace_back(Ask[i].l , l - 1 , i , 1);
		while(l > Ask[i].l) Ask[i].Ans -= Pre[--l];
		if(r < Ask[i].r) V[l - 1].emplace_back(r + 1 , Ask[i].r , i , -1);
		while(r < Ask[i].r) Ask[i].Ans += Pre[++r];
		if(l < Ask[i].l) V[r].emplace_back(l , Ask[i].l - 1 , i , -1);
		while(l < Ask[i].l) Ask[i].Ans += Pre[l++];
		if(r > Ask[i].r) V[l - 1].emplace_back(Ask[i].r + 1 , r , i , 1);
		while(r > Ask[i].r) Ask[i].Ans -= Pre[r--];
	}
	
	for(int i = 1; i <= N; i++) {
		for(const auto &x : Buc) ++T[Num[i] ^ x];
		for(const auto &x : V[i]) {
			for(int j = get<0>(x); j <= get<1>(x); j++) {
				if(j <= i && K == 0) Ask[get<2>(x)].Ans += get<3>(x) * (T[Num[j]] - 1);
				else Ask[get<2>(x)].Ans += get<3>(x) * T[Num[j]]; 
			}
		}
	}
	
	for(int i = 1; i <= M; i++) Ask[i].Ans += Ask[i - 1].Ans;
	for(int i = 1; i <= M; i++) Ans[Ask[i].Id] = Ask[i].Ans;
	for(int i = 1; i <= M; i++) {
		print(Ans[i]);
		putc('\n');
	}
}


