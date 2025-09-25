#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1000;
const int B=31;
const int M=1e9;
int a[N],ans[N];

vector<int> solve(vector<int> val){
    unordered_map<int,int> mp;
    int n=val.size();
    mt19937_64 rng(1234);
    while (1){
        auto mask=rng()&((1ll<<n)-1);
        int sum=0;
        for (int i=0;i<n;++i) if (mask>>i&1) sum=(sum+val[i])%M;
        if (mp.find(sum)!=mp.end()&&mp[sum]!=mask) {
            vector<int> ret(n,0);
            for (int i=0;i<n;++i){
                if (mask>>i&1) ret[i]+=1;
                if (mp[sum]>>i&1) ret[i]-=1;
            }
            return ret;
        }
        mp[sum]=mask;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    for (int i=0;i<N;++i) cin>>a[i];
    vector<int> lst;
    vector<vector<int>> res;
    for (int i=0;i<B;++i){
        vector<int> lst2;
        for (int j=0;j<B;++j){
            lst2.push_back(a[i*B+j]%M);
        }
        auto ret=solve(lst2);
        int sum=0;
        for (int j=0;j<B;++j) sum=(sum+ret[j]*a[i*B+j]+M*M)%(M*M);
        res.push_back(ret);
        assert(sum%M==0);
        sum/=M, lst.push_back(sum);
    }
    auto final=solve(lst);
    for (int i=0;i<B;++i){
        for (int j=0;j<B;++j){
            ans[i*B+j]=final[i]*res[i][j];
        }
    }
    for (int i=0;i<N;++i){
        if (ans[i]==-1) cout<<1;
        if (ans[i]==1) cout<<2;
        if (!ans[i]) cout<<0;
    }
}