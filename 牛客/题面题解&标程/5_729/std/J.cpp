#include<bits/stdc++.h>
using namespace std;using ll=long long;using pii=pair<int,int>;
const int M=998244353;
int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct S
{	
	int n,m;vector<vector<int>>mat;
    vector<pii>Q;int l=0,r=0;
    int mi[2]={M,M},ma[2]={-M,-M};
    void upd(int y,int x){int v[2]={y-x,y+x};for(int z=0;z<2;z++)mi[z]=min(mi[z],v[z]),ma[z]=max(ma[z],v[z]);}
	int qry()
    {       
        int d[2]={ma[0]-mi[0],ma[1]-mi[1]},mx=max(d[0],d[1]);
        int sp=(d[0]==d[1])&&(d[0]%2==0)&&((ma[0]+ma[1])%2);
        return (mx+sp+1)/2;
    }
    void solve()
	{   
        cin>>n>>m;mat.resize(n+2,vector<int>(m+2,-1));
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
            {auto&v=mat[i][j];cin>>v;if(!v)v=M;else v=0,Q.push_back({i,j}),r++;}
        while(l<r)
        {
            auto [y,x]=Q[l++];int dis=mat[y][x]+1;
            for(int z=0;z<4;z++)
            {
                int ny=y+d[z][0],nx=x+d[z][1];
                if(mat[ny][nx]==M)mat[ny][nx]=dis,Q.push_back({ny,nx}),r++;
            }
        }
        int ans=M;
        while(r--)
        {
            auto [y,x]=Q[r];
            int ta=mat[y][x],tb=qry();
            ans=min(ans,max(ta,tb));
            upd(y,x);
        }
        upd(1,1);upd(1,m);upd(n,1);upd(n,m);ans=min(ans,qry());
        cout<<ans<<'\n';
	}
};
void precal()//
{

}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
    precal();int t=1;//cin>>t;
	while(t--){S SS;SS.solve();}
}