#include<bits/stdc++.h>
using namespace std;
using ll=long long;using i128=__int128;using ld=long double;
using pii=pair<int,int>;using pll=pair<ll,ll>;using ppl=pair<pll,pll>;
const ld eps=1e-7;const int M=998244353;const ll inf=1e17;
void opErr(string s){cout<<"Err:"<<s<<"\n";exit(0);}
namespace geometry_pack2
{
    #define pT pair<T,T>
    #define X first
    #define Y second
	template<typename T>void Dop(pT a){cout<<"("<<a.X<<','<<a.Y<<")";}
	template<typename T>T fxv(T v){if(abs(v)<eps)return 0;return v>0?1:-1;}
    template<typename T>T operator+(const T&a,const T&b){return{a.X+b.X,a.Y+b.Y};}
    template<typename T>T operator-(const T&a,const T&b){return{a.X-b.X,a.Y-b.Y};}
    template<typename T>T operator%(const pair<T,T>&a,const pair<T,T>&b){return a.X*b.Y-a.Y*b.X;}//sin(b-a) a%b<0:a=b+eps
    template<typename T>bool gs(T&a){return a.second<0||(a.second==0&&a.first<0);}
	template<typename T>bool LL_closer_to_O(pT A,pT A2,pT B,pT B2)
	{//两(不含边界)不交线段(角度逆时针走向),角度并区间上哪个离原点更近 0:A 1:B		
		if(A%A2<0)swap(A,A2);if(B%B2<0)swap(B,B2);
		ll v0=fxv((A2-A)%(B-A)),v1=fxv((A2-A)%(B2-A));if(v0*v1!=-1)return fxv(v0+v1)==1;swap(A,B),swap(A2,B2);
		v0=fxv((A2-A)%(B-A)),v1=fxv((A2-A)%(B2-A));if(v0*v1!=-1)return fxv(v0+v1)==-1;opErr("closer");
	}
	struct Num
	{
		ll B,u,d;
		bool operator<(const Num&e)const
		{
			if(B^e.B)return B<e.B;
			return i128(u)*e.d<i128(d)*e.u;
		}
	};
	Num gds(pll A,pll B,pll C,pll D)//A+x*vec(AB),line with C&D
	{
		ll vU=(C-A)%(D-A),vD=(B-A)%(D-C);
		if(vD<0)vU=-vU,vD=-vD;return {0,vU,vD};
	}
    #undef X
    #undef Y
}using namespace geometry_pack2;
struct cmp2
{
	bool operator()(const pll&a,const pll&b)const//正右最小,逆时针
		{bool c=gs(a),d=gs(b);if(c^d)return !c;return a%b>0;}//{0,0}例外	
};
struct S2
{
	int n,m=0;
	vector<pll>Arr;vector<int>ocp,litv;
    set<pair<pii,int>>xS;
	bool cp(int a,int b)
    {
        if(a==-1)return 1;if(b==-1)return 0;
        return LL_closer_to_O(Arr[a],Arr[(a+1)%n],Arr[b],Arr[(b+1)%n]);
    }
    void Ins(int l,int r,int id){if(l^r)xS.insert({{r,l},id});}
    ll p,ph;
    void InsA(ll l,ll r,int i)//+
    {       
        if(l>p||r<=p)return;ll D=min({l,r,p})/m;
		l-=D*m,r-=D*m,p-=D*m;l=p;
        while(1)
        {
            if(p==r){Ins(l,p,i);break;}         
            auto ite=xS.lower_bound({{p+1,-M},-M});
            auto [_,id2]=*ite;auto [r2,l2]=_;
            if(cp(i,id2)){Ins(l,p,i);break;}
            xS.erase(ite);if(l2<l)Ins(l2,l,id2);if(r2>r)Ins(r,r2,id2);p=min(r,ll(r2));                  
        }
		p+=D*m;
	}
    void InsB(ll l,ll r,int i)//-
    {
        if(r<p||l>=p)return;ll D=min({l,r,p})/m;		
		l-=D*m,r-=D*m,p-=D*m;r=p;
        while(1)
        {
            if(p==l){Ins(p,r,i);break;}
            auto ite=xS.lower_bound({{p,-M},-M});
            auto [_,id2]=*ite;auto [r2,l2]=_;
            if(cp(i,id2)){Ins(p,r,i);break;}
            xS.erase(ite);if(l2<l)Ins(l2,l,id2);if(r2>r)Ins(r,r2,id2);p=max(l,ll(l2));                  
        }
		p+=D*m;
    }
    vector<int>Sol(pll O,vector<pll>&_Arr)
	{
        n=_Arr.size();Arr.resize(n);litv.resize(n,0);map<pll,int,cmp2>mp;
		for(int i=0;i<n;i++)Arr[i]=_Arr[i]-O,mp[Arr[i]]=1;for(auto&[p,b]:mp)b=m++;        
		xS.insert({{m,0},-1});
		int pS=-1;Num V={1,0,1};
        for(int i=0;i<n;i++)
        {
            auto pL=Arr[i],pR=Arr[(i+1)%n];
            int dv=fxv(pL%pR);if(dv!=1)continue;
            if(pR.second<0||pL.second>0)continue;
            auto nd=gds(pll{0,0},pll{1,0},Arr[i],Arr[(i+1)%n]);
            auto [_,vU,vD]=nd;if(vU<0)continue;if(nd<V)V=nd,pS=i;
        }
		p=ph=mp[Arr[pS]]+ll(1e9)*m;
		for(int z=0,i=pS;z<n;z++,i=(i+1)%n)
		{
			auto pL=Arr[i],pR=Arr[(i+1)%n];
			int dv=fxv(pL%pR);if(!dv)continue;
			int il=mp[pL],ir=mp[pR];
			ll pl=ph,pr=pl+ir-il;
			if(dv==1)
			{
				if(il<ir)InsA(pl,pr,i);
				else
				{
					pr+=m;ll Div=max(pl,pr)/m*m;
					InsA(pl,Div,i);InsA(Div,pr,i);
				}
			}
			else
			{				
				if(il>ir)InsB(pr,pl,i);
				else
				{
					pr-=m;ll Div=max(pl,pr)/m*m;
					InsB(Div,pl,i);InsB(pr,Div,i);
				}			
			}
			ph=pr;
		}
		ocp.resize(m+1,-1);for(auto&[p,id]:xS){auto [r,l]=p;for(int i=l;i<r;i++)ocp[i]=id;}		
		for(int i=0;i<n;i++)
		{
			int pos=mp[Arr[i]],E[2];
            for(int da=0;da<2;da++)E[da]=ocp[(pos+m-da)%m];
            if(E[0]==E[1])continue;bool sp=cp(E[0],E[1]);
            for(int db=0;db<2;db++)if(E[sp]==(i+n-db)%n)litv[i]=1;
		}
		for(int i=0;i<n;i++)cout<<litv[i]<<" \n"[i==n-1];
        return litv;
	}
    int g_bord(int l,int r)
	{
		pll Bl=Arr[l],Br=Arr[r];int bd=-1;
		for(int i=0;i<n;i++)
		{
			auto pL=Arr[i],pR=Arr[(i+1)%n];if(pL%pR<=0)continue;
			if(Bl%pR<0)continue;if(pL%Br<0)continue;
            if(Bl%pL>0)continue;if(pR%Br>0)continue;///!!!std8->9
			if(bd==-1||LL_closer_to_O(Arr[bd],Arr[(bd+1)%n],pL,pR))bd=i;
		}
		return bd;
	}
};
struct S
{
	int n,l[2]={-1,-1},r[2]={-1,-1},Bord[2]={-1,-1};
	pll Dot[2];vector<pll>Arr;vector<int>Visr[2];S2 Nd[2];
	map<Num,int>mp;
	void F(int x){cout<<(x?"Yes\n":"No\n");}	
	void solve()
	{	
		cin>>n;for(int z=0;z<2;z++){auto&[x,y]=Dot[z];cin>>x>>y;}
		Arr.resize(n);for(auto&[x,y]:Arr)cin>>x>>y;	
		for(int z=0;z<2;z++)Visr[z]=Nd[z].Sol(Dot[z],Arr);

        for(int _=0,lp=-1,lc=-1,cnt=0;_<2;_++)for(int i=0;i<n;i++)
        {
            auto v0=Visr[0][i],v1=Visr[1][i];
            if(v0&&v1)return F(1);if(!v0&&!v1)continue;int c=v1;
            if(lc!=-1&&lc!=c){if(++cnt==3)return F(1);l[c]=i,r[lc]=lp;}
            lp=i,lc=c;if(_)break;
        }		

		for(int z=0;z<2;z++)Bord[z]=Nd[z].g_bord(l[z],r[z]);
		for(int i=0;i<n;i++)for(int sa=0;sa<2;sa++)mp[{i,0,1}]|=Visr[sa][i]<<sa;
		for(int sa=0;sa<2;sa++)for(int sb=0;sb<2;sb++)
		{
			int bd=Bord[sa];
			ll U=(Dot[sa]-Arr[bd])%(Arr[sb?r[sa]:l[sa]]-Arr[bd]);
			ll D=(Arr[(bd+1)%n]-Arr[bd])%(Arr[sb?r[sa]:l[sa]]-Dot[sa]);
			if(D<0)U=-U,D=-D;if(U==D)U=0,bd=(bd+1)%n;mp[{bd,U,D}]|=(1<<sa);
		}
        /*
        for(auto [nd,w]:mp)
        {
            cout<<nd.B<<"_"<<nd.u<<"/"<<nd.d<<"^"<<w<<'\n';
        }*/
        vector<vector<int>>dp(2,vector<int>(5,0));dp[0][0]=dp[1][0]=1;
		for(auto [nd,w]:mp)
        {
            bool v[2]={w&1,w&2};
            for(int p=4;p;p--)for(int z=0;z<2;z++)dp[z][p]|=(v[z]&dp[z^1][p-1]);
        }		
		return F(dp[0][4]||dp[1][4]);
	}
};
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	//freopen("1.in","r",stdin);
	int t=1;cin>>t;
	while(t--){S SS;SS.solve();}
}