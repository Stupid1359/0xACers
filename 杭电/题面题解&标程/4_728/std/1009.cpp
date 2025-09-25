#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
int cas,n,a[100009];
signed main(){
	 freopen("input.in","r",stdin);
	 freopen("output.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>cas;
	while(cas--){
		cin>>n;long long sum=0;bool fl=1;
		for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i],fl&=(a[i]>0);
		if(sum<2*n-2||!fl)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
