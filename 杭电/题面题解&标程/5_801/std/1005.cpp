#include <bits/stdc++.h>
using namespace std;
#define cs const
#define re register
#define pb push_back
#define pii pair<int, int>
#define ll long long
#define y1 shinkle
#define fi first
#define se second
#define bg begin
namespace IO {

cs int RLEN = 1 << 22 | 1;
char ibuf[RLEN], *ib, *ob;
inline char gc() {
    (ib == ob) && (ob = (ib = ibuf) + fread(ibuf, 1, RLEN, stdin));
    return (ib == ob) ? EOF : *ib++;
}
inline int read() {
    char ch = gc();
    int res = 0;
    bool f = 1;
    while (!isdigit(ch)) f ^= ch == '-', ch = gc();
    while (isdigit(ch)) res = (res * 10) + (ch ^ 48), ch = gc();
    return f ? res : -res;
}
inline ll readll() {
    char ch = gc();
    ll res = 0;
    bool f = 1;
    while (!isdigit(ch)) f ^= ch == '-', ch = gc();
    while (isdigit(ch)) res = (res * 10) + (ch ^ 48), ch = gc();
    return f ? res : -res;
}
inline char readchar() {
    char ch = gc();
    while (isspace(ch)) ch = gc();
    return ch;
}
inline int readstring(char *s) {
    int top = 0;
    char ch = gc();
    while (isspace(ch)) ch = gc();
    while (!isspace(ch) && ch != EOF) s[++top] = ch, ch = gc();
    s[top + 1] = '\0';
    return top;
}

}  // namespace IO
using IO::read;
using IO::readchar;
using IO::readll;
using IO::readstring;
template <typename tp>
inline void chemx(tp &a, tp b) { (a < b) ? (a = b) : 0; }
template <typename tp>
inline void chemn(tp &a, tp b) { (a > b) ? (a = b) : 0; }

cs int N = 100005;
int a, b, c, d;
int k[4];
int cnt[4];
int val[4][N], sm[4][N];
int ttt;
int ans;
void calc() {
    ttt++;
    int res = 0;
    // for(int i=0;i<4;i++){
    //     for(int j=1;j<=min(k[i],cnt[i]);j++){
    //         res+=val[i][j];
    //     }
    // }
    for (int i = 0; i < 4; i++) {
        res += sm[i][min(k[i], cnt[i])];
    }
    ans = max(ans, res);
}
int main() {
    //    freopen("1.in","r",stdin);
    int T = read();
    while (T--) {
        ans = 0;
        for (int i = 0; i < 4; i++) cnt[i] = k[i] = 0;
        a = read(), b = read(), c = read(), d = read();
        for (int i = 0; i < 4; i++) {
            k[i] = read();
            for (int j = 1; j <= k[i]; j++) {
                val[i][j] = read();
            }
            sort(val[i] + 1, val[i] + k[i] + 1);
            reverse(val[i] + 1, val[i] + k[i] + 1);
            for (int j = 1; j <= k[i]; j++) sm[i][j] = sm[i][j - 1] + val[i][j];
        }
        cnt[0] = a;
        for (int i = 0; i <= b; i++) {  // i*2个1*1,b-i个1*2
            cnt[0] += i * 2,
                cnt[1] += b - i;
            for (int j = 0; j <= c; j++)  // j*3个1*1,k个1*1,k个1*2，c-j-k个1*3
                for (int k = 0; j + k <= c; k++) {
                    cnt[0] += j * 3;
                    cnt[0] += k;
                    cnt[1] += k;
                    cnt[2] += c - j - k;
                    // 4*1 1*2+2*1 2*2 1*4
                    for (int l = 0; l <= d; l++)  // l*4个1*1,m个1*2,m*2个1*1,r个2*2,(d-r-l-m)*2个1*2
                        for (int m = 0; l + m <= d; m++)
                            for (int r = 0; r + l + m <= d; r++) {
                                cnt[0] += l * 4;
                                cnt[0] += m * 2;
                                cnt[1] += m;
                                cnt[3] += r;
                                cnt[1] += (d - r - l - m) * 2;
                                calc();
                                cnt[0] -= l * 4;
                                cnt[0] -= m * 2;
                                cnt[1] -= m;
                                cnt[3] -= r;
                                cnt[1] -= (d - r - l - m) * 2;
                            }
                    cnt[0] -= j * 3;
                    cnt[0] -= k;
                    cnt[1] -= k;
                    cnt[2] -= c - j - k;
                }
            cnt[0] -= i * 2,
                cnt[1] -= b - i;
        }
        // cerr<<ttt<<"\n";
        cout << ans << '\n';
    }
}
// 2e5
// 66825
// 7e4*50