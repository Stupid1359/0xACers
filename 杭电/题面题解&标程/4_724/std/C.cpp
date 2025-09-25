#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=2e7+7;
const int mod=998244353;
int f[N],rf[N];

int modpow(int u,int v){
    int ans=1, t=u;
    while (v){
        if (v&1) ans=ans*t%mod;
        t=t*t%mod, v>>=1;
    }
    return ans;
}
int C(int u,int v){
    if (u<0||v<0||u<v) return 0;
    return f[u]*rf[v]%mod*rf[u-v]%mod;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    f[0]=1;
    for (int i=1;i<N;++i) f[i]=f[i-1]*i%mod;
    rf[N-1]=modpow(f[N-1],mod-2);
    for (int i=N-1;i>0;--i) rf[i-1]=rf[i]*i%mod;
    int n,m,k;
    // ans=(m-1)!*C(nm-m,m-1-r)*C(m,r), r=nm-1-k-(m-1)
    cin>>n>>m>>k;
    int r=(m-1)-(n*m-1-k-(m-1));
    if (m-1-r<0||r<0) {cout<<0; return 0;}
    int ans=f[m-1]*C(m,r)%mod*rf[m-1-r]%mod;
    for (int i=0;i<m-1-r;++i) ans=ans*((n*m-m)%mod-i+mod)%mod; 
    cout<<ans<<endl;
}