#include<bits/stdc++.h>
using namespace std;
long long a[200000];
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int T;
	long long n,i,mx;
	for(cin>>T;T>0;T--)
	{
		cin>>n;
		mx=0;
		for(i=0;i<n;i++)
		{
			cin>>a[i];
			mx=max(mx,a[i]);
		}
		if(n<=2)cout<<"0\n";
		else cout<<mx*(n-3)+max(a[0],a[n-1])<<'\n';
	}
	return 0;
}
