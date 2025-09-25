#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,c,a[MAXN];
int main()
{
    scanf("%d%d%d",&n,&k,&c);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    ll sum=0;
    for(int i=1;i<=k;i++) sum+=a[i];
    ll ans=sum;
    vector<ll> v1,v2;
    for(int i=1;i<=k;i++) v1.push_back(-a[i]-1LL*(k-i)*c);
    for(int i=k+1;i<=n;i++) v2.push_back(a[i]-1LL*(i-k-1)*c);
    sort(v1.begin(),v1.end(),greater<ll>());
    sort(v2.begin(),v2.end(),greater<ll>());
    ll s=0;
    for(int i=1;i<=min(k,n-k);i++){
        //i^2 interchanging swaps
        s+=v1[i-1]+v2[i-1];
        ll cost=s-1LL*i*c;
        ans=max(ans,sum+cost);
    }
    printf("%lld\n",ans);
    return 0;
}
 