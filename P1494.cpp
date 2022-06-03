#include <iostream>
#include <cmath>
#include <algorithm>
using std::sqrt;
using std::sort;
using std::cin;

const int MAXN = 50010;

int N , M , Maxn;

int Cnt[MAXN] , Col[MAXN];

long long Sum , Ans1[MAXN] , Ans2[MAXN];

struct Ask {
    int L , R , Id;
    bool operator < (const Ask &x) const {
        if(L / Maxn != x.L / Maxn) return L < x.L;
        return(L / Maxn) & 1 ? R < x.R : R > x.R;
    }
} Num[MAXN];

void Add(int Pos) {
    Sum += Cnt[Pos];
    Cnt[Pos]++;
}

void Del(int Pos) {
    Cnt[Pos]--;
    Sum -= Cnt[Pos];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> N >> M;
    Maxn = sqrt(N);
    for(int i = 1; i <= N; i++) cin >> Col[i];
    for(int i = 0; i < M; i++) cin >> Num[i].L >> Num[i].R , Num[i].Id = i;
    sort(Num , Num + M);
    for(int i = 0 , l = 1 , r = 0; i < M; i++) {
        if(Num[i].L == Num[i].R) {
            Ans1[Num[i].Id] = 0;
            Ans2[Num[i].Id] = 1;
            continue;
        }
        while (l > Num[i].L) Add(Col[--l]);
        while (r < Num[i].R) Add(Col[++r]);
        while (l < Num[i].L) Del(Col[l++]);
        while (r > Num[i].R) Del(Col[r--]);
        Ans1[Num[i].Id] = Sum;
        Ans2[Num[i].Id] = (long long)(r - l + 1) * (r - l) / 2;
    }
    for(int i = 0; i < M; i++) {
        if(Ans1[i] != 0) {
            long long g = std::__gcd(Ans1[i] , Ans2[i]);
            Ans1[i] /= g;
            Ans2[i] /= g;
        } 
        else {
            Ans2[i] = 1;
        }
        std::cout << Ans1[i] << "/" << Ans2[i] << std::endl;
    }
    return 0;
}