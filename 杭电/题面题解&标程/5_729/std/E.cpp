#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,a[N],cnt[N];
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    long long ans=0;
    for(int w=0;w<30;w++){
        int res[2][2]={0,0,0,0};
        for(int i=1;i<=n;i++){
            int num=(a[i]>>w)&1;
            ans+=(1ll<<w)*res[num^1][cnt[i]];
            res[num][cnt[i]]++;
            cnt[i]^=num;
        }
    }
    cout<<ans;
    return 0;
}