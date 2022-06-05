#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int BS = 620;

namespace Fread
{
    const int SIZE = 1 << 21;
    char buf[SIZE], *S, *T;
    inline char getchar()
    {
        if (S == T)
        {
            T = (S = buf) + fread(buf, 1, SIZE, stdin);
            if (S == T)
                return '\n';
        }
        return *S++;
    }
}
namespace Fwrite
{
    const int SIZE = 1 << 21;
    char buf[SIZE], *S = buf, *T = buf + SIZE;
    inline void flush()
    {
        fwrite(buf, 1, S - buf, stdout);
        S = buf;
    }
    inline void putchar(char c)
    {
        *S++ = c;
        if (S == T)
            flush();
    }
    struct NTR
    {
        ~NTR()
        {
            flush();
        }
    } ztr;
}

#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    return x * f;
}

inline void write(int x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}


int N , M , Num[MAXN + 10] , Bel[MAXN + 10];

int BLOCK , op , l , r , k , x , y;

int Id[BS][MAXN + 10] , ReId[BS][MAXN + 10];
int Left[BS] , Right[BS];
int Pos[MAXN + 10];

int Cnt1[BS][BS] , Cnt2[BS][MAXN + 10];

int Query_Cnt1[BS] , Query_Cnt2[MAXN + 10];

inline void Build(int x) {
    int ToT = 0;
    for(int i = 1; i <= BLOCK; i++) {
        Id[x][ReId[x][i]] = 0;
    }
    for(int i = Left[x]; i <= Right[x]; i++) {
        if(!Id[x][Num[i]]) {
            Id[x][Num[i]] = ++ToT;
            ReId[x][ToT] = Num[i];
        }
    }
    for(int i = Left[x]; i <= Right[x]; i++) {
        Pos[i] = Id[x][Num[i]];
    }
}

inline void UpDateValue(int x) {
    for(int i = Left[x]; i <= Right[x]; i++) {
        Num[i] = ReId[x][Pos[i]];
    }
}

inline void DutyChange(int l , int r , int x , int y) {
    for(int i = l; i <= r; i++) {
        if(Num[i] == x) {
            Cnt1[Bel[l]][Bel[x]]--;
            Cnt1[Bel[l]][Bel[y]]++;
            Cnt2[Bel[l]][x]--;
            Cnt2[Bel[l]][y]++;
            Num[i] = y;
        }
    }
}

inline void Change(int l , int r , int x , int y) {
    if(x == y || Cnt2[Bel[r]][x] - Cnt2[Bel[l] - 1][x] == 0) return;
    for(int i = Bel[N]; i >= Bel[l]; i--) {
        Cnt2[i][x] -= Cnt2[i - 1][x];
        Cnt2[i][y] -= Cnt2[i - 1][y];
        Cnt1[i][Bel[x]] -= Cnt1[i - 1][Bel[x]];
        Cnt1[i][Bel[y]] -= Cnt1[i - 1][Bel[y]];
    }

    if(Bel[l] == Bel[r]) {
        UpDateValue(Bel[l]);
        DutyChange(l , r , x , y);
        Build(Bel[l]);
        for(int i = Bel[l]; i <= Bel[N]; i++) {
            Cnt2[i][x] += Cnt2[i - 1][x];
            Cnt2[i][y] += Cnt2[i - 1][y];
            Cnt1[i][Bel[x]] += Cnt1[i - 1][Bel[x]];
            Cnt1[i][Bel[y]] += Cnt1[i - 1][Bel[y]];
        }
        return;
    }

    UpDateValue(Bel[l]);
    DutyChange(l , Right[Bel[l]] , x , y);
    Build(Bel[l]);

    UpDateValue(Bel[r]);
    DutyChange(Left[Bel[r]] , r , x , y);
    Build(Bel[r]);

    for(int i = Bel[l] + 1; i <= Bel[r] - 1; i++) {
        if(!Cnt2[i][x]) continue;
        if(Cnt2[i][y]) {
            UpDateValue(i);
            DutyChange(Left[i] , Right[i] , x , y);
            Build(i);
        }
        else {
            Cnt1[i][Bel[y]] += Cnt2[i][x];
            Cnt1[i][Bel[x]] -= Cnt2[i][x];
            Cnt2[i][y] = Cnt2[i][x];
            Cnt2[i][x] = 0;
            Id[i][y] = Id[i][x];
            ReId[i][Id[i][x]] = y;
            Id[i][x] = 0;
        }
    }

    for(int i = Bel[l]; i <= Bel[N]; i++) {
        Cnt2[i][x] += Cnt2[i - 1][x];
        Cnt2[i][y] += Cnt2[i - 1][y];
        Cnt1[i][Bel[x]] += Cnt1[i - 1][Bel[x]];
        Cnt1[i][Bel[y]] += Cnt1[i - 1][Bel[y]];
    }
}

