#include<bits/stdc++.h>
using namespace std;

const int N=59;
const int M=4e6+13;
int C[N][N];
int dp[7][M];
int a[N];

int encode(vector<int> &lst){
    assert(lst[0]==0);
    int n=lst.size();
    int cnt=0;
    for (int i=n-1;i>0;--i){
        cnt+=C[i-1+lst[i]][i];
    }
    return cnt;
}

void dfs(vector<int>&lst, int n,int cap=50){
    if (lst.size()==n-1){
        vector<int> nlst(lst);
        nlst.push_back(0);
        reverse(nlst.begin(), nlst.end());
        auto id=encode(nlst);
        dp[n][id]=1000;
        bool ok=0;
        for (int i=0;i<n;++i) for (int j=0;j<i;++j){
            if (nlst[i]==nlst[j]) continue;
            ok=1;
            vector<int> nw(nlst);
            int md=(nlst[i]+nlst[j])/2;
            nw[i]=nw[j]=md;
            sort(nw.begin(), nw.end());
            int z=nw[0];
            for (auto &c:nw) c-=z;
            dp[n][id]=min(dp[n][id],dp[n][encode(nw)]+z);
        }
        if (!ok) dp[n][id]=0;
        return;
    }
    for (int i=0;i<=(lst.size()?lst.back():cap);++i) {lst.push_back(i);  dfs(lst,n,cap); lst.pop_back();}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    C[0][0]=1;
    for (int i=1;i<N;++i){
        C[i][0]=1;
        for (int j=1;j<=i;++j) C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    for (int k=3;k<=6;++k){
        vector<int> lst;
        dfs(lst,k);
    }
    int _;
    cin>>_;
    while (_--){
        int n;
        cin>>n;
        for (int i=0;i<n;++i) cin>>a[i];
        sort(a,a+n);
        if (n<=2){cout<<(a[0]+a[1%n])/2<<"\n"; continue;}
        int w=a[0];
        vector<int> lst;
        for (int i=0;i<min(6,n);++i) lst.push_back(a[i]-w);
        cout<<dp[lst.size()][encode(lst)]+w<<"\n";
    }
}