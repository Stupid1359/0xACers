#include<bits/stdc++.h>
using namespace std;

#define int long long
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
const int N=400+7,M=200+7;

template<class _t1,class _t2>inline void cmax(_t1 &a,_t2 b){a=a<b?b:a;}
template<class _t1,class _t2>inline void cmin(_t1 &a,_t2 b){a=a>b?b:a;}
inline int qp(int a,int b,int p=mod){int res=1;while(b){if(b&1)res=1ll*res*a%p;a=1ll*a*a%p;b>>=1;}return res;}
inline int sqrt(int x,int r){int l=0,ans=0;while(l<=r){if(1ll*mid*mid<=x) ans=mid,l=mid+1;else r=mid-1;}return ans;}

int n,m,k=200;
int a[N],mx;
int ans;
int dp[N][2];

void Main(){
    
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],cmax(mx,a[i]);
    if(n==1) return cout<<0<<endl,void();
    ans=0;
    a[n+1]=0;
    if(m==1){
        for(int i=1;i<=n;i++) a[i]=mx-a[i];
        for(int i=1;i<=n+1;i++) ans+=abs(a[i]-a[i-1]);
        cout<<ans/2<<endl;
    }else{
        ans=inf;
        for(int d=0;d<=k;d++){
            for(int e=d;e<=k;e++){
                msp(dp);
                if(d>=a[1]) dp[1][0]=(d-a[1]);
                if(e>=a[1]) dp[1][1]=(e-a[1]);
                for(int i=2;i<=n;i++){
                    if(d>=a[i]) dp[i][0]=min(dp[i-1][0]+abs((d-a[i])-(d-a[i-1])),dp[i-1][1]+abs((d-a[i])-(e-a[i-1])));
                    if(e>=a[i]) dp[i][1]=min(dp[i-1][0]+abs((e-a[i])-(d-a[i-1])),dp[i-1][1]+abs((e-a[i])-(e-a[i-1])));
                }
                cmin(ans,dp[n][0]+(d-a[n]));
                cmin(ans,dp[n][1]+(e-a[n]));
            }
        }
        cout<<ans/2<<endl;
    }

    return;
}
string RdFile="woodguy";
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