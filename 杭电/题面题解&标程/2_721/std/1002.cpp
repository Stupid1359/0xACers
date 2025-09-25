#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
ll n;
ll hs(ll x,ll y){
    if(x==y)return 0;
    if(__builtin_popcountll(x)==__builtin_popcountll(y))return 1;
    if(__builtin_ctzll(x)==__builtin_ctzll(y))return 1;
    return 2;
}
int main()
{
    int T;scanf("%d",&T);
    while(T--)
{
    ll x,y;
    scanf("%lld%lld%lld",&n,&x,&y);
    printf("%lld\n",hs(x,y));
}
    return 0;
}
