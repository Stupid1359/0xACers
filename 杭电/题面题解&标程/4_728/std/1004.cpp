#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7,M=1e7;
bool vis[M+5];
int cnp,pr[M],To[M+5];
inline void add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
void oula(){
	for(int i=2;i<=M;i++){
		if(!vis[i])
			pr[++cnp]=i,To[i]=cnp;
		for(int j=1;j<=cnp&&i*pr[j]<=M;j++){
			vis[i*pr[j]]=1;
			if(i%pr[j]==0) break;
		}
	}
}
int n,m;
const int M2=18; 
int dp[2][1<<M2];
int id[M2+1],tg[1<<M2];
int pp[1<<M2],lg2[1<<M2];
void solve(){
	cin>>n;
	for(int i=0;i<n;i++){
		int x;
		cin>>x;
		if(x==2)id[i]=0;
		else id[i]=To[x];
	}
	for (int i=0;i<n;i++)lg2[1<<i]=i;
	for(int i=0;i<(1<<n);i++){
		int lb=i&-i;
		int k=lg2[lb];
		pp[i]=pp[i^lb]^id[k];
	}
	cin>>m;
	for(int i=0;i<(1<<n);i++){
		tg[i]=0;
	}
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		tg[x]=1;
	}
	memset(dp,0,sizeof(dp)); 
	dp[0][0]=1;
	int ct=0;
	for(int i=0;i<n;i++){
		memset(dp[i&1^1],0,sizeof(dp[i&1^1])); 
		int d=(1<<n)-(1<<i);
		for(int j=0;j<(1<<n);j++){
			if(!dp[i&1][j])continue;
			
			if (j>>i&1){
				add(dp[i&1^1][j^(1<<i)],dp[i&1][j]);
			}else{
				int w=((~j)&d)^(1<<i);
				for (int k=w;;k=(k-1)&w){++ct;
					if (!tg[k|(1<<i)]){
						add(dp[i&1^1][j|k|(1<<i)],dp[i&1][j]);
					}
					if (k==0)break;
				}
			}
		}
	}
	int ans=0,ans2=0;
	for (int j=0;j<(1<<n);j++){
		if (pp[j]==0)add(ans,dp[n&1][j]);
		else add(ans2,dp[n&1][j]);
	}
	cout<<ans2<<' '<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	oula();
	int tc;
	cin>>tc;
	while(tc--)solve();
	return 0;
}
