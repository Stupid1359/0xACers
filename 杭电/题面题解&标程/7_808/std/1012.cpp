#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef unsigned long long ull;
const int N=200005,P=998244353,LESS=0,GREATER=1,SUB=2,CONTAIN=3,SAME=4;
int Case,n,m,i,x,deg[N];vector<int>son[N];
int compare(int x,int y){
  int n=deg[x],m=deg[y],i=0;
  if(!n&&!m)return SAME;
  if(!n)return LESS;
  if(!m)return GREATER;
  while(i<n&&i<m){
    int t=compare(son[x][i],son[y][i]);
    if(t==SAME){
      i++;
      continue;
    }
    if(t==SUB&&i+1<n)return GREATER;
    if(t==CONTAIN&&i+1<m)return LESS;
    return t;
  }
  if(i==n&&i==m)return SAME;
  return i==n?SUB:CONTAIN;
}
inline bool cmp(int x,int y){
  if(x==y)return 0;
  int t=compare(x,y);
  return t==LESS||t==CONTAIN;
}
void dfs(int x,ull h){
  if(!deg[x]){
    cout<<h<<"\n";
  }
  h*=P;
  for(int i=0;i<deg[x];i++)dfs(son[x][i],h+i+1);
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>Case;
  while(Case--){
    cin>>n;
    for(i=1;i<=n;i++)son[i].clear();
    for(i=2;i<=n;i++){
      cin>>x;
      son[x].emplace_back(i);
    }
    for(m=0,i=n;i;i--){
      deg[i]=son[i].size();
      if(deg[i]==0)m++;else sort(son[i].begin(),son[i].end(),cmp);
    }
    cout<<m<<"\n";
    dfs(1,0);
  }
}