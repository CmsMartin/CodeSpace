#include <bits/stdc++.h>
using namespace std;

#define int long long

const int SIZE = 100010;

struct STree {
    int LeftTree , RightTree;
    int Sum;
    int Add , Prod;
} Tree[SIZE * 4];

int Num[SIZE];
int N , M , P;

void Build(int p , int l, int r) {
    Tree[p].LeftTree = l;
    Tree[p].RightTree = r;
    Tree[p].Prod = 1;
    if(l == r) {
        Tree[p].Sum = Num[l] % P;
        return;
    }
    int Mid = l + r >> 1;
    Build(p * 2 , l , Mid);
    Build(p * 2 + 1 , Mid + 1 , r);
    Tree[p].Sum = Tree[p * 2 + 1].Sum + Tree[p * 2].Sum;
    Tree[p].Sum %= P;
}

void Spread(int p) {
    Tree[2 * p].Sum = (Tree[p].Prod * Tree[2 * p].Sum  + Tree[p].Add * (Tree[p * 2].RightTree - Tree[p * 2].LeftTree + 1) % P) % P;
    Tree[2 * p + 1].Sum = (Tree[p].Prod * Tree[2 * p + 1].Sum + Tree[p].Add * (Tree[p * 2 + 1].RightTree - Tree[p * 2 + 1].LeftTree + 1) % P) % P;

    Tree[2 * p].Prod = Tree[p * 2].Prod * Tree[p].Prod % P;
    Tree[2 * p + 1].Prod = Tree[p * 2 + 1].Prod * Tree[p].Prod % P;

    Tree[2 * p].Add = (Tree[2 * p].Add * Tree[p].Prod + Tree[p].Add) % P;
    Tree[2 * p + 1].Add = (Tree[2 * p + 1].Add * Tree[p].Prod + Tree[p].Add) % P;

    Tree[p].Prod = 1;
    Tree[p].Add = 0;
}

int Ask(int p , int l , int r) {
    if(l <= Tree[p].LeftTree && r >= Tree[p].RightTree) 
        return Tree[p].Sum;
    Spread(p);
    int Val = 0;
    if(l <= (Tree[p].LeftTree + Tree[p].RightTree >> 1))
        Val = (Ask(p * 2 , l , r) + Val) % P;
    if(r > (Tree[p].LeftTree + Tree[p].RightTree >> 1))
        Val = (Val + Ask(p * 2 + 1 , l , r)) % P;
    return Val;
}

void Add(int p , int l , int r , int d) {
    if(l <= Tree[p].LeftTree && r >= Tree[p].RightTree)  {
        Tree[p].Sum = (Tree[p].Sum + d * (Tree[p].RightTree - Tree[p].LeftTree + 1)) % P;
        Tree[p].Add += d;
        Tree[p].Add %= P;
        return;
    }
    Spread(p);
    if(l <= (Tree[p].LeftTree + Tree[p].RightTree >> 1))
        Add(p * 2 , l , r , d);
    if(r > (Tree[p].LeftTree + Tree[p].RightTree >> 1))
        Add(p * 2 + 1 , l , r , d);
    Tree[p].Sum = Tree[p * 2 + 1].Sum + Tree[p * 2].Sum;
    Tree[p].Sum %= P;
}

void Mu(int p , int l , int r , int k) {
    if(l <= Tree[p].LeftTree && r >= Tree[p].RightTree) {
        Tree[p].Add = (Tree[p].Add * k) % P;
        Tree[p].Prod = (Tree[p].Prod * k) % P;
        Tree[p].Sum = (Tree[p].Sum * k) % P;
        return;
    }
    Spread(p);
    if(l <= (Tree[p].LeftTree + Tree[p].RightTree >> 1))
        Mu(p * 2 , l , r , k);
    if(r > (Tree[p].LeftTree + Tree[p].RightTree >> 1))
        Mu(p * 2 + 1 , l , r , k);
    Tree[p].Sum = Tree[p * 2 + 1].Sum + Tree[p * 2].Sum;
    Tree[p].Sum %= P;
}


signed main() {
    ios::sync_with_stdio(false);
    cin >> N >> M >> P;
    for(int i = 1; i <= N; i++)
        cin >> Num[i];
    Build(1 , 1 , N);
    int op , x , y , k;
    while(M--) {
        cin >> op >> x >> y;
        if(op == 1) {
            cin >> k;
            Mu(1 , x , y , k);
        }
        else if(op == 2) {
            cin >> k;
            Add(1 , x , y , k);
        }
        else {
            cout << Ask(1 , x , y) << endl;
        }
    }
    return 0;
}