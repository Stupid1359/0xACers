#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
int n;
ll a[66],ans;
struct Basis{
    static const int K=60;
    ll a[K];
    Basis(){memset(a,0,sizeof a);}
    bool ins(ll x){
        for(int i=K-1;~i;--i)
        if(x>>i&1){
            if(!a[i]){a[i]=x;return true;}
            x^=a[i];
        }
        return false;
    }
    ll max_val(ll x=0){
        for(int i=K-1;~i;--i)if((x^a[i])>x)x^=a[i];
        return x;
    }
}B;
void hs(int x,Basis B){
    if(x>n){
        ans=max(ans,B.max_val());
        return;
    }
    B.ins(a[x]);
    hs(x+2,B);
    hs(x+3,B);
}
int main()
{
    int T;scanf("%d",&T);
    while(T--)
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
    ans=0;
    Basis B;
    hs(1,B);
    hs(2,B);
    printf("%lld\n",ans);
}
    return 0;
}
