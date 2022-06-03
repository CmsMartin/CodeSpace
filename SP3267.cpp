#include<bits/stdc++.h>
using namespace std;

#define maxn 1000119

int c[maxn] , a[maxn];
int n , m;
int book[maxn];
int ans[maxn];

struct Node{
    int l , r;
    int pos;
}ask[maxn];

bool cmp(Node x , Node y){ 
    return x.r < y.r;
}

int lowbit(int x){
	return x & (-x);
}
//求1~x的前缀和 
long long GetSum(int x){
	long long ret = 0;
	while(x){
		ret += c[x];
		x -= lowbit(x);
	}
	return ret;
}
//c[x] += d 
void Add(int x , int d , int n){
	while(x <= n){
		c[x] += d;	
		x += lowbit(x);
	}
}
//求第k小 
int kth(int k , int n){
	int x = 0;
	for(int i = 1 << 20; i ;i >>=1){
		if(x + i <= n && k - c[x + i] > 0){
			x += i;
			k -= c[x];
		}
	}
	++x;
	return x;
}

int main()
{
	scanf("%d" ,&n);
	for(int i = 1;i <= n;i++){
		scanf("%d" ,&a[i]);
	}
	scanf("%d" ,&m);
	for(int i = 1 ; i <= m;i++){
        scanf("%d%d" ,&ask[i].l ,&ask[i].r);
        ask[i].pos=i; 
    }
    sort(ask + 1 , ask + 1 + m , cmp);
    int temp = 1;
    for(int i = 1 ; i <= m ; i++)
    {
        for(int j = temp ; j <= ask[i].r ; j++)
        {
            if(book[a[j]]) 
                Add(book[a[j]] , -1 , n);
            Add(j , 1 , n);
            book[a[j]] = j;
        }
        temp = ask[i].r + 1;
        ans[ask[i].pos] = GetSum(ask[i].r) - GetSum(ask[i].l - 1);
    }
    for(int i = 1;i <= m;i++)
    	printf("%d\n" ,ans[i]);
	return 0;
}
