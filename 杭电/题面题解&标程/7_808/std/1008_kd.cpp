#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=50005;
int Case,n,m,i,root,cmp_d,L,R,P;
vector<int>g[N],h[N];
ll ans;
struct E{int u,l,r;}e[N];
struct Node{
  int l,r;
  int d[2],ma[2],mi[2];
  int coef,w,tag,val;ll sum;
}t[N<<1];
inline bool cmp(const Node&a,const Node&b){return a.d[cmp_d]<b.d[cmp_d];}
inline void umax(int&a,int b){a<b?(a=b):0;}
inline void umin(int&a,int b){a>b?(a=b):0;}
int build(int l,int r,int D){
  int mid=(l+r)>>1;
  cmp_d=D;
  nth_element(t+l,t+mid,t+r+1,cmp);
  Node&x=t[mid];
  x.ma[0]=x.mi[0]=x.d[0];
  x.ma[1]=x.mi[1]=x.d[1];
  x.w=x.coef;
  x.tag=0;
  x.val=0;
  x.sum=0;
  if(l!=mid){
    x.l=build(l,mid-1,!D);
    const Node&y=t[x.l];
    umax(x.ma[0],y.ma[0]);
    umin(x.mi[0],y.mi[0]);
    umax(x.ma[1],y.ma[1]);
    umin(x.mi[1],y.mi[1]);
    x.w+=y.w;
  }else x.l=0;
  if(r!=mid){
    x.r=build(mid+1,r,!D);
    const Node&y=t[x.r];
    umax(x.ma[0],y.ma[0]);
    umin(x.mi[0],y.mi[0]);
    umax(x.ma[1],y.ma[1]);
    umin(x.mi[1],y.mi[1]);
    x.w+=y.w;
  }else x.r=0;
  return mid;
}
inline void tag(Node&x,int P){
  x.tag+=P;
  x.val+=x.coef*P;
  x.sum+=x.w*P;
}
inline void pb(Node&x){
  if(!x.tag)return;
  if(x.l)tag(t[x.l],x.tag);
  if(x.r)tag(t[x.r],x.tag);
  x.tag=0;
}
void change(Node&x){
  if(x.mi[1]>R)return;
  if(x.ma[1]<=R){tag(x,P);return;}
  pb(x);
  if(x.d[1]<=R)x.val+=x.coef*P;
  x.sum=x.val;
  if(x.l){
    change(t[x.l]);
    x.sum+=t[x.l].sum;
  }
  if(x.r){
    change(t[x.r]);
    x.sum+=t[x.r].sum;
  }
}
void query(Node&x){
  if(x.ma[0]<L||x.mi[0]>R)return;
  if(x.mi[0]>=L&&x.ma[0]<=R){ans+=x.sum;return;}
  pb(x);
  if(x.d[0]>=L&&x.d[0]<=R)ans+=x.val;
  if(x.l)query(t[x.l]);
  if(x.r)query(t[x.r]);
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n>>m;
    ans=0;
    for(i=1;i<=n+1;i++){
      g[i].clear();
      h[i].clear();
    }
    for(i=1;i<=m;i++){
      cin>>e[i].u>>e[i].l>>e[i].r;
      g[e[i].u].emplace_back(i);
      h[e[i].l].emplace_back(i);
      h[e[i].r+1].emplace_back(-i);
      t[i].d[0]=e[i].u;
      t[i].d[1]=e[i].l;
      t[i].coef=1;
      t[i+m].d[0]=e[i].u;
      t[i+m].d[1]=e[i].r+1;
      t[i+m].coef=-1;
    }
    root=build(1,m*2,0);
    for(i=1;i<=n;i++){
      for(const auto&it:h[i]){
        if(it>0){
          R=e[it].u;
          P=1;
        }else{
          R=e[-it].u;
          P=-1;
        }
        change(t[root]);
      }
      for(const auto&it:g[i]){
        L=e[it].l;
        R=e[it].r;
        query(t[root]);
      }
    }
    cout<<ans<<"\n";
  }
}