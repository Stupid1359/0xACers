#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define MAXN 4000005
#define ll long long
#define ull unsigned long long

struct PAM{ // sum[i]: 以i结尾的回文串的个数
    int ch[MAXN][26], len[MAXN], fail[MAXN], tot = 1, now = 1, cnt[MAXN];
    void build(string s){
        fail[0] = 1, len[1] = -1;
        s = "#" + s;
        for(int i=1;i<s.size();i++){
            int j, v = (s[i]-'a');
            while(s[i-len[now]-1] != s[i]) now = fail[now];
            if(!ch[now][v]){
                len[++tot] = len[now] + 2;
                j = fail[now];
                while(s[i-len[j]-1] != s[i]) j = fail[j];
                fail[tot] = ch[j][v];
                ch[now][v] = tot;
            }
            now = ch[now][v];
            cnt[now]++;
        }
        for(int i=tot;i>=2;i--) cnt[fail[i]] += cnt[i];
        ll ans = 0;
        for(int i=2;i<=tot;i++) {
            int d = len[i] - len[fail[i]];
            if(len[i] % d != 0) continue;
            ll tmp = len[i] / d;
            // printf("len = %d, d = %d, tmp = %lld, cnt = %d\n", len[i], d, tmp, cnt[i]);
            ans += (tmp-1) * cnt[i];
        }
        cout << (ull)ans << '\n';
    }
} pam; // 定理：长度为n的字符串S最多有n个本质不同回文串

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n; string s;
    cin>>n;
    cin>>s;
    pam.build(s);
    return 0;
}