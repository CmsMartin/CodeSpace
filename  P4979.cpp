#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l , r;
    mutable char v;
    Node(const int &il , const int &ir , const char &iv) : l(il) , r(ir) , v(iv) { };
    bool operator < (const Node &o) const {
        return l < o.l;
    } 
};

set<Node> ODT;

typedef set<Node>::iterator sit;

sit Split(int Pos) {
    sit it = ODT.lower_bound(Node(Pos , 0 , 0));
    if(it != ODT.end() && it -> l == Pos) return it;
    it--;
    int l = it -> l;
    int r = it -> r;
    char v = it -> v;
    ODT.erase(it);
    ODT.insert(Node(l , Pos - 1 , v));
    return ODT.insert(Node(Pos , r , v)).first;
}

void Assign(int l , int r , char v) {
    sit itr = Split(r + 1);
    sit itl = Split(l);
    ODT.erase(itl , itr);
    ODT.insert(Node(l , r , v));
}

char Get(int Pos) {
    sit it = Split(Pos);
    return it -> v;
}

bool Check(int l , int r) {
    sit itr = Split(r + 1);
    sit itl = Split(l);
    char c = itl -> v;
    for(sit it = itl; it != itr; it++) {
        if(it -> v != c) {
            return false;
        }
    }
    return true;
}

int N , M , x , y;
char S[500010];
int ToT = 1;
char Last , Op;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d" ,&N);
    scanf("%s" ,S + 1);
    Last = S[1];
    for(int i = 2; i <= N; i++) {
        if(S[i] == Last) {
            ToT++;
        }
        else {
            ODT.insert(Node(i - ToT , i - 1 , Last));
            Last = S[i];
            ToT = 1;
        }
    }
    ODT.insert(Node(N - ToT + 1 , N , Last));
    // for(int i = 0; i < S.size(); i++) ODT.insert(Node(i + 1, i + 1 , S[i]));
    scanf("%d" ,&M);
    while(M--) {
        scanf(" %c %d %d" ,&Op ,&x ,&y);
        if(Op == 'A') {
            scanf(" %s" ,&Op);
            Assign(x , y , Op);
        }
        else {
            if(x == 1 || y == 1 || x == N || y == N) {
                if(Check(x , y)) { printf("Yes\n"); char v = Get(x); Assign(x , y , v);}
                else printf("No\n");
                continue;
            }
            char b = Get(y + 1);
            char a = Get(x - 1);
            if(a == b || !Check(x , y)) printf("No\n");
            else { printf("Yes\n"); char v = Get(x); Assign(x , y , v); }
        }
    }
    return 0;
}