#include<bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
long long a[151],h[150],psum[151],inf=1000000000000000000LL;
long long dp1[151][151][4][4],dp2[151][151][4][4],dp3[151][4],pw[151];
bool check(int l,int r,int z1,int z2,int n){
	long long s=psum[r]-psum[l],nxt=a[r];
	if(z1&1)
	{
		if(l!=0)s+=h[l-1];
	}
	if(z2&1)
	{
		s-=h[r-1];
		nxt+=h[r-1];
	}
	if(z2>>1)
	{
		if(r!=n)nxt-=h[r];
	}
	return s>nxt;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,m,i,j,z1,z2,z3,len,l,r;
	long long x;
	for(cin>>T;T>0;T--)
	{
		cin>>n>>x;
		for(i=0;i<n;i++)cin>>a[i];
		for(i=0;i<n-1;i++)cin>>h[i];
		pw[0]=1;
		for(i=1;i<=n;i++)pw[i]=pw[i-1]*x%mod;
		a[n]=inf;
		h[n-1]=0;
		psum[0]=0;
		for(i=0;i<n;i++)psum[i+1]=psum[i]+a[i];
		for(i=0;i<=n;i++)
		{
			for(j=0;j<=n;j++)
			{
				for(z1=0;z1<4;z1++)
				{
					for(z2=0;z2<4;z2++)
					{
						dp1[i][j][z1][z2]=0;
						dp2[i][j][z1][z2]=0;
					}
				}
			}
		}
		for(i=0;i<n;i++)
		{
			for(z1=0;z1<4;z1++)
			{
				for(z2=0;z2<4;z2++)
				{
					if((z1>>1)!=(z2&1))continue;
					if(check(i,i+1,z1,z2,n))dp1[i][i+1][z1][z2]=x;
					else dp2[i][i+1][z1][z2]=x;
				}
			}
		}
		for(len=2;len<=n;len++)
		{
			for(l=0;l+len<=n;l++)
			{
				r=l+len;
				for(i=l+1;i<r;i++)
				{
					for(z1=0;z1<4;z1++)
					{
						for(z2=0;z2<4;z2++)
						{
							for(z3=0;z3<4;z3++)
							{
								if(check(l,r,z1,z3,n))dp1[l][r][z1][z3]=(dp1[l][r][z1][z3]+dp1[l][i][z1][z2]*dp2[i][r][z2][z3]%mod*pw[r-i])%mod;
								else dp2[l][r][z1][z3]=(dp2[l][r][z1][z3]+dp1[l][i][z1][z2]*dp2[i][r][z2][z3]%mod*pw[r-i])%mod;
							}
						}
					}
				}
			}
		}
		for(i=0;i<=n;i++)
		{
			for(z1=0;z1<4;z1++)dp3[i][z1]=0;
		}
		dp3[0][0]=1;
		dp3[0][2]=1;
		for(i=0;i<=n;i++)
		{
			for(j=i+1;j<=n;j++)
			{
				for(z1=0;z1<4;z1++)
				{
					for(z2=0;z2<4;z2++)dp3[j][z2]=(dp3[j][z2]+dp3[i][z1]*dp2[i][j][z1][z2])%mod;
				}
			}
		}
		cout<<dp3[n][0]<<'\n';
	}
	return 0;
}
