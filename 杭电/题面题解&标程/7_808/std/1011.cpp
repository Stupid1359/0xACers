#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200005;
int Case,n,m,i,j,k,qa[N],qb[N],tmp[N],fin[N];
struct P{int x,y;}a[N];
struct Line{
  int a,b;ll c;
  bool contain(const P&p)const{return 1LL*a*p.x+1LL*b*p.y<=c;}
}b[N],hull[N];
ll lim[N];
inline ll pos(const Line&p,const Line&q){
  return (p.c*q.b-q.c*p.b)/(1LL*p.a*q.b-1LL*q.a*p.b);
}
inline bool cmpa(int p,int q){return a[p].x<a[q].x;}
inline bool cmpb(int p,int q){
  ll cross=1LL*b[p].a*b[q].b-1LL*b[q].a*b[p].b;
  if(cross)return cross>0;
  return b[p].c*b[q].b>b[q].c*b[p].b;
}
inline bool cmpfin(int p,int q){return fin[p]==fin[q]?p<q:fin[p]<fin[q];}
void solve(int al,int ar,int bl,int br){
  int i,o;
  if(bl==br){
    const Line&B=b[bl];
    for(i=al;i<=ar;i++){
      o=qa[i];
      fin[o]=B.contain(a[o])?bl:m+1;
    }
    return;
  }
  int mid=(bl+br)>>1,t=0;
  for(i=bl;i<=br;i++){
    o=qb[i];
    if(o>mid)continue;
    const Line&now=b[o];
    if(t&&1LL*hull[t].a*now.b==1LL*hull[t].b*now.a)continue;
    while(t>1&&pos(hull[t],now)<=lim[t-1])t--;
    if(t)lim[t]=pos(hull[t],now);
    hull[++t]=now;
  }
  int tl=al-1,tr=ar+1,h=1;
  for(i=al;i<=ar;i++){
    o=qa[i];
    while(h<t&&a[o].x>lim[h])h++;
    if(hull[h].contain(a[o]))tmp[++tl]=o;else tmp[--tr]=o;
  }
  reverse(tmp+tr,tmp+ar+1);
  for(i=al;i<=ar;i++)qa[i]=tmp[i];
  int l=bl-1,r=mid;
  for(i=bl;i<=br;i++){
    o=qb[i];
    if(o<=mid)tmp[++l]=o;else tmp[++r]=o;
  }
  for(i=bl;i<=br;i++)qb[i]=tmp[i];
  if(al<=tl)solve(al,tl,bl,mid);
  if(tr<=ar)solve(tr,ar,mid+1,br);
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n;
    for(i=1;i<=n;i++){
      cin>>a[i].x>>a[i].y;
      qa[i]=i;
    }
    cin>>m;
    for(i=1;i<=m;i++){
      cin>>b[i].a>>b[i].b>>b[i].c;
      qb[i]=i;
    }
    sort(qa+1,qa+n+1,cmpa);
    sort(qb+1,qb+m+1,cmpb);
    solve(1,n,1,m);
    sort(qa+1,qa+n+1,cmpfin);
    for(i=j=1;i<=m;i++){
      for(k=j;k<=n&&fin[qa[k]]==i;k++);
      cout<<k-j;
      while(j<k)cout<<" "<<qa[j++];
      cout<<"\n";
    }
  }
}