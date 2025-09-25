#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int t,n,m;
int b[N],c[N];
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>t;
    
    while(t--){
        cin>>n>>m;
        for(int i=1;i<=n;i++)cin>>b[i];
        for(int i=1;i<=n;i++)cin>>c[i];
        bool flag=true;
        int pre=0;
        long long sum=0;
        for(int i=1;i<=n;i++){
            b[i]=max(pre,b[i]);
            if(b[i]>c[i]){
                flag=false;
                break;
            }
            sum+=b[i];
            pre=b[i];
        }
        if(m<sum)flag=false;
        pre=c[n];
        sum=0;
        for(int i=n;i>=1;i--){
            c[i]=min(pre,c[i]);
            if(b[i]>c[i]){
                flag=false;
                break;
            }
            sum+=c[i];
            pre=c[i];
        }
        if(m>sum)flag=false;
        if(flag)cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}