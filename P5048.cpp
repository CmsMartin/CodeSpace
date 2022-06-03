#include <bits/stdc++.h>

const int MAXN = 5e5 + 10;
const int BLOCK_SIZE = 710;

namespace IO {
    int _tmp_write[50] = {0}; // __int128_t max
    int _cnt_write = 0;    
#ifdef FILE_IO
    static int8_t _tmp_put = 0;
    static const u_int32_t _max_buf_size = 65536;
    static int8_t _buf[_max_buf_size], *_buf_now = _buf, *_buf_end = _buf;
    static int8_t _obuf[_max_buf_size], *_obuf_now = _obuf;
    #define getchar() (_buf_now == _buf_end && (_buf_end = (_buf_now = _buf) + fread(_buf, 1, _max_buf_size, stdin), _buf_now == _buf_end) ? EOF : *_buf_now++)
    #define putchar(x) do { _tmp_put = x; if (_obuf_now - _obuf >= _max_buf_size) { fwrite(_obuf, _obuf_now - _obuf, 1, stdout); _obuf_now = _obuf; } *_obuf_now++ = _tmp_put; } while (false) // 压行的快乐
    #define main_return do { fwrite(_obuf, _obuf_now - _obuf, 1, stdout); fclose(stdin); fclose(stdout); return 0; } while (false) // main 函数结尾一定要调用！！！
#endif
    template <typename _Tp> inline int read(_Tp& _r) {
        int ch = getchar(); bool f = false; _r = 0;
        while (ch < 48 || ch > 57) { if (ch == EOF) return EOF; if (ch == 45) f ^= 1; ch = getchar(); }
        while (ch > 47 && ch < 58) { _r = (_r << 1) + (_r << 3) + ch - 48; ch = getchar(); }
        if (f) _r = -_r; return ch;
    }
    template <typename _Tp> inline int uread(_Tp& _r) {
        int ch = getchar(); _r = 0;
        while (ch < 48 || ch > 57) { if (ch == EOF) return EOF; ch = getchar(); }
        while (ch > 47 && ch < 58) { _r = (_r << 1) + (_r << 3) + ch - 48; ch = getchar(); }
        return ch;
    }
    template <typename _Tp> inline int sread(_Tp* _r) {
        int ch = getchar(); int cnt = 0; _r[0] = 0;
        while (ch == 9 || ch == 10 || ch == 32 || ch == EOF) { if (ch == EOF) return EOF; ch = getchar(); }
        while (ch != 9 && ch != 10 && ch != 32 && ch != EOF) { _r[cnt++] = ch; _r[cnt] = 0; ch = getchar(); }
        return ch;
    }
    inline int strread(std::string& _r) {
        int ch = getchar(); _r = "";
        while (ch == 9 || ch == 10 || ch == 32 || ch == EOF) { if (ch == EOF) return EOF; ch = getchar(); }
        while (ch != 9 && ch != 10 && ch != 32 && ch != EOF) { _r += ch; ch = getchar(); }
        return ch;
    }
    template <typename _Tp> inline void write(_Tp _w, int8_t _end = 10) {
        if (_w == 0) { putchar(48); return; } if (_w < 0) { putchar(45); _w = -_w; } _cnt_write = 0;
        while (_w) { _tmp_write[_cnt_write++] = _w % 10 + 48; _w /= 10; }
        while (_cnt_write) putchar(_tmp_write[--_cnt_write]);
        putchar(_end); return;
    }
    template <typename _Tp> inline void uwrite(_Tp _w, int8_t _end = 10) {
        if (_w == 0) { putchar(48); return; } _cnt_write = 0;
        while (_w) { _tmp_write[_cnt_write++] = _w % 10 + 48; _w /= 10; }
        while (_cnt_write) putchar(_tmp_write[--_cnt_write]);
        putchar(_end); return;
    }
    template <typename _Tp> inline void swrite(_Tp* _w, int8_t _end = 10) {
        for (int i = 0; i < strlen(_w); i++) putchar(_w[i]);
        putchar(_end); return;
    }
    inline void strwrite(std::string _w, int8_t _end = 10) {
        for (int i = 0; i < _w.size(); i++) putchar(_w[i]);
        putchar(_end); return;
    }
};

