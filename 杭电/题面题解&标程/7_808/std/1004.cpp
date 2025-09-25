#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int,int>E;
const int N=200005,M=200005,CNT=533333;
int Case,n,m,i,mx[CNT],delta[CNT];
struct P{int g,k,t,l,r,d;}bomb[N];
vector<E>e[M];
void build(int x,int a,int b){
  mx[x]=delta[x]=0;
  if(a==b)return;
  int mid=(a+b)>>1;
  build(x<<1,a,mid);
  build(x<<1|1,mid+1,b);
}
inline int ask(int x,int a,int b,int p){
  int ret=0;
  while(1){
    if(p>=mx[x])return ret;
    if(a==b)return ret+1;
    int mid=(a+b)>>1;
    if(p>=mx[x<<1]){
      a=mid+1;
      x=x<<1|1;
    }else{
      ret+=delta[x];
      b=mid;
      x<<=1;
    }
  }
}
void change(int x,int a,int b,int c,int p){
  if(a==b){
    mx[x]^=p;
    return;
  }
  int mid=(a+b)>>1;
  if(c<=mid)change(x<<1,a,mid,c,p);
  else change(x<<1|1,mid+1,b,c,p);
  mx[x]=max(mx[x<<1],mx[x<<1|1]);
  delta[x]=ask(x<<1|1,mid+1,b,mx[x<<1]);
}
inline int kth(int p,int k){
  if(ask(1,1,m,p)<k)return m+1;
  int x=1,a=1,b=m;
  while(a<b){
    int mid=(a+b)>>1;
    x<<=1;
    int tmp=ask(x,a,mid,p);
    if(k<=tmp){
      b=mid;
    }else{
      k-=tmp;
      a=mid+1;
      p=max(p,mx[x++]);
    }
  }
  return a;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n>>m;
    for(i=1;i<=n;i++){
      cin>>bomb[i].g>>bomb[i].k>>bomb[i].t;
      if(i<n)cin>>bomb[i].l>>bomb[i].r>>bomb[i].d;
    }
    build(1,1,m);
    for(i=1;i<=n;i++){
      for(const auto&it:e[i])change(1,1,m,it.first,it.second);
      int t=min(kth(bomb[i].g,bomb[i].k)+1,bomb[i].t);
      cout<<t;
      if(i<n){
        cout<<" ";
        e[bomb[i].l].emplace_back(E(t,bomb[i].d));
        e[bomb[i].r+1].emplace_back(E(t,bomb[i].d));
      }else cout<<"\n";
    }
    for(i=1;i<=n+1;i++)e[i].clear();
  }
}