#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100005;
const ll inf=1LL<<60;
int Case,n;ll pool[N*2];
struct E{ll q,r,s;}e[N];
inline void umin(ll&a,ll b){a>b?(a=b):0;}
inline void umax(ll&a,ll b){a<b?(a=b):0;}
inline ll myabs(ll x){return x>0?x:-x;}
inline ll cal(ll q){
  int i;
  ll sum=0;
  for(i=1;i<=n;i++){
    pool[i]=e[i].r;
    pool[i+n]=e[i].s-q;
    sum+=myabs(e[i].q-q);
  }
  nth_element(pool+1,pool+n,pool+n*2+1);
  ll r=pool[n];
  for(i=1;i<=n*2;i++)sum+=myabs(pool[i]-r);
  return sum;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n;
    ll l=inf,r=-inf;
    ll minr=inf,maxr=-inf;
    ll mins=inf,maxs=-inf;
    for(int i=1;i<=n;i++){
      cin>>e[i].q>>e[i].r>>e[i].s;
      e[i].s*=-1;
      umin(l,e[i].q);
      umax(r,e[i].q);
      umin(minr,e[i].r);
      umax(maxr,e[i].r);
      umin(mins,e[i].s);
      umax(maxs,e[i].s);
    }
    l=min(l,mins-maxr);
    r=max(r,maxs-minr);
    ll ans=inf;
    while(l<=r){
      ll len=(r-l)/3;
      ll m1=l+len;
      ll m2=r-len;
      ll f1=cal(m1);
      ll f2=cal(m2);
      if(f1<f2){
        umin(ans,f1);
        r=m2-1;
      }else{
        umin(ans,f2);
        l=m1+1;
      }
    }
    cout<<ans/2<<"\n";
  }
}