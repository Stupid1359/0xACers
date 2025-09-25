#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int T;
ll a[10];

int main(){
	for(scanf("%d",&T);T;T--){
		for(int i=0;i<10;i++)
			scanf("%lld",&a[i]);
		ll c1357=a[1]+a[3]+a[5]+a[7],c048=a[0]+a[4]+a[8],c69=a[6]+a[9],c2=a[2];
		ll ans=0;
		if(c69>abs(c1357-c2))
			ans=c048+(c1357+c2+c69)/2;
		else ans=c048+min(c1357,c2)+c69;
		printf("%lld\n",ans);
	}
	return 0;
}
