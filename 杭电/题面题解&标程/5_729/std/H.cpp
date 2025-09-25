#include<bits/stdc++.h>
using namespace std;
const int N=105;
const int INF=0x3f3f3f3f;
int m,s,t;
int n,a[N],k[N],b[N],c[N];
int dp[N][N][N];
bool check(int p){
    for(int i=0;i<=t;i++){
        for(int j=0;j<=n;j++){
            for(int z=0;z<=t;z++){
                dp[i][j][z]=-INF;
            }
        }
    }
    int mav=-INF;
    dp[0][0][0]=0;
    for(int i=0;i<=t;i++){
        for(int j=0;j<=n;j++){
            for(int z=0;z<=t;z++){
                if(dp[i][j][z]==-INF)continue;
                if(i+1<=t){
                    dp[i+1][j][z+1]=max(dp[i+1][j][z+1],dp[i][j][z]+k[j]);
                }
                if(j+1<=n){
                    int cnt=(a[j+1]+k[j]-1)/k[j];
                    if(i+cnt<=t){
                        dp[i+cnt][j+1][z+cnt]=max(dp[i+cnt][j+1][z+cnt],dp[i][j][z]);
                    }
                    cnt=(a[j+1]-c[j+1]+k[j]-1)/k[j];
                    if(p>0){
                        int cnt2=(b[j+1]+p-1)/p;
                        if(i+cnt<=t && z+cnt-cnt2>=0){
                            dp[i+cnt][j+1][z+cnt-cnt2]=max(dp[i+cnt][j+1][z+cnt-cnt2],dp[i][j][z]);
                        }
                    }
                }
                mav=max(mav,dp[i][j][z]);
            }
        }
    }
    return mav>=s;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>m>>s>>t>>n;
    k[0]=m;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>k[i]>>b[i]>>c[i];
        k[i]+=k[i-1];
    }
    int l=0,r=10000,mid;
    while(l<r){
        mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    if(check(l)){
        cout<<l;
    }else{
        cout<<-1;
    }
    return 0;
}