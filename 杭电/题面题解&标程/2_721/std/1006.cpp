#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N=1e6+5;
int n,p1[N],p2[N],t[N],w[N],ans[N];
void add(int x,int y){
    for(;x<=n;x+=x&-x)t[x]+=y;
}
int sum(int x){
    int z=0;
    for(;x;x-=x&-x)z+=t[x];
    return z;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--)
{
    cin>>n;
    for(int i=1;i<=n;++i)cin>>p1[i];
    for(int i=1;i<=n;++i)cin>>p2[i],w[p2[i]]=i;
    for(int i=1;i<=n;++i)add(i,1);
    for(int i=1;i<=n;++i){
        int x=p1[i];
        ans[x]=i-1+sum(w[x]-1);
        add(w[x],-1);
    }
    for(int i=1;i<=n;++i)cout<<ans[i]<<' ';
    cout<<"\n";
    memset(t,0,(n+2)*4);
}
    return 0;
}
