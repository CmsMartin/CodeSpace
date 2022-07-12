#include <bits/stdc++.h>
using namespace std;

int N, M, Cnt , Son[400010] , T_in[200010] , T_out[200010] , flag[200010] , Tree[200010] , T , Link[200010] , Next[400010];
int Num[200010];
long long C[200010];
bool book[200010];

vector<int> G[200010];

void add(int u , int v) {
    Son[++Cnt] = v;
    Next[Cnt] = Link[u];
    Link[u] = Cnt;
}

int lowbit(int x) {
   return x & -x;
}

void Add(int N , int P , int D) {
   while(P <= N) {
       C[P] += D;
       P += lowbit(P);
   }
}

int GetSum(int P) {
   int ret = 0;
   while(P) {
       ret += C[P];
       P -= lowbit(P);
   }
   return ret;
}


void dfs(int x , int fa) {
	T_in[x] = ++T;
    flag[x] = -flag[fa];
    for(int i = Link[x]; i ; i = Next[i]) {
        if(Son[i] != fa) dfs(Son[i] , x);
    }
    T_out[x] = T;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> Num[i];
    }

    for(int i = 1 ,u ,v; i < N; i++) {
        cin >> u >> v;
        add(u , v);
        add(v , u);
    }
    flag[0] = -1;
    dfs(1 , 0);
   
    for(int i = 1; i <= M; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int x , y;
            cin >> x >> y;
            Add(N , T_in[x] , flag[x] * y);
            Add(N , T_out[x] + 1 , -flag[x] * y);
        }
        else {
            int x;
            cin >> x;
            cout << Num[x] + GetSum(T_in[x]) * flag[x] << endl; 
        }
    }
    return 0;
}
