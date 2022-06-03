#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

struct Node {
    ll l , r;
    mutable ll v;
    Node(const ll &il , const ll &ir , const ll &iv) : l(il) , r(ir) , v(iv) { }
    inline bool operator < (const Node &o) const { 
        return l < o.l; 
    }
};

typedef set<Node>::iterator sit;

set<Node> ODT;
ll N , M , seed , vmax , Num[100010];

sit Split(ll Pos) {
    sit it = ODT.lower_bound(Node(Pos , 0 , 0));
    if(it != ODT.end() && it -> l == Pos) return it;
    it--;
    ll l = it -> l;
    ll r = it -> r;
    ll v = it -> v;
    ODT.erase(it);
    ODT.insert(Node(l , Pos - 1 , v));
    return ODT.insert(Node(Pos , r , v)).first;
}

void Assign(ll l , ll r , ll v) {
    sit itr = Split(r + 1);
    sit itl = Split(l);
    ODT.erase(itl , itr);
    ODT.insert(Node(l , r , v));
}

void Add(ll l , ll r , ll v) {
    sit itr = Split(r + 1);
    sit itl = Split(l);
    for(sit it = itl ; it != itr; it++) {
        it -> v += v;
    }
}

ll Rank(ll l , ll r , ll k) {
    sit itr = Split(r + 1);
    sit itl = Split(l);
    vector<pair<ll , ll> > v;
    v.clear();
    for(sit it = itl; it != itr; it++) {
        v.push_back(make_pair(it -> v , it -> r - it -> l + 1));
    }
    sort(v.begin() , v.end());
    ll i;
    for(i = 0; i < v.size(); i++) {
        if(v[i].second < k) {
            k -= v[i].second;
        }
        else {
            break;
        }
    }
    return v[i].first;
}

ll BinPower(ll x , ll y , ll p) {
    ll res = 1;
    x %= p;
    while(y) {
        if(y & 1) res = res * x % p;
        x = x * x  % p;
        y >>= 1;
    }
    return res;
}

ll Cal_p(ll l , ll r , const ll x , const ll y) {
    sit itr = Split(r + 1);
    sit itl = Split(l);
    ll Ans = 0;
    for(sit it = itl; it != itr; it++) {
        Ans = (Ans + BinPower(it -> v , x , y) * (it -> r - it -> l + 1) % y) % y;
    }
    return Ans;
}

ll rnd() {
    ll res = seed;
    seed = (seed * 7 + 13) % MOD;
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin >> N >> M >> seed >> vmax;
    for(int i = 1; i <= N; i++) {
        Num[i] = (rnd() % vmax) + 1;
        ODT.insert(Node(i , i , Num[i]));
    }
    for(int i = 1; i <= M; i++) {
        ll op , l , r , x , y;
        op = (rnd() % 4) + 1;
        l = (rnd() % N) + 1;
        r = (rnd() % N) + 1;
        if(l > r) swap(l , r);
        if(op == 3) x = (rnd() % (r - l + 1)) + 1;
        else x = (rnd() % vmax) + 1;
        if(op == 4) y = (rnd() % vmax) + 1;
        if(op == 1) Add(l , r , x);
        else if(op == 2) Assign(l , r , x);
        else if(op == 3) cout << Rank(l , r , x) << endl;
        else cout << Cal_p(l , r , x , y) << endl;
    }
    return 0;
}