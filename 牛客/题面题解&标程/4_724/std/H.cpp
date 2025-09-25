#include<bits/stdc++.h>
#define int long long
using namespace std;

const int _base = 123123123321ll;
const int _mod = 283352491887623359ll; 
const int N=57;

/* 
    polynomial f(x) = \sum_{i=0}^d c_i x^{\underline{i}}
    k! c_k = \sum_{i=0}^{k} x_i e_i + constant (mod M)
*/
struct modulo_equation{
    int constant;
    vector<int> x;
};

map<int,int> phi_val;
modulo_equation eq[N];
int n,M;
int f[N],C[N][N],g[N],h[N];

int phi(int x){
    // if (phi_val.find(x)!=phi_val.end()) return phi_val[x];
    int ans=x,tmp=x;
    for (int u=2;u*u<=x;++u){
        if (x%u==0){
            ans=ans/u*(u-1);
            while (x%u==0) x/=u;
        }
    }
    if (x>1) ans=ans/x*(x-1);
    return ans;
}

int modpow(int u,int v,int M){
    int ans=1, t=u;
    while (v){
        if (v&1) ans=ans*t%M;
        t=t*t%M, v>>=1;
    }
    return ans%M;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n>>M;
    // cerr<<phi(25)<<endl;
    C[0][0]=1;
    for (int i=1;i<N;++i){
        C[i][0]=1;
        for (int j=1;j<=i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%M;
    }
    int tmp=M;
    g[0]=1, h[0]=1;
    for (int i=1;i<N;++i) g[i]=g[i-1]*__gcd(i,tmp), tmp/=__gcd(i,tmp), h[i]=h[i-1]*i%M;
    for (int i=0;i<n;++i) cin>>f[i], f[i]=(f[i]-1+M)%M;
    for (int k=0;k<n;++k){
        eq[k].x.resize(n,0);
        eq[k].constant = f[k];
        eq[k].x[k] = 1;
        for (int i=0;i<k;++i) {
            eq[k].constant-=C[k][i]*eq[i].constant%M;
            eq[k].constant+=M, eq[k].constant%=M;
            for (int j=0;j<=i;++j){
                eq[k].x[j]-=C[k][i]*eq[i].x[j]%M;
                eq[k].x[j]+=M, eq[k].x[j]%=M;
            }
        }
    }
    auto check=[&](int u){
        int L=n/2, R=n-n/2;
        vector<pair<int,int>> lst(1<<L);
        for (int mask=0;mask<(1<<L);++mask){
            int hsh=0;
            for (int i=0;i<n;++i){
                hsh=(__int128_t)_base*hsh%_mod;
                int sum=eq[i].constant, mod=(i<n-u?g[i]:M);
                sum%=mod;
                for (int k=0;k<L;++k){
                    if (mask>>k&1) sum=(sum+2*eq[i].x[k])%mod;
                }
                hsh+=sum, hsh%=_mod;
            }
            lst[mask]=make_pair(hsh,mask);
        }
        sort(lst.begin(), lst.end());
        for (int mask=0;mask<(1<<R);++mask){
            int hsh=0;
            for (int i=0;i<n;++i){
                hsh=(__int128_t)_base*hsh%_mod;
                int sum=0, mod=(i<n-u?g[i]:M);
                sum%=mod;
                for (int k=0;k<R;++k){
                    if (mask>>k&1) sum=(sum+2*eq[i].x[k+L])%mod;
                }
                sum=(mod-sum)%mod;
                hsh+=sum, hsh%=_mod;
            }
            auto pos=lower_bound(lst.begin(), lst.end(), make_pair(hsh,0ll))-lst.begin();
            if (pos<(1<<L)&&lst[pos].first==hsh) return mask*(1<<L)+lst[pos].second;
        }
        return -1ll;
    };
    int L=-1, R=n-1;
    while (L<R){
        int md=(L+R)>>1;
        if (check(md+1)!=-1) L=md+1;
        else R=md;
    }
    if (L<0) {cout<<"-1\n"; return 0;}
    auto ret=check(L);
    auto solve=[&](int mask){
        vector<int> c(n,0),nc(n+1,0),_nc(n+1,0);
        for (int i=0;i<n;++i){
            c[i]=eq[i].constant;
            for (int j=0;j<n;++j){
                if (mask>>j&1) c[i]=(c[i]+2*eq[i].x[j])%M;               
            }
            assert(c[i]%g[i]==0);
            c[i]/=g[i], h[i]/=g[i];
            c[i]=c[i]*modpow(h[i],phi(M/g[i])-1,M/g[i])%(M/g[i]);
            // c[i]*=g[i];
        }
        for (int i=n-1;i>-1;--i){
            _nc[0]=c[i];
            for (int k=1;k<n+1;++k) _nc[k]=0;
            for (int k=0;k<n;++k) _nc[k+1]=nc[k];
            for (int k=0;k<n;++k) _nc[k]=(_nc[k]-nc[k]*(i+1)%M+M)%M;
            for (int k=0;k<n+1;++k) nc[k]=_nc[k];
        }
        return nc;
    };
    auto res=solve(ret);
    cout<<n-1-L<<endl;
    for (int i=0;i<n-L;++i) cout<<res[i]<<" ";
}