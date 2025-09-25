#include <bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
long long dp[100][100][100],dpl[100][100][100],dpr[100][100][100];
string s;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,i,j,t,p;
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				for(t=0;t<n;t++)
				{
					dp[i][j][t]=0;
					dpl[i][j][t]=0;
					dpr[i][j][t]=0;
				}
			}
		}
		for(i=0;i<n;i++)
		{
			cin>>s;
			for(j=0;j<n;j++)
			{
				if(s[j]=='1')
				{
					dp[i][j][0]=1;
					dpl[i][j][0]=1;
					dpr[i][j][0]=1;
				}
			}
		}
		for(i=1;i<n;i++)
		{
			for(j=0;i+j<n;j++)
			{
				for(t=0;i+t<n;t++)
				{
					for(p=0;p<i;p++)
					{
						dpl[j][t][i]=(dpl[j][t][i]+dpr[j][t][p]*dp[j+p+1][t+p+1][i-p-1])%mod;
						dpr[j][t][i]=(dpr[j][t][i]+dpl[j][t+i-p][p]*dp[j+p+1][t][i-p-1])%mod;
					}
					dp[j][t][i]=(dpl[j][t][i]+dpr[j][t][i])%mod;
				}
			}
		}
		cout<<dp[0][0][n-1]<<'\n';
	}
	return 0;
}
