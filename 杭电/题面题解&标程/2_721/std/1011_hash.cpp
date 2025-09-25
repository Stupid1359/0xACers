#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ul unsigned long long
using namespace std;
const int N=5.2e5+5;
const ul B=131;
ul pp[N],pi[N],qi[N];
ll idx[N];
int n,m,a[N];
string s;
ul qs(ul x,ll y){
    ul z=1;
    while(y){
        if(y&1)z*=x;
        x*=x,y>>=1;
    }
    return z;
}
namespace Fen{
    int a[N],fr;
    ul t[N];
    void init(){
        memset(a,0,(n+1)*4);
        memset(t,0,(n+1)*8);
    }
    void add(int x,int y,ul val){
        for(;x<=n;x+=x&-x)a[x]+=y,t[x]+=val;
    }
    ul sumT(int r){
        ul res=0;
        for(;r;r-=r&-r)res+=t[r];
        return res;
    }
    ul sumT(int l,int r){return sumT(r)-sumT(l-1);}
    int sumA(int r){
        int res=0;
        for(;r;r-=r&-r)res+=a[r];
        return res;
    }
    int sumA(int l,int r){return sumA(r)-sumA(l-1);}
    bool check(int L,int suma,ul sumt){
        if(!suma)return true;
        int p2=fr+suma-1;
        ul bb=qi[p2]-qi[fr-1];
        ul tt=sumt;
        tt*=pi[fr];
        bb*=pp[L+fr];
        return bb==tt;
    }
    int twopoint(int L){
        int x=0;
        int suma=-sumA(L-1);ul sumt=-sumT(L-1);
        for(int i=31-__builtin_clz(n);~i;--i){
            x^=1<<i;
            if(x>n||(x>=L&&!check(L,suma+a[x],sumt+t[x])))x^=1<<i;
            else suma+=a[x],sumt+=t[x];
        }
        return x;
    }
    int two0(int L){
        int x=0;
        int suma=-sumA(L-1);
        for(int i=31-__builtin_clz(n);~i;--i){
            x^=1<<i;
            if(x>n||(x>=L-1&&suma+a[x]))x^=1<<i;
            else suma+=a[x];
        }
        return x-L+1;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    pp[0]=1;for(int i=1;i<N;++i)pp[i]=pp[i-1]*B;
    idx[0]=1;for(int i=1;i<N;++i)idx[i]=idx[i-1]+i+1;
    for(int i=0;i<N;++i)pi[i]=qs(B,idx[i]);
    qi[0]=pi[0];for(int i=1;i<N;++i)qi[i]=qi[i-1]+pi[i];
    int T;cin>>T;
    while(T--)
{
    cin>>n>>m;
    cin>>s;
    for(int i=1;i<=n;++i)a[i]=s[n-i]-'0';
    Fen::init();
    for(int i=1;i<=n;++i)if(a[i])Fen::add(i,1,pp[i]);
    while(m--){
        int opt;cin>>opt;
        if(opt==1){
            int l,r;cin>>r>>l;
            l=n-l+1,r=n-r+1;
            int fr=0;
            fr=Fen::two0(l);
            Fen::fr=fr;
            if(l+fr>r){cout<<"0\n";continue;}
            int R=Fen::twopoint(l);
            if(R>r)R=r;
            int res=Fen::sumA(l,R);
            cout<<res*3+fr-3<<"\n";
        }
        else{
            int x;cin>>x;
            x=n-x+1;
            a[x]^=1;
            if(a[x])Fen::add(x,1,pp[x]);
            else Fen::add(x,-1,-pp[x]);
        }
    }
}
    return 0;
}
