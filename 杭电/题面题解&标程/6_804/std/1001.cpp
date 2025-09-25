#include <bits/stdc++.h>
using namespace std;
int inf=1000000010;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T,n,i,a,f,c,mn;
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		f=0;
		c=0;
		mn=inf;
		for(i=0;i<n;i++)
		{
			cin>>a;
			if(a==0)c++;
			if(a<0)
			{
				a=-a;
				f^=1;
			}
			mn=min(mn,a);
		}
		if(c)cout<<c<<'\n';
		else if(f)cout<<mn+1<<'\n';
		else cout<<"0\n";
	}
	return 0;
}
