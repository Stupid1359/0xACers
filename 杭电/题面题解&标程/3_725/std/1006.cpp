#include<bits/stdc++.h>
using namespace std;using ll=long long;
const int M=1e9+7,P=30,N=10;
ll f[N+1][N+1][N+1][2];//lm,rm,s_lf,x_tight
ll g[N+1][N+1][N+1][2];
ll C[N+1][N+1];
void add(ll&a,ll b){a+=b;if(a>=M)a-=M;}
struct btb
{	
	int n;vector<int>Vl,Vr,Vs,Vx;
    void iniv(vector<int>&v){v.resize(P,0);ll x;cin>>x;for(int i=0;i<P;i++)v[i]=x>>i&1;}
    void pre(){iniv(Vl);iniv(Vr);iniv(Vs);iniv(Vx);}
	void solve()
	{
        cin>>n;pre();
        memset(f,0,sizeof(f));memset(g,0,sizeof(g));f[0][0][0][1]=1;
        for(int z=P-1,lrt=1;z>=0;z--)
        {
            if(Vl[z]==Vr[z]&&lrt)
            {
                for(int slf=0;slf<=n;slf++)for(int xt=0;xt<2;xt++)
                {
                    ll v=f[0][0][slf][xt];
                    int slf2=slf*2+Vs[z]-Vl[z]*n;if(slf2<0)continue;slf2=min(slf2,n);
                    int se=Vx[z],se2=(n&1)&(Vl[z]&1);
                    int xt2;if(se==se2)xt2=xt;else if(se2){if(xt)continue;else xt2=xt;}else xt2=0;
                    add(g[0][0][slf2][xt2],v);
                }               
            }
            else if(lrt)
            {
                lrt=0;
                for(int slf=0;slf<=n;slf++)for(int xt=0;xt<2;xt++)
                {
                    ll v=f[0][0][slf][xt];
                    for(int sl=0,sr=n;sl<=n;sl++,sr--)
                    {
                        int slf2=slf*2+Vs[z]-sr;if(slf2<0)continue;slf2=min(slf2,n);
                        int se=Vx[z],se2=sr&1;
                        int xt2;if(se==se2)xt2=xt;else if(se2){if(xt)continue;else xt2=xt;}else xt2=0;
                        add(g[sl][sr][slf2][xt2],v*C[n][sl]%M);
                    }     
                }
            }
            else
            {
                for(int bl=0;bl<=n;bl++)for(int br=0;br<=n-bl;br++)for(int slf=0;slf<=n;slf++)for(int xt=0;xt<2;xt++)
                {
                    ll v=f[bl][br][slf][xt];//if(!v)continue;
                    int bm=n-bl-br;
                    for(int ltl=0,ltr=bl;ltl<=bl;ltl++,ltr--)if(Vl[z]==0||!ltl)
                    {
                        ll v2=v*C[bl][ltl]%M;
                        for(int rtl=0,rtr=br;rtl<=br;rtl++,rtr--)if(Vr[z]==1||!rtr)
                        {
                            ll v3=v2*C[br][rtl]%M;
                            for(int mtl=0,mtr=bm;mtl<=bm;mtl++,mtr--)
                            {
                                int c=ltr+rtr+mtr,nl=Vl[z]?ltr:ltl,nr=Vr[z]?rtr:rtl;
                                int slf2=slf*2+Vs[z]-c;if(slf2<0)continue;slf2=min(slf2,n);
                                int se=Vx[z],se2=c&1;
                                int xt2;if(se==se2)xt2=xt;else if(se2){if(xt)continue;else xt2=xt;}else xt2=0;
                                add(g[nl][nr][slf2][xt2],v3*C[bm][mtl]%M);
                            }
                        }
                    }                   
                }
            }
            memcpy(f,g,sizeof(g));memset(g,0,sizeof(g));
        }
        ll res=0;
        for(int bl=0;bl<=n;bl++)for(int br=0;br<=n-bl;br++)for(int slf=0;slf<=n;slf++)for(int xt=0;xt<2;xt++)add(res,f[bl][br][slf][xt]);
        cout<<res<<'\n';
	}
};
void precal()
{
    for(int i=0;i<=N;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%M;
    }
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
    precal();int t=1;cin>>t;
	while(t--){btb RR;RR.solve();}
}