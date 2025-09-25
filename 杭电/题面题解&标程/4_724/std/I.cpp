#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN];
char mp[MAXN][MAXN];
int dist[MAXN][MAXN];
P pre[MAXN][MAXN];
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
queue<P> que;
vector<pair<P,P> > ans;
int px,py;
vector<P> path;
void bfs(int x,int y){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dist[i][j]=INF;
    while(que.size()) que.pop();
    que.push(P(x,y)); dist[x][y]=0;
    px=py=-1; path.clear();
    while(que.size()){
        P p=que.front(); que.pop();
        if(mp[p.F][p.S]=='*') {
            px=p.F; py=p.S; 
            int tx=p.F,ty=p.S;
            do{
                path.push_back(P(tx,ty));
                if(dist[tx][ty]==0) break;
                tie(tx,ty)=pre[tx][ty];
            }while(true);
            return;
        }
        for(int t=0;t<4;t++){
            int nx=p.F+dx[t],ny=p.S+dy[t];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&mp[nx][ny]!='#'&&dist[nx][ny]==INF){
                dist[nx][ny]=dist[p.F][p.S]+1; pre[nx][ny]=P(p.F,p.S);
                que.push(P(nx,ny));
            }
        }
    }
}
void construct_sol(){
    int now=0; 
    //printf("sz=%d\n",(int)path.size());
    for(int i=1;i<(int)path.size();i++){
        if(mp[path[i].F][path[i].S]!='.'){
            for(int j=i;j>now;j--){
                ans.push_back(make_pair(path[j],path[j-1]));
            }
            now=i;
        }
    }
    mp[path.back().F][path.back().S]='.'; mp[path[0].F][path[0].S]='!';
}
char get_dir(pair<P,P> p){
    if(p.S.F==p.F.F+1) return 'D';
    if(p.S.F==p.F.F-1) return 'U';
    if(p.S.S==p.F.S+1) return 'R';
    if(p.S.S==p.F.S-1) return 'L';
    assert(0);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='@'){
                bfs(i,j);
                if(px==-1) {puts("-1"); return 0;}
                construct_sol();
            }
        }
    }
    printf("%d\n",(int)ans.size());
    for(auto p:ans){
        printf("%d %d %c\n",p.F.F,p.F.S,get_dir(p));
    }
    return 0;
}
 