int Max(int a , int b) {
    return a > b ? a : b;
}

int Min(int a , int b) {
    return a < b ? a : b;
}

// 以上为卡常

int N , M , Last_Ans , Ans;
int Num[MAXN] , Num2[MAXN]; //数组 + 离散化
int Left[BLOCK_SIZE] , Right[BLOCK_SIZE]; //每个块的左右端点

std::vector<int> Appear[MAXN]; //每个数在 Num 数组中出现的下标
int Lacation[MAXN]; //第 i 个数在 vector 中出现的下标
int Count[MAXN]; //桶

int Interval_Mode[BLOCK_SIZE][BLOCK_SIZE]; //Interval_Mode[i][j] 表示 块i 到 块j 众数出现次数

int GetBel(int Pos) {
    return (Pos - 1) / BLOCK_SIZE + 1;
}

void InItBlock() {
    for(int i = 1; i <= GetBel(N); i++) { //预处理每个块的左右端点
        Left[i] = Right[i - 1] + 1;
        Right[i] = i * BLOCK_SIZE;
    }

    Right[GetBel(N)] = N;

    for(int i = 1; i <= GetBel(N); i++) { //暴力计算 Insertval_Mode 数组
        memset(Count , 0 , sizeof Count);
        for(int j = i; j <= GetBel(N); j++) {
            Interval_Mode[i][j] = Interval_Mode[i][j - 1];
            for(int k = Left[j]; k <= Right[j]; k++) {
                Count[Num[k]]++;
                Interval_Mode[i][j] = Max(Interval_Mode[i][j] , Count[Num[k]]);
            }
        }
    }
}

int Query(int l , int r) {
    int res = 0;

    int Bel_l = GetBel(l);
    int Bel_r = GetBel(r);

    if(Bel_l == Bel_r) { // 在同一块，暴力算
        for(int i = l; i <= r; i++) { 
            Count[Num[i]] = 0;
        }
        for(int i = l; i <= r; i++) {
            Count[Num[i]]++;
            res = Max(res , Count[Num[i]]);
        }
    }
    else { //不在同一块
        res = Interval_Mode[Bel_l + 1][Bel_r - 1];
        for(int i = l; i <= Right[Bel_l]; i++) { //完整块左侧是否可能有数字成为众数
            int pos = Lacation[i];
            int v = pos + res;
            while(v < Appear[Num[i]].size() && Appear[Num[i]][v] <= r) { //在数量足够的情况下，改变答案的数量
                res++;
                v++;
            }
        }

        for(int i = Left[Bel_r]; i <= r; i++) { // 完整块右侧是否可能有数字成为众数
            int pos = Lacation[i];
            int v = pos - res;
            while(v >= 0 && Appear[Num[i]][v] >= l) { 
                res++;
                v--;
            }
        }
    }
    return res;
}

int main() {
    IO::read(N);
    IO::read(M);
    for(int i = 1; i <= N; i++) {
        IO::read(Num[i]);
        Num2[i] = Num[i];
    }

    std::sort(Num2 + 1 , Num2 + 1 + N);
    int Sum = std::unique(Num2 + 1 , Num2 + 1 + N) - 1 - Num2;

    for(int i = 1; i <= N; i++) {
        Num[i] = std::lower_bound(Num2 + 1 , Num2 + 1 + Sum , Num[i]) - Num2;
    }

    for(int i = 1; i <= N; i++) {
        Appear[Num[i]].push_back(i);
        Lacation[i] = Appear[Num[i]].size() - 1;
    }

    InItBlock();

    while(M--) {
        int l , r;
        IO::read(l);
        IO::read(r);

        l ^= Last_Ans;
        r ^= Last_Ans;

        Ans = Query(l , r);

        IO::write(Ans , '\n');

        Last_Ans = Ans;
    }

    return 0;
}