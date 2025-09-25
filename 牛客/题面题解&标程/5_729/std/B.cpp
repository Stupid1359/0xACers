#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pb push_back
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define _rep(i,s,t) for(int i=s;i>=t;--i)
using namespace std;
const int N=1e6+11,mod=998244353,P=52;
void inc(int &x,int y){
	x+=y;
	if(x>=mod)
		x-=mod;
}
int n,k;
struct matrix{
	int a[P+1][P+1];
	matrix(int x=0){
		memset(a,0,sizeof a);
		rep(i,0,P)
			a[i][i]=x;
	}
	int *operator[](const int x){
		return a[x];
	}
	matrix operator*(matrix A)const{
		matrix res;
		rep(k,0,P-1)
			rep(i,0,P-1)
				if(a[i][k])
					rep(j,0,P-1)
						if(A[k][j])
							res[i][j]=(res[i][j]+1ll*a[i][k]*A[k][j])%mod;
		return res;
	}
	matrix operator+(matrix A)const{
		matrix res;
		rep(i,0,P)
			rep(j,0,P)
				res[i][j]=(a[i][j]+A[i][j])%mod;
		return res;
	}
}A,S,a,I;
void Sum(int k){
	if(k==0){
		S=matrix(1);
		a=matrix(1);
		return ;
	}
	if(k&1){
		Sum(k/2);
		matrix b=a*A;
		S=(b+I)*S;
		a=a*b;
	}
	else{
		Sum(k-1);
		S=A*S+I;
		a=a*A;
	}
}
struct SAM{
    int ch[N][P+1],las=1,cnt=1,sz[N],fa[N],l[N],c[N],pos[N],val[N],deg[N];
    int path[P+1][N],sum[N];
    vector<int>go[N];
    ll ans;
    void init(){
    	rep(i,1,n+n){
    		memset(ch[i],0,sizeof ch[i]);
    		val[i]=pos[i]=c[i]=fa[i]=l[i]=sz[i]=0;
		}
		las=cnt=1;
		ans=0;
	}
    void add(int c){
        int np=++cnt,p=las;las=np;l[np]=l[p]+1;
        for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;
        if(!p)fa[np]=1;
        else{
            int q=ch[p][c];
            if(l[p]+1==l[q])
                fa[np]=q;
            else{
                int nq=++cnt;l[nq]=l[p]+1;
                memcpy(ch[nq],ch[q],sizeof ch[q]);
                fa[nq]=fa[q],fa[q]=fa[np]=nq;
                for(;ch[p][c]==q;p=fa[p])ch[p][c]=nq;
            }
        }
        sz[np]=1;
    }
    void solve(){
        int p;
        rep(i,1,cnt)
            ++c[l[i]];
        rep(i,1,cnt)
            c[i]+=c[i-1];
        _rep(i,cnt,1)
            pos[c[l[i]]--]=i;
        _rep(i,cnt,1)
            p=pos[i],sz[fa[p]]+=sz[p];
        rep(i,1,cnt)
        	rep(j,0,P-1)
        		if(ch[i][j]){
        			go[i].push_back(ch[i][j]);
				}
        rep(i,0,P-1)
        	if(ch[1][i]){
        		queue<int>q;
        		path[i][ch[1][i]]=1;
        		rep(j,1,cnt){
        			int p=pos[j];
        			for(auto v:go[p]){
        				inc(path[i][v],path[i][p]);
					}
				}
			}
		rep(i,2,cnt)
			rep(j,0,P-1)
				if(!ch[i][j])
					rep(k,0,P-1)
						inc(A[k][j],path[k][i]);
		Sum(k-1);
		int ans=1;
		rep(i,0,P-1)
			rep(j,0,P-1)
				inc(sum[j],S[i][j]);
		rep(j,0,P-1)
			rep(k,1,cnt)
				ans=(ans+1ll*sum[j]*path[j][k])%mod;
		printf("%d\n",ans);
	}
}sam;
char Str[N];
int g(char x){
	if('a'<=x&&x<='z')return x-'a';
	return x-'A'+26;
}
void solve(){
	scanf("%d%d",&n,&k);
	I=matrix(1);
    scanf("%s",Str+1);
	sam.init();
	rep(i,1,n)
        sam.add(g(Str[i]));
    sam.solve();
}
int main(){
	solve();
	return 0;
}