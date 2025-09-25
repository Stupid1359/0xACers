#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>P;
const int N=50005,M=50005,K=253,W=4,CNT=(M*2+K)*2+5,inf=~0U>>1;
int Case,n,m,cnt,A,B,C,lim,i,x,y,u,v,w,o,pre[N];
P p[N];
vector<P>cons[N];
vector<int>g[CNT],h[CNT];
bool vis[CNT];
int scc,from[CNT],t,s[CNT];
ull mask[CNT][W],reach[CNT][W];
inline void add_edge(int x,int y){
  g[x].emplace_back(y);
  h[y].emplace_back(x);
}
struct Pool{
  vector<int>v;
  int st,len;
  bool big;
  void clear(){v.clear();}
  void ext(int x){v.emplace_back(x);}
  int find(int x){
    int idx=lower_bound(v.begin(),v.end(),x)-v.begin();
    return st+idx;
  }
  int get_prev(int x){
    if(!len)return -1;
    const auto&it=lower_bound(v.begin(),v.end(),x);
    if(it==v.begin())return -1;
    int idx=it-v.begin();
    return st+idx-1;
  }
  void build(){
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    len=v.size();
    st=cnt;
    cnt+=len;
  }
  void add_adj_edges(){
    for(int i=1;i<len;i++){
      add_edge(st+i-1,st+i);
      add_edge(st+i+cnt,st+i-1+cnt);
    }
  }
  void make_pre(){
    big=len>lim;
    if(big)for(int i=0;i+1<len;i++)for(int j=v[i];j<v[i+1];j++)pre[j]=st+i;
  }
}upper[N];
struct E{
  int x,y,w;
  E(){}
  E(int _x,int _y,int _w){x=_x,y=_y,w=_w;}
}e[M],a[M],b[M],c[K];
inline int dis(const P&a,const P&b){
  ll dx=a.first-b.first,dy=a.second-b.second;
  ll tmp=dx*dx+dy*dy;
  ll ret=sqrt(tmp)-3;
  ret=max(ret,0LL);
  while(ret*ret<tmp)ret++;
  return ret;
}
inline void add_or(int x,int y){
  add_edge(x+cnt,y);
  add_edge(y+cnt,x);
}
inline void add_nand(int x,int y){
  add_edge(x,y+cnt);
  add_edge(y,x+cnt);
}
inline void add_constraints(const Pool&a,const Pool&b,int w){
  if(b.big){
    for(int i=0;i<a.len;i++){
      int r=w-a.v[i]-1;
      if(r<b.v[0])return;
      add_nand(a.st+i,r<b.v[b.len-1]?pre[r]:(b.st+b.len-1));
    }
  }else for(int i=0,j=b.len-1;i<a.len;i++){
    while(j>=0&&a.v[i]+b.v[j]>=w)j--;
    if(j<0)return;
    add_nand(a.st+i,b.st+j);
  }
}
void dfs(int x){
  vis[x]=1;
  for(const auto&y:h[x])if(!vis[y])dfs(y);
  s[++t]=x;
}
inline void go(int x){
  static int q[CNT];
  static ull now[W];
  int h=1,t=1,i;
  q[1]=x;
  vis[x]=0;
  from[x]=++scc;
  for(i=0;i<W;i++)now[i]=0;
  while(h<=t){
    x=q[h++];
    for(i=0;i<W;i++)now[i]|=mask[x][i];
    for(const auto&y:g[x])if(vis[y]){
      q[++t]=y;
      vis[y]=0;
      from[y]=scc;
    }else if(from[y]<scc){
      int z=from[y];
      now[0]|=reach[z][0];
      now[1]|=reach[z][1];
      now[2]|=reach[z][2];
      now[3]|=reach[z][3];
    }
  }
  for(i=0;i<W;i++)reach[scc][i]=now[i];
}
inline void up(int&x,int y){x>y?(x=y):0;}
inline bool check(int x,int y){return reach[from[c[x].y]][y>>6]>>(y&63)&1;}
inline int solve(){
  int i,j;
  for(i=0;i<cnt;i++)if(from[i]==from[i+cnt])return 0;
  int ans=inf;
  for(i=0;i<C;i++){
    if(check(i,i))up(ans,c[i].w);
    for(j=0;j<i;j++)if(check(i,j)&&check(j,i))up(ans,c[i].w+c[j].w);
  }
  if(ans==inf)ans=-1;
  return ans;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n>>m>>A>>B>>C;
    for(i=0;i<n;i++)cin>>p[i].first>>p[i].second;
    for(i=0;i<m;i++){
      cin>>x>>y;
      x--,y--;
      e[i]=E(x,y,dis(p[x],p[y]));
    }
    for(i=0;i<n;i++){
      upper[i].clear();
      cons[i].clear();
    }
    for(i=0;i<A;i++){
      cin>>x>>y>>w;
      x--,y--;
      a[i]=E(x,y,w);
    }
    for(i=0;i<B;i++){
      cin>>x>>y>>w;
      x--,y--;
      b[i]=E(x,y,w);
      upper[x].ext(w);
      upper[y].ext(w);
    }
    for(i=0;i<C;i++){
      cin>>x>>y>>w;
      x--;
      c[i]=E(x,y,w);
      upper[x].ext(y);
    }
    cnt=0;
    for(i=0;i<n;i++)upper[i].build();
    for(i=0;i<cnt*2;i++){
      g[i].clear();
      h[i].clear();
      for(o=0;o<W;o++)mask[i][o]=0;
    }
    for(i=0;i<A;i++){
      x=a[i].x,y=a[i].y,w=a[i].w;
      u=upper[x].get_prev(w);
      v=upper[y].get_prev(w);
      if(~u&&~v)add_nand(u,v);
    }
    for(i=0;i<B;i++){
      x=b[i].x,y=b[i].y,w=b[i].w;
      add_or(upper[x].find(w),upper[y].find(w));
    }
    for(i=0;i<C;i++){
      o=upper[c[i].x].find(c[i].y);
      c[i].x=o+cnt;
      c[i].y=o;
      mask[c[i].x][i>>6]|=1ULL<<(i&63);
    }
    for(i=0;i<n;i++)upper[i].add_adj_edges();
    for(i=0;i<m;i++){
      x=e[i].x,y=e[i].y;
      if(upper[x].len>upper[y].len)swap(x,y);
      cons[y].emplace_back(P(x,e[i].w));
    }
    lim=sqrt((2.0*B*n)/max(m,1));
    for(i=0;i<n;i++){
      if(!upper[i].len||!cons[i].size())continue;
      upper[i].make_pre();
      for(const auto&con:cons[i])add_constraints(upper[con.first],upper[i],con.second);
    }
    scc=t=0;
    for(i=0;i<cnt*2;i++)if(!vis[i])dfs(i);
    for(i=t;i;i--)if(vis[s[i]])go(s[i]);
    cout<<solve()<<"\n";
  }
}