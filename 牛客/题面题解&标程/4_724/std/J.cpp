#include<bits/stdc++.h>
#define ll   long long
#define pb   emplace_back
#define mp   make_pair
#define orz  1000000007
#define fi   first
#define se   second
#define MAXN  205
using namespace std;
int T;
int n,f[MAXN][MAXN*3],g[MAXN][MAXN*3],d[MAXN][MAXN*3],res[MAXN],h[4][MAXN][MAXN*3],dp[MAXN][MAXN*3];
vector<pair<int,int>> v[3][MAXN][MAXN*3];
void sol(pair<int,int> s){
	vector<pair<int,int>> V[3];
	int o=0,p=1,q=2;
	V[0].pb(s);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n*2;++j)d[i][j]=-1;
	}
	d[s.fi][s.se]=0;
	int D=0;
	while(V[o].size()>0||V[p].size()>0){
		for(auto x:V[o]){
			for(auto y:v[1][x.fi][x.se])if(d[y.fi][y.se]==-1){
				d[y.fi][y.se]=D+1;
				V[p].pb(y);
			}
		}
		for(auto x:V[o]){
			for(auto y:v[2][x.fi][x.se])if(d[y.fi][y.se]==-1){
				d[y.fi][y.se]=D+2;
				V[q].pb(y);
			}
		}
		V[o].clear();
		o=p,p=q;
		q=3-o-p;
		++D;
	}
}
void sol2(pair<int,int> s){
	int l=s.se-n,r=s.se+n;
	int B;
	if(s.fi==1)B=2+n/2;
	else B=n-n/2-1;
	vector<pair<int,int>> V[3];
	int o=0,p=1,q=2;
	V[0].pb(s);
	for(int i=1;i<=n;++i){
		for(int j=l;j<=r;++j)d[i][j]=-1;
	}
	d[s.fi][s.se]=0;
	int D=0;
	while(V[o].size()>0||V[p].size()>0){
		for(auto x:V[o]){
			for(auto y:v[1][x.fi][x.se])if(d[y.fi][y.se]==-1){
				d[y.fi][y.se]=D+1;
				if(y.se>=l&&y.se<=r&&y.fi!=B)V[p].pb(y);
			}
		}
		for(auto x:V[o]){
			for(auto y:v[2][x.fi][x.se])if(d[y.fi][y.se]==-1){
				d[y.fi][y.se]=D+2;
				if(y.se>=l&&y.se<=r&&y.fi!=B)V[q].pb(y);
			}
		}
		V[o].clear();
		o=p,p=q;
		q=3-o-p;
		++D;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j)cin>>f[i][j];
		}
		for(int i=1;i<n;++i){
			for(int j=1;j<=n;++j)cin>>g[i][j];
		}
		for(int i=1;i<=n;++i){
			for(int j=n+1;j<=n*3;++j)f[i][j]=f[i][j-n];
		}
		for(int i=1;i<n;++i){
			for(int j=n+1;j<=n*3;++j)g[i][j]=g[i][j-n];
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n*3;++j)v[1][i][j].clear(),v[2][i][j].clear();
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				pair<int,int> x,y;
				x=mp(i,j),y=mp(i,j+1);
				v[f[i][j]][x.fi][x.se].pb(y);
				v[f[i][j]][y.fi][y.se].pb(x);
				x=mp(i,j+n),y=mp(i,j+n+1);
				if(j==n)y.se=1;
				v[f[i][j]][x.fi][x.se].pb(y);
				v[f[i][j]][y.fi][y.se].pb(x);
			}
		}
		for(int i=1;i<n;++i){
			for(int j=1;j<=n;++j){
				pair<int,int> x,y;
				x=mp(i,j),y=mp(i+1,j);
				v[g[i][j]][x.fi][x.se].pb(y);
				v[g[i][j]][y.fi][y.se].pb(x);
				x=mp(i,j+n),y=mp(i+1,j+n);
				v[g[i][j]][x.fi][x.se].pb(y);
				v[g[i][j]][y.fi][y.se].pb(x);
			}
		}
		for(int i=1;i<=n;++i){
			sol(mp(1,i));
			res[i]=d[n][n+i];
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n*3;++j)v[1][i][j].clear(),v[2][i][j].clear();
		}
		for(int i=1;i<=n;++i){
				for(int j=1;j<=n;++j){
				pair<int,int> x,y;
				x=mp(i,j),y=mp(i,j+1);
				v[f[i][j]][x.fi][x.se].pb(y);
				v[f[i][j]][y.fi][y.se].pb(x);
				x=mp(i,j+n),y=mp(i,j+n+1);
				v[f[i][j]][x.fi][x.se].pb(y);
				v[f[i][j]][y.fi][y.se].pb(x);
				if(j==n) continue;
				x=mp(i,j+n*2),y=mp(i,j+n*2+1);
				v[f[i][j]][x.fi][x.se].pb(y);
				v[f[i][j]][y.fi][y.se].pb(x);
			}
		}
		for(int i=1;i<n;++i){
			for(int j=1;j<=n;++j){
				pair<int,int> x,y;
				x=mp(i,j),y=mp(i+1,j);
				v[g[i][j]][x.fi][x.se].pb(y);
				v[g[i][j]][y.fi][y.se].pb(x);
				x=mp(i,j+n),y=mp(i+1,j+n);
				v[g[i][j]][x.fi][x.se].pb(y);
				v[g[i][j]][y.fi][y.se].pb(x);
				x=mp(i,j+n*2),y=mp(i+1,j+n*2);
				v[g[i][j]][x.fi][x.se].pb(y);
				v[g[i][j]][y.fi][y.se].pb(x);
			}
		}
		for(int i=1;i<=n;++i){
			sol2(mp(1,i+n));
			for(int j=1;j<=n*3;++j)h[0][i][j]=d[1][j];
			for(int j=1;j<=n*3;++j)h[1][i][j]=d[2][j];
			sol2(mp(n,i+n));
			for(int j=1;j<=n*3;++j)h[2][i][j]=d[n-1][j];
			for(int j=1;j<=n*3;++j)h[3][i][j]=d[n][j];
		}
		for(int k=1;k<=n*2;++k){
			int k2=k+n-1;
			dp[1][k]=0;
			for(int i=k;i<k+n;++i)dp[1][i+1]=dp[1][i]+f[1][i];
			for(int i=1;i<n;++i)dp[i+1][k]=dp[i][k]+g[i][k];
			for(int i=2;i<=n;++i){
				for(int j=k+1;j<k+n;++j)dp[i][j]=min(dp[i][j-1]+f[i][j-1],dp[i-1][j]+g[i-1][j]);
			}
			for(int i=1;i<=n;++i)if(k<=n+i&&k2>=n+i)res[i]=min(res[i],h[0][i][k]+dp[n][k2]+h[3][i][k2]);
			for(int i=1;i<=n;++i)if(k<=n+i&&k2>=n+i)res[i]=min(res[i],h[0][i][k]+dp[n-1][k2]+h[2][i][k2]);
			dp[2][k]=0;
			for(int i=k;i<k+n;++i)dp[2][i+1]=dp[2][i]+f[2][i];
			for(int i=2;i<n;++i)dp[i+1][k]=dp[i][k]+g[i][k];
			for(int i=3;i<=n;++i){
				for(int j=k+1;j<k+n;++j)dp[i][j]=min(dp[i][j-1]+f[i][j-1],dp[i-1][j]+g[i-1][j]);
			}
			for(int i=1;i<=n;++i)if(k<=n+i&&k2>=n+i)res[i]=min(res[i],h[1][i][k]+dp[n][k2]+h[3][i][k2]);
		}
		for(int k=n+1;k<=n*3;++k){
			int k2=k-n+1;
			dp[1][k]=0;
			for(int i=k-1;i>k-n;--i)dp[1][i]=dp[1][i+1]+f[1][i];
			for(int i=1;i<n;++i)dp[i+1][k]=dp[i][k]+g[i][k];
			for(int i=2;i<=n;++i){
				for(int j=k-1;j>k-n;--j)dp[i][j]=min(dp[i][j+1]+f[i][j],dp[i-1][j]+g[i-1][j]);
			}
			for(int i=1;i<=n;++i)if(k>=n+i&&k2<=n+i)res[i]=min(res[i],h[0][i][k]+dp[n][k2]+h[3][i][k2]);
			for(int i=1;i<=n;++i)if(k>=n+i&&k2<=n+i)res[i]=min(res[i],h[0][i][k]+dp[n-1][k2]+h[2][i][k2]);
			dp[2][k]=0;
			for(int i=k-1;i>k-n;--i)dp[2][i]=dp[2][i+1]+f[2][i];
			for(int i=2;i<n;++i)dp[i+1][k]=dp[i][k]+g[i][k];
			for(int i=3;i<=n;++i){
				for(int j=k-1;j>k-n;--j)dp[i][j]=min(dp[i][j+1]+f[i][j],dp[i-1][j]+g[i-1][j]);
			}
			for(int i=1;i<=n;++i)if(k>=n+i&&k2<=n+i)res[i]=min(res[i],h[1][i][k]+dp[n][k2]+h[3][i][k2]);
		}
		for(int i=1;i<=n;++i)cout<<res[i]<<'\n';
	}
    return 0;
}