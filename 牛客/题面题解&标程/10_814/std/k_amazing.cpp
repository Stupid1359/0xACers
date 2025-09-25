#include <bits/stdc++.h>
using namespace std;
bool dp[10005][10005];
int sm[10005],a[10005],n,to[10005],tg[10005],dep[10005];
vector<int> vc[10005];
void dfs(int x){
    for(int y:vc[x])dep[y]=dep[x]+1,dfs(y);
} 
void dfs2(int x){
    for(int y:vc[x])dfs2(y),to[x]=min(to[x],to[y]);
}
void dfs3(int x){
    dp[x][0]=1;
    for(int y:vc[x]){
        dfs3(y);
        for(int i=sm[x];~i;i--)if(dp[x][i])for(int j=sm[y];j;j--){
            dp[x][i+j]|=dp[y][j];
        }
        sm[x]+=sm[y];
    }
    sm[x]+=a[x];
    if(to[x]==dep[x])dp[x][sm[x]]=1;
}
signed main(){
//	freopen("sub34.in", "r", stdin);
//	freopen("sub34.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        vc[x].push_back(y),tg[y]=1;
    }
    int root=0;
    for(int i=1;i<=n;i++)if(!tg[i])root=i;
    dfs(root);
    for(int i=1;i<=n;i++)to[i]=dep[i];
    int m;
    cin>>m; 
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        to[x]=min(to[x],dep[y]);
    }
    dfs2(root),dfs3(root);
    int ans=0;
    for(int i=0;i<=sm[root];i++)if(dp[root][i])ans++;
    cout<<ans<<'\n';
    return 0;
}
