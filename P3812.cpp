#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll N , P[60];
void Insert(ll k) {
	for(ll i = 50; i >= 0; i--) {
		if(!(k & (1ll << i))) continue;
		if(!P[i]) {
			P[i] = k;
			return;
		}
		k ^= P[i];
	}
}

ll Query() {
	ll res = 0;
	for(ll i = 50; i >= 0; i--) res = max(res , (res ^ P[i]));
	return res;
}

signed main() {
	cin >> N;
	while(N--) {
		ll t;
		cin >> t;
		Insert(t);
	}
	cout << Query() << endl;
	return 0;
}