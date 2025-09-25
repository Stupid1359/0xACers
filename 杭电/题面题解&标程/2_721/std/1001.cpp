#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
typedef vector<int> poly;
constexpr int N=205;
int mu[N];
poly operator *(const poly &p,const poly &q){
    poly ret;
    int deg=p.size()+q.size()-2;
    ret.resize(deg+1);
    for(int i=0;i<p.size();i++)for(int j=0;j<q.size();j++)
        ret[i+j]+=p[i]*q[j];
    return ret;
}
poly operator /(poly p,const poly &q){
    poly ret;
    int deg=p.size()-q.size();
    ret.resize(deg+1);
    for(int i=deg;i>=0;i--){
        int a=p[i+q.size()-1];
        for(int j=0;j<q.size();j++)p[j+i]-=a*q[j];
        ret[i]=a;
    }
    return ret;
}
poly Phi(int n){
    poly num={1},den={1};
    for(int d=1;d<=n;d++)if(n%d==0){
        int k=mu[n/d];
        if(k==0)continue;
        poly p(d+1);
        p[d]=1;p[0]=-1;
        if(k==1)num=num*p;
        else den=den*p;
    }
    return num/den;
}
vector<poly> P1,P2;
vector<int> cof;
int n,ans;
void dfs(int i,int pf,int pg,poly f,poly g){
    if(pf>n||pg>n)return;
    if(i==cof.size()){
        bool ok=true;
        for(auto x:f)ok&=(x>=0);
        for(auto x:g)ok&=(x>=0);
        if(ok)ans++;
        return;
    }
    dfs(i+1,pf,pg*cof[i]*cof[i],f,g*P2[i]);
    dfs(i+1,pf*cof[i],pg*cof[i],f*P1[i],g*P1[i]);
    dfs(i+1,pf*cof[i]*cof[i],pg,f*P2[i],g);
}
void work(int n){
    ans=0;
    P1.clear();P2.clear();cof.clear();
    for(int i=2;i<=n;i++)if(n%i==0){
        auto cyc=Phi(i);
        P1.push_back(cyc);
        P2.push_back(cyc*cyc);
        cof.push_back(accumulate(cyc.begin(),cyc.end(),0));
    }
    dfs(0,1,1,{1},{1});
}
int main(){
    fastio;
    mu[1]=1;
    for(int i=1;i<N;i++)for(int j=i+i;j<N;j+=i)mu[j]-=mu[i];
    int tc;cin>>tc;
    while(tc--){
        cin>>n;
        work(n);
        cout<<ans<<endl;
    }
    return 0;
}
