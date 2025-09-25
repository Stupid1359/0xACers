#include<iostream>
using namespace std;
const int N=15;
int Case,n,m,k,i,j,x,y,f[N][N];char c[N][N];
inline void draw(int x,int y,int w){
  if(x<1||y<1||y>m)return;
  c[x][y]=w;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n>>m>>k;
    for(i=1;i<=n;i++)for(j=1;j<=m;j++){
      f[i][j]=0;
      c[i][j]='.';
    }
    for(i=1;i<=k;i++){
      cin>>x>>y;
      f[x][y]=i;
    }
    for(i=1;i<=n;i++)for(j=1;j<=m;j++){
      x=f[i][j];
      if(!x)continue;
      x+='0';
      draw(i,j,x);
      draw(i-1,j,x);
      for(k=j-2;k<=j+2;k++)draw(i-2,k,x);
      for(k=j-1;k<=j+1;k++)draw(i-3,k,x);
      draw(i-4,j,x);
    }
    for(i=1;i<=n;i++){
      for(j=1;j<=m;j++)cout<<c[i][j];
      cout<<"\n";
    }
  }
}