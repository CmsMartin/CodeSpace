#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e10;

struct SegmentTree {
	int LeftTree;
	int RightTree;
	int Value;
	SegmentTree(int l = 0 , int r = 0 , int v = 0) : LeftTree(l) , RightTree(r) , Value(v) { };
} Tree[100010 * 70];

int root , Cnt , N , L , R;
int Num[100010];

void UpDate(int &root , int l , int r , int val) {
	if(!root) root = ++Cnt;
	Tree[root].Value++;
	if(l == r) return;
	int Mid = l + r >> 1;
	if(val <= Mid) UpDate(Tree[root].LeftTree , l , Mid , val);
	else UpDate(Tree[root].RightTree , Mid + 1 , r , val);
}

int Query(int root , int l , int r , int L , int R) {
	if(!root || l > R || L > r) return 0;
	if(l >= L && r <= R) return Tree[root].Value;
	int Mid = l + r >> 1;
	if(Mid >= R) return Query(Tree[root].LeftTree , l , Mid , L , R);
	else if(Mid < L) return Query(Tree[root].RightTree , Mid + 1 , r , L , R);
	else return Query(Tree[root].LeftTree , l , Mid , L , Mid) + Query(Tree[root].RightTree , Mid + 1 , r , Mid + 1 , R);
}

signed main() {
	scanf("%lld%lld%lld" ,&N ,&L ,&R);
	for(int i = 1; i <= N; i++) {
		scanf("%lld" ,Num + i);
		Num[i] += Num[i - 1];
	}
	long long Ans = 0;
	root = ++Cnt;
	UpDate(root , -INF , INF , 0);
	for(int i = 1; i <= N; i++) {
		Ans += Query(root , -INF , INF , Num[i] - R , Num[i] - L);
		UpDate(root , -INF , INF , Num[i]);
	}
	cout << Ans << endl;
	return 0;
}