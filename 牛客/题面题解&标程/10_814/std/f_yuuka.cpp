#include<bits/stdc++.h>
using namespace std;

//#define int long long
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
#define all(_array) (_array).begin(),(_array).end()
#define msp(_array) memset(_array,0x3f,sizeof _array)
#define ms0(_array) memset(_array,0,sizeof _array)
#define msn(_array) memset(_array,-1,sizeof _array)
#define mc(_tar,_array) memcpy(_tar,_array,sizeof _tar)
#define Yes cout<<"Yes"<<endl,void()
#define No cout<<"No"<<endl,void()
#define YES cout<<"YES"<<endl,void()
#define NO cout<<"NO"<<endl,void()
#define yes cout<<"yes"<<endl,void()
#define no cout<<"no"<<endl,void()
#define TAK cout<<"TAK"<<endl,void()
#define NIE cout<<"NIE"<<endl,void()
#define OK cerr<<"OK"<<endl,void()
#define pii pair<int,int>
#define endl '\n'

bool bg_memory;
mt19937_64 rnd(time(0));
chrono::_V2::system_clock::time_point bg_clock,en_clock;
int Case=1;
const int mod=1e9+7;
const int inf=1e7;
const int bs=233;
const double eps=1e-6;
const int N=4e5+7,M=1e6+7;

template<class _t1,class _t2>inline void cmax(_t1 &a,_t2 b){a=a<b?b:a;}
template<class _t1,class _t2>inline void cmin(_t1 &a,_t2 b){a=a>b?b:a;}
inline int qp(int a,int b,int p=mod){int res=1;while(b){if(b&1)res=1ll*res*a%p;a=1ll*a*a%p;b>>=1;}return res;}
inline int sqrt(int x,int r){int l=0,ans=0;while(l<=r){if(1ll*mid*mid<=x) ans=mid,l=mid+1;else r=mid-1;}return ans;}

int n;
int a[N];
int lst[M],nxt[N];
set<int> s;
int ans,b1,b2;
int t[N<<2],tg[N<<2],id[N<<2];
void pushup(int p){
    t[p]=t[ls],id[p]=id[ls];
    if(t[rs]>t[p]) t[p]=t[rs],id[p]=id[rs];
}
void pushdown(int p){
    t[ls]+=tg[p],t[rs]+=tg[p];
    tg[ls]+=tg[p],tg[rs]+=tg[p];
    tg[p]=0;
}
void build(int p,int l,int r){
    t[p]=tg[p]=0;
    if(l==r) return id[p]=l,void();
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}
void upd(int p,int l,int r,int ll,int rr,int x){
    if(ll<=l&&rr>=r) return t[p]+=x,tg[p]+=x,void();
    pushdown(p);
    if(ll<=mid) upd(ls,l,mid,ll,rr,x);
    if(rr>mid) upd(rs,mid+1,r,ll,rr,x);
    pushup(p);
}

void Main(){
    
    for(int i=1;i<=n;i++) nxt[i]=lst[a[i]]=0;
    s.clear(),ans=-114514;
    cin>>n;
    build(1,1,n);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=n;i;i--) nxt[i]=lst[a[i]],lst[a[i]]=i;
    for(int i=1;i<=n;i++) lst[a[i]]=i;
    upd(1,1,n,1,1,-inf);
    for(int i=1;i<n;i++){
        upd(1,1,n,i+1,i+1,-inf);
        int cnt=s.count(a[i]);
        if(cnt&&nxt[i]) upd(1,1,n,i+2,nxt[i],-1);
        else if(!cnt&&nxt[i]) upd(1,1,n,nxt[i]+1,lst[a[i]],1);
        if(!cnt) s.insert(a[i]);
        if(t[1]>ans) ans=t[1],b1=i+1,b2=id[1];
    }
    cout<<ans<<endl<<b1<<" "<<b2<<endl;

    return;
}
string RdFile="yuuka";
bool en_memory;

signed main(){
    bg_clock=chrono::high_resolution_clock::now();
// #ifdef ONLINE_JUDGE
    // freopen((RdFile+".in").c_str(),"r",stdin);
    // freopen((RdFile+".out").c_str(),"w",stdout);
// #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>Case;
    while(Case--) Main();
    en_clock=chrono::high_resolution_clock::now();
    auto duration_clock=chrono::duration_cast<chrono::microseconds>(en_clock-bg_clock);
    double duration_count=duration_clock.count()*0.001;
    double memory_used=(&en_memory-&bg_memory)/1024.0/1024;
    // cerr<<"Time:"<<duration_count<<"ms"<<endl;
    // cerr<<"Memory: "<<memory_used<<"MB"<<endl;
    return 0;
}