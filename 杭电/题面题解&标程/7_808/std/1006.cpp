#include<iostream>
using namespace std;
typedef long long ll;
int Case;
ll mygcd(ll a,ll b){return b?mygcd(b,a%b):a;}
struct Frac{
  ll u,d;
  Frac(){}
  Frac(ll _u,ll _d){u=_u,d=_d;}
  void show(){
    ll g=mygcd(u,d);
    cout<<u/g<<"/"<<d/g<<"\n";
  }
  bool operator>=(const Frac&p)const{return u*p.d>=p.u*d;}
}k,l,r;
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>k.u>>k.d>>l.u>>l.d>>r.u>>r.d;
    Frac tmp(k.u*r.d,k.d*r.u);
    ll v=tmp.u/tmp.d+1;
    Frac ans(r.u*v,r.d);
    if(tmp.u%tmp.d){
      Frac x(k.u,k.d*v);
      if(x>=l){
        Frac now(x.u*(v+1),x.d);
        if(now>=ans)ans=now;
      }
    }
    ans.show();
  }
}