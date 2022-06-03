#include <bits/stdc++.h>
using namespace std;

int C1[2060][2060] , C2[2060][2060] , C3[2060][2060] , C4[2060][2060];

int N , M;

int Lowbit(int x) {
    return x & -x;
}

int Sum(int x , int y) {
    int res = 0;
    for(int i = x; i > 0; i -= Lowbit(i)) {
        for(int j = y; j > 0 ;j -= Lowbit(j)) {
            res += C1[i][j] * (x + 1) * (y + 1) - C2[i][j] * (y + 1) - C3[i][j] * (x + 1) + C4[i][j];
        }
    }
    return res;
}

void Add(int x , int y , int d , int n , int m) {
    for(int i = x; i <= n; i += Lowbit(i)) {
        for(int j = y; j <= m; j += Lowbit(j)) {
            C1[i][j] += d;
            C2[i][j] += d * x;
            C3[i][j] += d * y;
            C4[i][j] += d * x * y;
        }
    }
}

char Op;
int a , b , c , d , delta;

int main() {
    cin >> Op >> N >> M;
    while(cin >> Op >> a >> b >> c >> d) {
        if(Op == 'L') {
            cin >> delta;
            Add(a , b , delta , N , M);
            Add(a , d + 1 , -delta , N , M);
            Add(c + 1 , b , -delta , N , M);
            Add(c + 1 , d + 1 , delta , N , M);
        }
        else {
            cout << Sum(c , d) - Sum(c , b - 1) - Sum(a - 1 , d) + Sum(a - 1 , b - 1) << endl;
        }
    }
    return 0;
}