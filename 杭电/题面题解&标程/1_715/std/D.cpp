#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
struct FastMod
{
    static const int N = 1000000;
    ll Mod, k, r, inv_fac[N + 5];
    ll mul(ll a,ll b) {
        __int128 x = (__int128) a * b;
        ll t = x - ((x * r) >> k) * Mod;
        return (t < Mod ? t : t - Mod);
    }
    ll fp(ll a,ll k)
    {
        ll res=1;
        while(k)
        {
            if(k&1)res=mul(res,a);
            a=mul(a,a);
            k>>=1;
        }
        return res;
    }
    ll inv(ll w) {
        return fp(w,Mod-2);
    }
    void init(ll P) {
        Mod = P;
        k = 2 * (__lg(Mod - 1) + 1);
        r = ((__int128) 1 << k) / Mod;
        for (int i = (inv_fac[0] = 1); i <= N; ++i)
            inv_fac[i] = mul(inv_fac[i-1], inv(i));
    }
}fm;
struct FFT
{
    static const int MAXL=1<<18;
    complex<db> rt[MAXL+5];
    void init()
    {
        static const db PI=acos(db(-1));
        for(int i=0;i<MAXL/2;i++)
            rt[i+MAXL/2]=complex<db>(cos(2*PI*i/MAXL),sin(2*PI*i/MAXL));
        for(int i=MAXL/2-1;i>0;i--)rt[i]=rt[i*2];
    }
    void butterfly(complex<db> a[],int n)
    {
        for(int i=1,j=n/2;i<n-1;i++)
        {
            if(i<j)swap(a[i],a[j]);
            int k=n/2;
            while(j>=k)j-=k,k/=2;
            if(j<k)j+=k;
        }
    }
    void fft(complex<db> a[],int n,int ty)
    {
        butterfly(a,n);
        for(int k=1;k<n;k*=2)
            for(int i=0;i<n;i+=k*2)
                for(int j=0;j<k;j++)
                {
                    complex<db> u=a[i+j],v=a[i+j+k]*rt[j+k];
                    a[i+j]=u+v,a[i+j+k]=u-v;
                }
        if(ty==-1)
        {
            reverse(a+1,a+n);
            for(int i=0;i<n;i++)a[i]/=n;
        }
    }
    void dft(complex<db> a[],int n)
    {
        n/=2;
        for(int i=0;i<n;i++)
            a[i]=complex<db>(a[i*2].real(),a[i*2+1].real());
        fft(a,n,1);
        for(int i=0;i<=n/2;++i)
        {
            int j=(n-i)&(n-1);
            complex<db> u=(a[i]+conj(a[j]))/complex<db>(2,0);
            complex<db> v=(a[i]-conj(a[j]))*rt[i+n]/complex<db>(0,2);
            a[i]=u+v,a[i+n]=u-v;
            if(j!=i)a[j]=conj(a[i+n]),a[j+n]=conj(a[i]);
        }
    }
    void idft(complex<db> a[],int n)
    {
        n/=2;
        for(int i=0;i<n;++i)
            a[i]=(a[i]+a[i+n])/complex<db>(2,0)-(a[i]-a[i+n])*conj(rt[i+n])/complex<db>(0,2);
        fft(a,n,-1);
        for(int i=n-1;i>=0;--i)
            a[i*2+1]=a[i].imag(),a[i*2]=a[i].real();
    }
    void convolution(ll f[],ll g[],int n,ll Mod)
    {
        static complex<db> p[3][MAXL+5],q[2][MAXL+5];
        ll Sqt=sqrt(Mod);
        auto split=[&](ll c)
        {
            if(2*c>=Mod)c-=Mod;
            ll x=(c%Sqt+Sqt)%Sqt;
            if(2*x>=Sqt)x-=Sqt;
            return make_pair((c-x)/Sqt,x);
        };
        for(int i=0;i<n;i++)
        {
            tie(p[0][i],p[1][i])=split(f[i]);
            tie(q[0][i],q[1][i])=split(g[i]);
        }
        for(int i=0;i<2;i++)
            dft(p[i],n),dft(q[i],n);
        for(int i=0;i<n;i++)
        {
            p[2][i]=p[0][i]*q[1][i]+p[1][i]*q[0][i];
            p[0][i]=p[0][i]*q[0][i],p[1][i]=p[1][i]*q[1][i];
        }
        for(int i=0;i<3;i++)
            idft(p[i],n);
        for(int i=0;i<n;i++)
        {
            ll tmp[3];
            for(int j=0;j<3;j++)
                tmp[j]=llround(p[j][i].real())%Mod;
            f[i]=(((__int128)tmp[0]*Sqt*Sqt+tmp[1]+tmp[2]*Sqt)%Mod+Mod)%Mod;
        }
    }
    vector<ll> point_value_shift(const vector<ll>& f,int m,ll c,ll Mod)
    {
        static ll fac[MAXL+5],inv_fac[MAXL+5],a[MAXL+5],b[MAXL+5];
        int n=f.size()-1,len=1;
        while(len<n+m)len<<=1;
        for(int i=0;i<len;i++)
        {
            if(i<=n)
            {
                a[i]=fm.mul(f[i],fm.mul(fm.inv_fac[i],fm.inv_fac[n-i]));
                if((n-i)&1)a[i]=(a[i] ? Mod-a[i] : 0);
            }
            else a[i]=0;
        }
        for(int i=(fac[0]=1);i<=n+m;i++)
            fac[i]=fm.mul(c-n-1+i,fac[i-1]);
        inv_fac[n+m]=fm.inv(fac[n+m]);
        for(int i=n+m;i>0;i--)
            inv_fac[i-1]=fm.mul(c-n-1+i,inv_fac[i]);
        for(int i=0;i<len;i++)
            b[i]=(i<n+m ? fm.mul(inv_fac[i+1],fac[i]) : 0);
        convolution(a,b,len,Mod);
        vector<ll> res(m);
        for(int i=0;i<m;i++)
            res[i]=fm.mul(a[i+n],fm.mul(fac[i+n+1],inv_fac[i]));
        return res;
    }
}fft;
struct Solver
{
    ll n,s;
    vector<ll> val,pri;
    int get(ll v)
    {
        return v<s ? v-1 : val.size()-n/v;
    }
    void prepare(ll _n)
    {
        n=_n;
        val.clear();
        for(s=1;s*s<n;s++)
            val.push_back(s);
        for(ll i=n/s;i>=1;i--)
            val.push_back(n/i);
        pri.clear();
        vector<bool> ispri(s+1,1);
        for(ll i=2;i<=s;i++)
        {
            if(ispri[i])pri.push_back(i);
            for(size_t j=0;j<pri.size() && i*pri[j]<=s;j++)
            {
                ispri[i*pri[j]]=0;
                if(i%pri[j]==0)break;
            }
        }
    }
    vector<ll> init_dp(ll Mod)
    {
        ll v=min(s,max((ll)1,Mod/2-1)),inv_v=fm.inv(v);
        vector<ll> pv{1,(v+1)%Mod};
        for(int c=__lg(v)-1,d=1;c>=0;c--)
        {
            vector<ll> qv=fft.point_value_shift(pv,d,d+1,Mod);
            vector<ll> rv=fft.point_value_shift(pv,2*d+1,fm.mul(d,inv_v),Mod);
            pv.insert(pv.end(),qv.begin(),qv.end());
            for(int i=0;i<=2*d;i++)
                pv[i]=fm.mul(pv[i],rv[i]);
            d*=2;
            if(v>>c&1)
            {
                for(int i=0;i<=d;i++)
                    pv[i]=fm.mul(pv[i],i*v+d+1);
                pv.push_back(1);
                for(int j=0;j<=d;j++)
                    pv[d+1]=fm.mul(pv[d+1],(d+1)*v+j+1);
                d+=1;
            }
        }
        for(int i=1;i<=v;i++)
            pv[i]=fm.mul(pv[i],pv[i-1]);
        vector<ll> g(val.size());
        for(size_t i=(g[0]=1),blk=sqrt(s);i<val.size();i++)
        {
            if(val[i]<=fm.N)
                g[i]=fm.inv(fm.inv_fac[val[i]]);
            else if(i+blk<val.size())
            {
                g[i]=g[i-1];
                for(ll j=val[i-1]+1;j<=val[i];j++)
                    g[i]=fm.mul(g[i],j);
            }
            else
            {
                ll blk=min((ll)pv.size(),val[i]/v);
                g[i]=(blk>0 ? pv[blk-1] : 1);
                for(ll j=blk*v+1;j<=val[i];j++)
                    g[i]=fm.mul(g[i],j);
            }
        }
        return g;
    }
    vector<ll> dp(ll Mod)
    {
        vector<ll> f(val),g=init_dp(Mod),g_inv(g);
        for(auto& v : g_inv)v=fm.inv(v);
        ll mx_blk=sqrt(n);
        while(mx_blk*mx_blk<n)++mx_blk;
        vector<vector<ll>> pw(2,vector<ll>(mx_blk+1)),pw_inv(2,vector<ll>(mx_blk+1));
        for(size_t i=0;i<pri.size();i++)
        {
            ll blk=sqrt(n/pri[i]);
            while(blk*blk<n/pri[i])++blk;
            for(int j=0;j<2;j++)
            {
                pw[j][0]=pw_inv[j][0]=1;
                pw[j][1]=(j>0 ? pw[j-1][blk] : pri[i]);
                pw_inv[j][1]=(j>0 ? pw_inv[j-1][blk] : fm.inv(pri[i]));
                for(int k=2;k<=blk;k++)
                {
                    pw[j][k]=fm.mul(pw[j][k-1],pw[j][1]);
                    pw_inv[j][k]=fm.mul(pw_inv[j][k-1],pw_inv[j][1]);
                }
            }
            for(ssize_t j=val.size()-1;j>=0 && val[j]>=pri[i]*pri[i];j--)
            {
                int u=get(val[j]/pri[i]),v=get(pri[i]-1);
                ll sub=f[u]-f[v];f[j]-=sub;
                g[j]=fm.mul(g[j],fm.mul(g[v],fm.mul(g_inv[u],fm.mul(pw_inv[0][sub%blk],pw_inv[1][sub/blk]))));
                g_inv[j]=fm.mul(g_inv[j],fm.mul(g_inv[v],fm.mul(g[u],fm.mul(pw[0][sub%blk],pw[1][sub/blk]))));
            }
        }
        return g;
    }
    ll solve(ll n,ll Mod)
    {
        prepare(n);
        ll res=dp(Mod).back();
        for(auto p : pri)
            for(ll i=p;i<=n/p;i*=p)
                res=fm.mul(res,p);
        return res;
    }
}solver;
int main()
{
    fft.init();
    ll n,Mod;
    scanf("%lld%lld",&n,&Mod);
    fm.init(Mod);
    return 0*printf("%lld\n",solver.solve(n,Mod));
}
