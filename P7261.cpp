#include <bits/stdc++.h>
using namespace std;

struct Color {
    int ToT[30010];
};

Color Mp[650];
int ToT[30010];
int N , C , K , M , l , r;
int Num[300010];

void Query(int l , int r) {
    memset(ToT , 0 , sizeof ToT);
    for(int i = l; i <= r; ) {
        if(i % K == 1 && i + K <= r) {
            for(int p = 1; p <= C; p++) {
                ToT[p] += Mp[i / K + 1].ToT[p];
            }
            i += K;
        }
        else if(i % K == 1) {
            for(int j = i; j <= r; j++) {
                ToT[Num[j]]++;
            }
            break;
        }
        else if(i % K != 1) {
            while(i % K != 1) {
                ToT[Num[i]]++;
                i++;
                if(i > r) break;
            }
        }
    }
    for(int i = 1; i <= C; i++) {
        if(ToT[i] > ((double)(r - l + 1) / (double)2)) {
            cout << "yes " << i << endl;
            return;
        }
    }
    cout << "no" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> C;
    for(int i = 1; i <= N; i++) cin >> Num[i];
    K = N / log2(N);
    for(int i = 1 , tot = 1; i + K <= N; i += K , tot++) {
        for(int l = i; l <= N && l <= i + K - 1; l++) {
            Mp[tot].ToT[Num[l]]++;
        }
    }
    cin >> M;
    for(int i = 1; i <= M; i++) {
        cin >> l >> r;
        Query(l , r);
    }
    return 0;
}