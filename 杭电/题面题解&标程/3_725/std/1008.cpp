#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int solve(vector<bool>&flag){
    int sum=0,res=0;
    if(flag[n-1]){
        for(int i=n-1;i>=0;i--){
            if(flag[i])sum++,flag[i]=false;
            else break;
        }
        for(int i=0;i<n;i++){
            if(flag[i])sum++,flag[i]=false;
            else break;
        }
        res+=(sum+1)/2;
        sum=0;
    }
    for(int i=0;i<n;i++){
        if(flag[i])sum++;
        else{
            res+=(sum+1)/2;
            sum=0;
        }
    }
    res+=(sum+1)/2;
    return res;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //freopen("2.in","r",stdin);
    //freopen("2.out","w",stdout);
    cin>>t;
    while(t--){
        cin>>n>>s;
        int ans=n;
        vector<bool>flag(n);
        for(int i=0;i<n;i++){
            flag[i]=(s[i]-'0')^(i&1);
        }
        ans=min(ans,solve(flag));
        for(int i=0;i<n;i++){
            flag[i]=(s[i]-'0')^((i+1)&1);
        }
        ans=min(ans,solve(flag));
        cout<<ans<<'\n';
    }
    return 0;
}