inline int Kth(int l , int r , int k) {
	if(Bel[l] == Bel[r]) {
		UpDateValue(Bel[l]);
		for(int i = l; i <= r; i++) {
			Query_Cnt2[i] = Num[i];
		}
		nth_element(Query_Cnt2 + l , Query_Cnt2 + l + k - 1 , Query_Cnt2 + r + 1); 
		int Ans = Query_Cnt2[k + l - 1];
		
		for(int i = l; i <= r; i++) {
			Query_Cnt2[i] = 0;
		}
		
		return Ans;
	}
	
	else {
		UpDateValue(Bel[l]);
		UpDateValue(Bel[r]);
		
		for(int i = l; i <= Right[Bel[l]]; i++) {
			Query_Cnt1[Bel[Num[i]]]++;
			Query_Cnt2[Num[i]]++;
		}
		
		for(int i = Left[Bel[r]]; i <= r; i++) {
			Query_Cnt1[Bel[Num[i]]]++;
			Query_Cnt2[Num[i]]++;
		}
		
		int Sum = 0;
        
        for(int i = 1; i <= (MAXN - 1) / BLOCK + 1; i++) {
        	if(Sum + Query_Cnt1[i] + Cnt1[Bel[r] - 1][i] - Cnt1[Bel[l]][i] >= k) {
        		for(int j = (i - 1) * BLOCK + 1; j <= i * BLOCK; j++) {
        			if(Sum + Query_Cnt2[j] + Cnt2[Bel[r] - 1][j] - Cnt2[Bel[l]][j] >= k) {
        				for(int i = l; i <= Right[Bel[l]]; i++) {
							Query_Cnt1[Bel[Num[i]]] = 0;
							Query_Cnt2[Num[i]] = 0;
						}
					
						for(int i = Left[Bel[r]]; i <= r; i++) {
							Query_Cnt1[Bel[Num[i]]] = 0;
							Query_Cnt2[Num[i]] = 0;
						}
        				return j;
					}
					else Sum += Query_Cnt2[j] + Cnt2[Bel[r] - 1][j] - Cnt2[Bel[l]][j];
				}
			}
			else Sum += Query_Cnt1[i] + Cnt1[Bel[r] - 1][i] - Cnt1[Bel[l]][i];
		}
	}
}

int main() {
	N = read();
	M = read();
	
	BLOCK = sqrt(N * 1.2);
	
	for(int i = 1; i <= N; i++) {
		Num[i] = read();
	}
	
	for(int i = 1; i <= MAXN; i++) {
		Bel[i] = (i - 1) / BLOCK + 1;
	}
	
	for(int i = 1; i <= Bel[N]; i++) {
		Left[i] = Right[i - 1] + 1;
		Right[i] = i * BLOCK;
	}
	
	Right[Bel[N]] = N;
	
	for(int i = 1; i <= Bel[N]; i++)
		Build(i); 
	
	for(int i = 1; i <= Bel[N]; i++) {
		for(int j = 1; j <= Bel[MAXN - 1 - 5]; j++) {
			Cnt1[i][j] = Cnt1[i - 1][j];
		}
		for(int j = 1; j <= MAXN - 5; j++) {
			Cnt2[i][j] = Cnt2[i - 1][j];
		}
		
		for(int j = Left[i]; j <= Right[i]; j++) {
			Cnt1[i][Bel[Num[j]]]++;
			Cnt2[i][Num[j]]++;
		}
	}
	
	while(M--) {
		op = read();
		l = read();
		r = read();
		if(op == 1) {
			x = read();
			y = read();
			Change(l , r , x , y);
		}
		else {
			k = read();
			write(Kth(l , r , k));
			putchar('\n');
		}
	}
    return 0;
}