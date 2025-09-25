#include<bits/stdc++.h>
using namespace std;
template <class code>inline code read(const code &a)
{
    code x=0;short w=0;char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)print(x/10);
	putchar(x%10+48);
}
const int maxn=2e5+5,maxm=60;
int a[maxn],lc[maxn],rc[maxn],sy[maxn],js[maxn][maxm],su[maxm][maxm],C[maxn][55],tj[maxn],dd[maxn],mp[maxn],f[maxn],fc[maxn];
int kc,zg,n,q,k,mod,tot;
set<pair<int,int> >s[maxn];
set<pair<pair<int,int>,int> >p;
vector<pair<pair<int,int>,int> >jl;
void upd1(int c,int op){
    for(int i=1;i<=zg;i++){
        for(int j=i;j<=zg;j++){
            su[i][j]+=op*fc[js[c][j]-js[c][i-1]];
            if(su[i][j]<0)su[i][j]+=mod;
            if(su[i][j]>=mod)su[i][j]-=mod;
        }
    }
}
void upd2(int l,int r,int c,int op){
    for(int i=sy[l];i<=zg;i++){
        js[c][i]+=op*(min(r,rc[i])-l+1);
    }
}
void upd(int l,int r,int c,int op){
    for(int i=1;i<=sy[r];i++){
        for(int j=max(i,sy[l]);j<=zg;j++){
            su[i][j]=su[i][j]+(fc[js[c][j]-js[c][i-1]+op*(min(r,rc[j])-max(l,lc[i])+1)]-fc[js[c][j]-js[c][i-1]]);
            if(su[i][j]<0)su[i][j]+=mod;
            if(su[i][j]>=mod)su[i][j]-=mod;
        }
    }
    upd2(l,r,c,op);
}
void xg(int l,int r,int c,int op){
    if(!op){
        upd(l,r,c,-1);
        pair<int,int>now=make_pair(l,1e9);
        auto it=s[c].upper_bound(now);
        --it;
        int pl=it->first,pr=it->second;
        s[c].erase(it);
        if(pl<l)s[c].insert(make_pair(pl,l-1)),jl.emplace_back(make_pair(make_pair(pl,l-1),c));
        if(pr>r)s[c].insert(make_pair(r+1,pr)),jl.emplace_back(make_pair(make_pair(r+1,pr),c));
    }else{
        s[c].insert(make_pair(l,r));
        upd(l,r,c,1);
    }
}
void update1(int l,int r,int c){
    jl.clear();
    vector<pair<pair<int,int>,int> >jl1;
    pair<pair<int,int>,int>x=make_pair(make_pair(l,1e9),0);
    auto it=p.upper_bound(x);
    --it;
    for(auto it1=it;it1!=p.end()&&it1->first.first<=r;++it1){
        xg(max(l,it1->first.first),min(r,it1->first.second),it1->second,0);
        jl1.emplace_back(*it1);
    }
    for(auto g:jl1)p.erase(g);
    x=make_pair(make_pair(l,r),c);
    p.insert(x);
    for(auto g:jl)p.insert(g);
    xg(l,r,c,1);
}
void update2(int c1,int c2){
    if(c1==c2)return;
    if(s[c1].size()<s[c2].size()){
        int f1=f[c1],f2=f[c2];
        upd1(f1,-1);upd1(f2,-1);
        for(auto it:s[f1]){
            upd2(it.first,it.second,f1,-1);
            upd2(it.first,it.second,f2,1);s[f2].insert(it);
            p.erase(make_pair(it,f1));
            p.insert(make_pair(it,f2));
        }
        s[f1].clear();
        upd1(f2,1);
        f[c1]=-1;
    }else{
        int f1=f[c1],f2=f[c2];
        upd1(f1,-1);upd1(f2,-1);
        for(auto it:s[f2]){
            upd2(it.first,it.second,f2,-1);
            upd2(it.first,it.second,f1,1);s[f1].insert(it);
            p.erase(make_pair(it,f2));
            p.insert(make_pair(it,f1));
        }
        s[f2].clear();
        f[c2]=f1;f[c1]=-1;
        upd1(f1,1);
    }
}
int getans(int l,int r){
    int cnt=0,pl=sy[l],pr=sy[r];
    long long ans=0;
    if(pl==pr){
        auto it=p.upper_bound(make_pair(make_pair(l,1e9),0));
        --it;
        for(;it!=p.end()&&it->first.first<=r;it++){
            int cd=min(it->first.second,r)-max(l,it->first.first)+1,c=it->second;
            ans+=fc[tj[c]+cd]-fc[tj[c]];
            tj[c]+=cd;
            dd[++cnt]=c;
        }
    }else{
        ans=su[pl+1][pr-1];
        auto it=p.upper_bound(make_pair(make_pair(l,1e9),0));
        --it;
        for(;it!=p.end()&&it->first.first<=rc[pl];it++){
            int cd=min(it->first.second,rc[pl])-max(l,it->first.first)+1,c=it->second;
            if(!mp[c])tj[c]=js[c][pr-1]-js[c][pl],mp[c]=1;
            ans+=fc[tj[c]+cd]-fc[tj[c]];
            tj[c]+=cd;
            dd[++cnt]=c;
        }
        it=p.upper_bound(make_pair(make_pair(lc[pr],1e9),0));
        --it;
        for(;it!=p.end()&&it->first.first<=r;it++){
            int cd=min(it->first.second,r)-max(lc[pr],it->first.first)+1,c=it->second;
            if(!mp[c])tj[c]=js[c][pr-1]-js[c][pl],mp[c]=1;
            ans+=fc[tj[c]+cd]-fc[tj[c]];
            tj[c]+=cd;
            dd[++cnt]=c;
        }
    }
    for(int i=1;i<=cnt;i++)mp[dd[i]]=tj[dd[i]]=0;
    return (ans%mod+mod)%mod;
}
void solve(){
    n=read(n),q=read(q),k=read(k),mod=read(mod);
    tot=n;
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=0;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=min(i,k);j++){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
        }
        fc[i]=C[i][k];
    }
    for(int i=1;i<=n;i++)a[i]=read(a[i]);
    kc=pow(n,2.0/3);
    zg=n/kc;
    for(int i=1;i<=zg;i++)lc[i]=rc[i-1]+1,rc[i]=lc[i]+kc-1;
    if(rc[zg]!=n){
        ++zg;
        lc[zg]=rc[zg-1]+1;
        rc[zg]=n;
    }
    for(int i=1;i<=zg;i++){
        for(int j=lc[i];j<=rc[i];j++)sy[j]=i;
    }
    
    for(int i=1;i<=zg;i++){
        long long now=0;
        for(int j=lc[i];j<=n;j++){
            now+=fc[tj[a[j]]+1]-fc[tj[a[j]]];
            ++tj[a[j]];
            if(j==rc[sy[j]])su[i][sy[j]]=(now%mod+mod)%mod;
        }
        for(int j=1;j<=n;j++)tj[j]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=sy[i];j<=zg;j++)js[a[i]][j]++;
    }
    for(int i=1;i<=n;i++){
        int j=i;
        while(a[j]==a[i]&&j<=n)++j;
        --j;
        s[a[i]].insert(make_pair(i,j));
        p.insert(make_pair(make_pair(i,j),a[i]));
        i=j;
    }
    while(q--){
        int op=read(op);
        int l,r,c;
        if(op==1){
            l=read(l),r=read(r),c=read(c);
            if(f[c]==-1)f[c]=++tot;
            update1(l,r,f[c]);
        }else if(op==2){
            int c1=read(c1),c2=read(c2);
            if(f[c1]==-1)continue;
            if(f[c2]==-1){
                f[c2]=f[c1];
                f[c1]=-1;
                continue;
            }
            update2(c1,c2);
        }else if(op==3){
            int l=read(l),r=read(r);
            printf("%d\n",getans(l,r));
        }
    }
    p.clear();
    for(int i=1;i<=tot;i++){
        s[i].clear();
        memset(js[i],0,sizeof(js[i]));
        if(i<=zg)memset(su[i],0,sizeof(su));
    }
}
signed main(){
    int t=read(t);
    while(t--)solve();
	return 0;
}
