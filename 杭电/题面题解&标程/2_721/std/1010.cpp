#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int M=1e5+5,K=1e5+5;
int m,k,t[K],a[M],but[M];
struct H{
    int x,y,id;
    bool operator < (const H op2)const{
        return (ll)x*op2.y<(ll)op2.x*y;
    }
    bool operator == (const H op2)const{
        return (ll)x*op2.y==(ll)op2.x*y;
    }
};
priority_queue<H> q;
struct PA{
    int x,y;
};
vector<PA> ans;
void print(){
    cout<<ans.size()<<"\n";
    for(auto i:ans)cout<<i.x<<' '<<i.y<<'\n';
}
bool check0(){
    for(int i=1;i<=m;++i)if(but[i]>a[i])return true;
    return false;
}
vector<PA> vt;
vector<vector<int>> v,len,vis;
vector<int> nt;
int le[M],un[M],ti[M];//le>=un
void solve(){
    if(check0()){
        for(int i=1;i<=m;++i)
        if(a[i]){
            ans.pb({a[i],i});
        }
        return;
    }

    vt.clear();
    v.clear();v.resize(m+1);
    len.clear();len.resize(m+1);
    vis.clear();vis.resize(m+1);

    vt.pb({1,t[1]});
    for(int i=2;i<=k;++i){
        if(t[i]==t[i-1])++vt.back().x;
        else vt.pb({1,t[i]});
    }
    for(int i=0;i<vt.size();++i){
        v[vt[i].y].pb(vt[i].x);
    }
    for(int i=1;i<=m;++i)
    if(but[i]){
        while(!q.empty())q.pop();
        len[i].assign(v[i].size(),1);
        vis[i].assign(v[i].size(),0);
        for(int j=0;j<v[i].size();++j){
            q.push({v[i][j],1,j});
        }
        int ss=a[i]-but[i];
        H last;
        while(ss--){
            last=q.top();
            ++len[i][last.id];
            q.pop();
            if(ss){
                ++last.y;
                q.push(last);
            }
        }
        for(int j=0;j<v[i].size();++j){
          if(a[i]>but[i]){
			H h={v[i][j],len[i][j],j};
            if(h==last){
                vis[i][j]=1;
                ++le[i];
            }
            else{
                --h.y;
                if(h==last){
                    --len[i][j];
                    vis[i][j]=1;
                    ++le[i],++un[i];
                }
            }
		  }
            len[i][j]+=v[i][j]-1;
        }
    }
    nt.clear();
    for(int i=m;i>=1;--i)if(!but[i]&&a[i])nt.pb(i);
    for(int i=0;i<vt.size();++i){
        while(!nt.empty()){
            if(nt.back()>vt[i].y)break;
            ans.pb({a[nt.back()],nt.back()});
            nt.pop_back();
        }
        ans.pb({0,vt[i].y});
    }
    while(!nt.empty()){
        ans.pb({a[nt.back()],nt.back()});
        nt.pop_back();
    }
    for(int i=0;i<ans.size();++i){
        int&x=ans[i].x;
        int&y=ans[i].y;
        if(!but[y])continue;
        if(!vis[y][ti[y]]){
            x=len[y][ti[y]];
        }
        else{
            if(un[y]==le[y]||(y<ans[i+1].y&&un[y])){
                x=len[y][ti[y]]+1;
                --le[y],--un[y];
            }
            else{
                x=len[y][ti[y]];
                --le[y];
            }
        }
        ++ti[y];
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--)
{
    cin>>m>>k;
    for(int i=1;i<=k;++i)cin>>t[i],++but[t[i]];
    for(int i=1;i<=m;++i)cin>>a[i];
    solve();
    print();
    ans.clear();
    memset(but,0,(m+2)*4);
    memset(le,0,(m+2)*4);
    memset(un,0,(m+2)*4);
    memset(ti,0,(m+2)*4);
}
    return 0;
}
