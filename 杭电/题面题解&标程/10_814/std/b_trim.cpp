#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i <= i##ABRACADABRA; i++)
#define drep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i >= i##ABRACADABRA; i--)
using namespace std;
using ll = long long;
constexpr int N=1e6+10;
constexpr ll inf=1e18;

struct PAM{
  int lst,tot,cnt[N],fail[N],len[N],t[N][27];
  PAM(){init();}
  void init(){
    fail[0]=1;
    lst=0;
    tot=1;
    len[0]=0;
    len[1]=-1;
  }
  void insert(char*s,int i){
    int p=lst;
    while (s[i-len[p]-1]!=s[i])p=fail[p];
    // cout<<p<<'\n';
    if (!t[p][s[i]^96]){
      int q=fail[p],r=++tot;
      len[r]=len[p]+2;
      while (s[i-len[q]-1]!=s[i])q=fail[q];
      fail[r]=t[q][s[i]^96];
      t[p][s[i]^96]=r;
      // cout<<q<<' '<<r<<'\n';
    }
    lst=t[p][s[i]^96];
    ++cnt[lst];
  }
  void bld(char*s){
    s[0]=0;
    int n=strlen(s+1);
    rep(i,1,n)insert(s,i);
  }
} T;

char s[N];
int n,m,sz[N],dep[N],in[N],out[N],hson[N],mxd[N],top[N],num;
bool vis[N];
ll res;
int c[N],a[N],b[N];
vector<int>G[N];

void dfs(int u,int p){
  in[u]=++num;
  sz[u]=1;
  mxd[u]=dep[u]=dep[p]+1;
  for (auto v:G[u]){
    dfs(v,u);
    sz[u]+=sz[v];
    mxd[u]=max(mxd[u],mxd[v]);
    if (mxd[v]>mxd[hson[u]])hson[u]=v;
  }
  out[u]=num;
}
void dfs_top(int u,int t){
  top[u]=t;
  if (hson[u])dfs_top(hson[u],t);
  for (auto v:G[u])if (v!=hson[u])dfs_top(v,v);
}

struct node{int x;ll y;}pool[N*2];
int tot;

struct dq{
  int L,R;
  dq():L(-1),R(-1){}
  void predictsize(int siz){
    L=tot+siz+1;
    R=tot+siz;
    tot+=siz;
  }
  void push_front(node z){pool[--L]=z;}
  void pop_front(){++L;}
  node&front(){return pool[L];}
  node&back(){return pool[R];}
  const node&front()const{return pool[L];}
  const node&back()const{return pool[R];}
  const node&operator[](int x)const{return pool[x+L];}
  node&operator[](int x){return pool[x+L];}
  void swap(dq&ot){
    std::swap(ot.L,L);
    std::swap(ot.R,R);
  }
  int size()const{return R-L+1;}
};

struct dpnode{
  dq g,dp;
  void updatedp(int x,ll y){
    if (!dp.size()){
      dp.push_front({x,y});
      return ;
    }
    if (dp.front().x<=x){
      int id=x-dp.front().x;
      dp[id].y=max(dp[id].y,y);
      return ;
    }
    int st=dp.front().x;
    drep(i,st-1,x+1)dp.push_front({i,-inf});
    dp.push_front({x,y});
  }
  void frontinsconv(int x1,ll y1){
    // static int acnt=0;
    // if (++acnt%10000==0)cout<<acnt<<endl;
    while ((int)g.size()>1){
      auto [x2,y2]=g[0];
      auto [x3,y3]=g[1];
      if ((y3-y2)*(x2-x1)>=(y2-y1)*(x3-x2)){
        // bad (x2,y2)
        g.pop_front();
      }else
        break;
    }
    g.push_front({x1,y1});
  }
  void remakeconv(int to){ // to 之后是重儿子的地盘，前面是轻儿子的地盘，倒着重新维护凸包
    while (g.size()&&g.front().x<=to)g.pop_front();
    int now=0;
    while (now<(int)dp.size()&&dp[now].x<=to)++now;
    drep(i,now-1,0)frontinsconv(dp[i].x,dp[i].y);
  }
  ll ask(ll k){
    while ((int)g.size()>1&&g[1].y-g[0].y>=-k*(g[1].x-g[0].x))g.pop_front();
    return !g.size()?-inf:g.front().x*k+g.front().y;
  }
}dat[N];

void dfs2(int u){
  // cout<<"?? "<<u<<' '<<sz[u]<<'\n';
  if (!hson[u]){
    dat[u].dp.predictsize(dep[u]-dep[top[u]]+1);
    dat[u].g.predictsize(dep[u]-dep[top[u]]+1);
    dat[u].dp.push_front({dep[u],0});
    dat[u].g.push_front({dep[u],0});
    // cout<<u<<" 0"<<endl;
    return ;
  }
  dfs2(hson[u]);
  dat[u].dp.swap(dat[hson[u]].dp);
  dat[u].g.swap(dat[hson[u]].g);
  ll fu=max(0ll,dat[u].ask(a[sz[u]])-1ll*a[sz[u]]*(dep[u]-1)+1ll*c[max(0,T.len[u])]*b[sz[u]]);
  // cout<<"@ "<<u<<' '<<hson[u]<<' '<<fu<<'\n';
  // if (u==1){
    // for (auto [x,y]:dat[u].g)printf("(%lld,%lld)\n",x,y);
  // }
  // cout<<u<<' '<<fu<<endl;
  int mx2d=dep[u];
  // f[u]=max(f[u],f[v]+a[sz[u]]*dep[v]-a[sz[u]]*(dep[u]-1)+c[len[u]]*b[sz[u]]);
  for (auto v:G[u])if (v!=hson[u]){
    dfs2(v);
    mx2d=max(mx2d,mxd[v]);
    rep(i,0,dat[v].g.size()-1)dat[u].updatedp(dat[v].g[i].x,dat[v].g[i].y);
    fu=max(fu,dat[v].ask(a[sz[u]])-1ll*a[sz[u]]*(dep[u]-1)+1ll*c[max(0,T.len[u])]*b[sz[u]]);
    // cout<<"@ "<<u<<' '<<v<<' '<<fu<<'\n';
  }
  dat[u].updatedp(dep[u],fu);
  // cout<<u<<' '<<fu<<endl;
  // if (u==1){
    // for (auto [x,y]:dat[u].g)printf("Z (%lld,%lld)\n",x,y);
  // }
  dat[u].remakeconv(mx2d);
  res=max(res,fu);
  // cout<<u<<' '<<fu<<endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>n>>m;
  string S;
  cin>>S;
  rep(i,1,n)s[i]=S[i-1];
  rep(i,1,m)cin>>a[i];
  rep(i,1,m)cin>>b[i];
  rep(i,0,n)cin>>c[i];
  // int st=clock();
  T.bld(s);
  rep(i,2,T.tot)G[max(T.fail[i],1)].push_back(i)/*,cout<<max(T.fail[i],1)<<" ==> "<<i<<'\n'*/;
  // rep(i,1,T.tot)cout<<i<<' '<<len[i]<<'\n';
  dfs(1,0),dfs_top(1,1);
  dfs2(1);
  cout<<res<<'\n';
  // cerr<<tot<<endl;
  // cerr<<st<<endl;
  // cerr<<clock()-st<<endl;
  return 0;
}