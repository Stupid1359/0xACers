#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n,m;

void jumpL(ll &x,ll y,ll z){
	y%=z;
	x-=y;
	if (x<=0)x+=z;
}

void jumpR(ll &x,ll y,ll z){
	y%=z;
	x+=y;
	if (x>z)x-=z;
}

int main() {
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	cin >> n >>m;
	if (__gcd(n,m)!=1) {
		cout<<"NO\n";
		return 0;
	}
	ll nwx=1,nwy=1;
	vector<vector<ll>> a(n+1);
	for (ll i=1;i<=n;i++)a[i].resize(m+1);
	ll tot=0,w=0;
	for (ll i=0; i<n; i++) {
		for (ll j=0; j<m; j++) {
			if (j&1) {
				jumpL(nwy,j,m);
			} else {
				jumpR(nwy,j,m);
			}
			++tot;
			a[nwx][nwy]=tot;
		}
//		cout<<"!"<< nwx<<"\n";
		if (i&1) {
			jumpL(nwx,(i+1)*m,n);
		} else {
			jumpR(nwx,(i+1)*m,n);
		}
	}
	cout<<"YES\n";
	for (ll i=1;i<=n;i++){
		for (ll j=1;j<=m;j++){
			cout<< a[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
