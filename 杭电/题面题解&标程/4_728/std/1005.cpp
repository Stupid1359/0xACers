#include<bits/stdc++.h>
using namespace std;

// #define int long long
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
const int mod=998244353;
const int inf=1e7;
const int bs=233;
const double eps=1e-6;
const int N=3e2+7,M=2e5+7;

template<class _t1,class _t2>inline void cmax(_t1 &a,_t2 b){a=a<b?b:a;}
template<class _t1,class _t2>inline void cmin(_t1 &a,_t2 b){a=a>b?b:a;}
inline int qp(int a,int b,int p=mod){int res=1;while(b){if(b&1)res=1ll*res*a%p;a=1ll*a*a%p;b>>=1;}return res;}
inline int sqrt(int x,int r){int l=0,ans=0;while(l<=r){if(1ll*mid*mid<=x) ans=mid,l=mid+1;else r=mid-1;}return ans;}

int n,m;
string s;
vector<int> son[N];
int fa[N];
bool lf[N];
int dwn[N],cnt;
int dp[N][N];
int pw[N],c[N][N];
int C(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return c[n][m];
}
int dfs(int x,int p){
    if(~dp[x][p]) return dp[x][p];
    dp[x][p]=0;
    int cur=1;
    int pos[N];
    bool is[N];
    for(int j=p;j<=cnt;j++){int tmp=0;
            for(int l=1;l<=cnt;l++) tmp+=rnd();
        for(int i=dwn[j]+1;i<dwn[j+1];i++){
            
            if(s[i]=='L') cur=max(cur-1,1);
            if(s[i]=='R') cur=min(cur+1,(int)son[x].size());
        }
        pos[j+1]=cur;
        is[cur]=0;
    }
    int lfs=0,sum=0,sum2=0;
    for(int i:son[x]) if(lf[i]) lfs++,(sum+=i)%=mod;else (sum2+=i)%=mod;
    int des=0,sz=son[x].size();
    sum=1ll*sum*qp(lfs,mod-2)%mod,sum2=1ll*sum2*qp(sz-lfs,mod-2)%mod;
    int Div=1ll*pw[lfs]%mod*pw[sz-lfs]%mod*qp(pw[sz],mod-2)%mod;
    for(int i=p+1;i<=cnt+1;i++){
        if(i==cnt+1){
            if(is[pos[i]]){
                (dp[x][p]+=1ll*sum*C(sz-des,sz-lfs)%mod*Div%mod)%=mod;
            }else{
                (dp[x][p]+=1ll*sum*C(sz-des-1,sz-lfs)%mod*Div%mod)%=mod;
                (dp[x][p]+=1ll*sum2*C(sz-des-1,sz-lfs-1)%mod*Div%mod)%=mod;
            }
            continue;
        }
        if(is[pos[i]]) continue;
        int fval=0;
        for(int j:son[x]){
            if(lf[j]) continue;
            (fval+=dfs(j,i))%=mod;
        }
        fval=1ll*fval*qp(sz-lfs,mod-2)%mod;
        int prob=1ll*C(sz-des-1,sz-lfs-1)*Div%mod;
        fval=1ll*fval*prob%mod;
        (dp[x][p]+=fval)%=mod;
        is[pos[i]]=1;
        if(des==lfs) break;
        des++;
    }
    return dp[x][p];
}

void Main(){
    
    cin>>n>>s;
    m=s.size();
    s=' '+s;
    cnt=-1;
    for(int i=1;i<=m;i++) if(s[i]=='D') dwn[++cnt]=i;
    dwn[cnt+1]=m+1;
    for(int i=1;i<=n;i++) fa[i]=lf[i]=0,son[i].clear();
    msn(dp);
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        for(int j=1;j<=x;j++){
            int y;
            cin>>y;
            son[i].push_back(y);
            fa[y]=x;
        }
    }
    int rt;
    for(int i=1;i<=n;i++) if(!fa[i]) rt=i;
    for(int i=1;i<=n;i++) if(!son[i].size()) lf[i]=1;
    if(cnt>=0&&!lf[rt]) cout<<dfs(rt,0)<<endl;
    else cout<<rt<<endl;
    
    return;
}
string RdFile="dreak";
bool en_memory;

signed main(){
    bg_clock=chrono::high_resolution_clock::now();
// #ifdef ONLINE_JUDGE
    // freopen((RdFile+".in").c_str(),"r",stdin);
    // freopen((RdFile+".ans").c_str(),"w",stdout);
// #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    pw[0]=1;
    for(int i=1;i<N;i++) pw[i]=1ll*pw[i-1]*i%mod;
    c[0][0]=1;
    for(int i=1;i<N;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }
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