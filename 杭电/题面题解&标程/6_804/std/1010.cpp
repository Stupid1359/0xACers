#include<bits/stdc++.h>
using namespace std;
long long a[200000];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,i,p;
	long long mx,mx2,c,s,d;
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		mx=-1;
		p=-1;
		for(i=0;i<n;i++)
		{
			cin>>a[i];
			if(a[i]>mx)
			{
				mx=a[i];
				p=i;
			}
		}
		mx2=-1;
		c=0;
		for(i=0;i<n;i++)
		{
			if(i==p)continue;
			if(a[i]>mx2)
			{
				mx2=a[i];
				c=0;
			}
			if(a[i]==mx2)c++;
		}
		s=0;
		for(i=0;i<n;i++)
		{
			if(a[i]!=mx&&a[i]!=mx2)s+=a[i];
		}
		if(mx>c*mx2+s)cout<<"NO\n";
		else if(mx>=c*mx2)cout<<"YES\n";
		else
		{
			d=(mx+mx2-1)/mx2;
			if((c-d)%2==0)cout<<"YES\n";
			else if(mx-(d-1)*mx2<=s)cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
