#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e6+7;
const int mod=998244353;
const int inv2=(mod+1)/2;
string s;
int sum[N],f[N];
int suf[N],pref[N];
bool ok[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int ans=0;
    cin>>s;
    int n=s.size();
    f[0]=1;
    for (int i=1;i<=n;++i) f[i]=f[i-1]*2%mod;
    for (int i=0;i<n;++i){
        sum[i+1]=sum[i]+(s[i]=='('?1:-1);
    }
    for (int i=n;i>0;--i){
        suf[i]=suf[i+1]+(s[i-1]==')');
    }
    for (int i=1;i<=n;++i){
        pref[i]=pref[i-1]+(s[i-1]=='(');
    }
    int R=1;
    for (int i=1;i<=n;++i){
        R=max(R,i);
        while (R<=n&&sum[R]>1) R++;
        if (s[i-1]=='(') ans=(ans+f[suf[R+1]]*f[pref[i-1]])%mod;
    }
    ans=(ans+f[n/2])%mod;
    for (int i=1;i<=n;++i) ans=ans*inv2%mod;
    cout<<ans;
}