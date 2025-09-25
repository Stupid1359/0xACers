#include<bits/stdc++.h>
using namespace std;
 
//#define int long long
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
#define all(_array) (_array).begin(),(_array).end()
#define msp(_array) memset(_array,0x3f,sizeof _array)
#define ms0(_array) memset(_array,0,sizeof _array)
#define msn(_array) memset(_array,-1,sizeof _array)
#define mc(_tar,_array) memcpy(_tar,_array,sizeof _tar)
#define Yes cout<<"Yes"<<endl,void()
#define No cout<<"No"<<endl,void()
#define YES cout<<"YES"<<endl,void()
#define NO cout<<"NO"<<endl,void()
#define yes cout<<"yes"<<endl,void()
#define no cout<<"no"<<endl,void()
#define TAK cout<<"TAK"<<endl,void()
#define NIE cout<<"NIE"<<endl,void()
#define OK cerr<<"OK"<<endl,void()
#define pii pair<int,int>
#define endl '\n'
 
bool bg_memory;
mt19937_64 rnd(time(0));
chrono::_V2::system_clock::time_point bg_clock,en_clock;
int Case=1;
const int mod=1e9+7;
const int inf=1e7;
const int bs=233;
const double eps=1e-6;
const int N=4e4+7,M=4e4+7;
 
template<class _t1,class _t2>inline void cmax(_t1 &a,_t2 b){a=a<b?b:a;}
template<class _t1,class _t2>inline void cmin(_t1 &a,_t2 b){a=a>b?b:a;}
inline int qp(int a,int b,int p=mod){int res=1;while(b){if(b&1)res=1ll*res*a%p;a=1ll*a*a%p;b>>=1;}return res;}
inline int sqrt(int x,int r){int l=0,ans=0;while(l<=r){if(1ll*mid*mid<=x) ans=mid,l=mid+1;else r=mid-1;}return ans;}
char buf[1<<24],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<24,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	int x=0;char ch=0;
	while((ch<'0'||ch>'9'))ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch-'0'),ch=getchar();
	return x;
} 
char pbuf[1<<24], *pp;
void push(const char &c) {
    if (pp - pbuf == 1<<24) fwrite(pbuf, 1, 1<<24, stdout), pp = pbuf;
    *pp++ = c;
}
inline void write(long long x,char tl=0){
	static char sta[18];
	int top=0;
	do{sta[top++]=x%10,x/=10;}while(x);
	while(top)push(sta[--top]+48);
	if(tl)push(tl);
}


int n,q,s,k;
int ql[N],qr[N],qd[N];
int ans[N];
vector<int> v[N];
int fa[N];
bool leaf[N];
array<int,3> dp[N][8];
struct node{
    int a,b,c,d;
    bool q;
}px[8][N<<1];
inline bool cmp00(node&a,node&b){if(a.c!=b.c) return a.c<b.c;if(a.a!=b.a) return a.a<b.a;if(a.b!=b.b) return a.b<b.b;return a.q<b.q;}
inline bool cmp010(node&a,node&b){if(a.a!=b.a) return a.a<b.a;if(a.c!=b.c) return a.c>b.c;if(a.b!=b.b) return a.b<b.b;return a.q<b.q;}
inline bool cmp011(node&a,node&b){if(a.c!=b.c) return a.c>b.c;if(a.a!=b.a) return a.a<b.a;if(a.b!=b.b) return a.b<b.b;return a.q<b.q;}
inline bool cmp10(node&a,node&b){if(a.a!=b.a) return a.a<b.a;if(a.c!=b.c) return a.c<b.c;if(a.b!=b.b) return a.b<b.b;return a.q<b.q;}
int len;
int C[M<<1];
inline void add(int x,int y){
    x+=M;
    if(y==-1) for(;x<(M<<1);x+=x&-x) C[x]=0;
    else for(;x<(M<<1);x+=x&-x) cmax(C[x],y);
}
inline int ask(int x){
    x+=M;
    int res=0;
    for(;x;x-=x&-x) cmax(res,C[x]);
    return res;
}
inline void dfs(int x){
    int sz=v[x].size();
    int mk=-1;
    for(int i=sz-1;i>=0;i--){
        if(leaf[v[x][i]]) mk=i;
        for(int j=0;j<4;j++){
            array<int,3> k=min(dp[x][j],dp[x][j+4]);
            dp[v[x][i]][j+4]={k[0],k[1]+i,k[2]+1};
        }
    }
    for(int i=0;i<sz;i++){
        array<int,3> k=min(dp[x][0],dp[x][4]);
        array<int,3> l=min(dp[x][2],dp[x][6]);l={l[0],l[1]+i,l[2]+1};
        dp[v[x][i]][6]=min((array<int,3>){k[0]+sz-i-1,k[1]+sz-1,k[2]+1},l);
    }
    if(mk!=-1){
        for(int i=0;i<sz;i++){
            array<int,3> k=min(dp[x][0],dp[x][4]);
            array<int,3> l=min(dp[x][1],dp[x][5]);l={l[0],l[1]+i,l[2]+1};
            if(mk<=i) dp[v[x][i]][5]=min((array<int,3>){k[0],k[1]+i,k[2]+1},l);
            else dp[v[x][i]][5]=min((array<int,3>){k[0]+mk-i,k[1]+mk,k[2]+1},l);
        }
        for(int i=0;i<sz;i++){
            array<int,3> k=min({dp[x][0],dp[x][4],dp[x][1],dp[x][5]});k={k[0]+sz-i-1,k[1]+sz-1,k[2]+1};
            array<int,3> l=min({dp[x][3],dp[x][7]});l={l[0],l[1]+i,l[2]+1};
            array<int,3> m=min({dp[x][2],dp[x][6]});
            if(mk<=i) dp[v[x][i]][7]=min({k,l,(array<int,3>){m[0],m[1]+i,m[2]+1}});
            else dp[v[x][i]][7]=min({k,l,(array<int,3>){m[0]+mk-i,m[1]+mk,m[2]+1}});
        }
    }else{
        for(int i=0;i<sz;i++){
            array<int,3> k=min(dp[x][1],dp[x][5]);
            array<int,3> l=min(dp[x][3],dp[x][7]);l={l[0],l[1]+i,l[2]+1};
            dp[v[x][i]][7]=min((array<int,3>){k[0]+sz-i-1,k[1]+sz-1,k[2]+1},l);
        }
    }
    for(int i:v[x]) dfs(i);
}
node Tmp[N<<1];
void merge011(int l,int m,int r){
	int i=l,j=m,k=l;
	while(i<m&&j<=r){
		if(cmp011(px[3][i],px[3][j])) Tmp[k++]=px[3][i++];
		else Tmp[k++]=px[3][j++];
	}
	while(i<m) Tmp[k++]=px[3][i++];
	while(j<=r) Tmp[k++]=px[3][j++];
	for(int i=l;i<=r;++i) px[3][i]=Tmp[i];
}
inline void cdq011(int l,int r){
    if(l==r) return;
    cdq011(l,mid);
    cdq011(mid+1,r);
    int j=l;
    for(int i=mid+1;i<=r;i++){
        while(j<=mid&&px[3][j].c>=px[3][i].c){
            if(px[3][j].q==0) add(px[3][j].b,px[3][j].d);
            j++;
        }
        if(px[3][i].q) cmax(ans[px[3][i].d],ask(px[3][i].b));
    }
    for(int i=l;i<j;i++) add(px[3][i].b,-1);
    if(!(l==1&&r==len)) merge011(l,mid+1,r);
}
void merge101(int l,int m,int r){
	int i=l,j=m,k=l;
	while(i<m&&j<=r){
		if(cmp00(px[5][i],px[5][j])) Tmp[k++]=px[5][i++];
		else Tmp[k++]=px[5][j++];
	}
	while(i<m) Tmp[k++]=px[5][i++];
	while(j<=r) Tmp[k++]=px[5][j++];
	for(int i=l;i<=r;++i) px[5][i]=Tmp[i];
}
inline void cdq101(int l,int r){
    if(l==r) return;
    cdq101(l,mid);
    cdq101(mid+1,r);
    int j=l;
    for(int i=mid+1;i<=r;i++){
        while(j<=mid&&px[5][j].c<=px[5][i].c){
            if(px[5][j].q==0) add(px[5][j].b,px[5][j].d);
            j++;
        }
        if(px[5][i].q) cmax(ans[px[5][i].d],ask(px[5][i].b));
    }
    for(int i=l;i<j;i++) add(px[5][i].b,-1);
    if(!(l==1&&r==len)) merge101(l,mid+1,r);
}
void merge111(int l,int m,int r){
	int i=l,j=m,k=l;
	while(i<m&&j<=r){
		if(cmp00(px[7][i],px[7][j])) Tmp[k++]=px[7][i++];
		else Tmp[k++]=px[7][j++];
	}
	while(i<m) Tmp[k++]=px[7][i++];
	while(j<=r) Tmp[k++]=px[7][j++];
	for(int i=l;i<=r;++i) px[7][i]=Tmp[i];
}
inline void cdq111(int l,int r){
    if(l==r) return;
    cdq111(l,mid);
    cdq111(mid+1,r);
    int j=l;
    for(int i=mid+1;i<=r;i++){
        while(j<=mid&&px[7][j].c<=px[7][i].c){
            if(px[7][j].q==0) add(px[7][j].b,px[7][j].d);
            j++;
        }
        if(px[7][i].q) cmax(ans[px[7][i].d],ask(px[7][i].b));
    }
    for(int i=l;i<j;i++) add(px[7][i].b,-1);
    if(!(l==1&&r==len)) merge111(l,mid+1,r);
}
 
void Main(){
    
    n=read(),q=read(),s=read();
    for(int i=1;i<=n;i++) fa[i]=leaf[i]=0,v[i].clear();
    for(int i=1;i<=n;i++){
        k=read();
        for(int j=1,x;j<=k;j++) x=read(),v[i].push_back(x),fa[x]=i;
        if(!k) leaf[i]=1;
    }
    for(int i=1;i<=n;i++) for(int j=0;j<8;j++) dp[i][j]={inf,inf,inf};
    for(int j=0;j<8;j++) px[j][0]={inf,inf,inf};
    if(!fa[s]) dp[s][6+leaf[s]]={0,0,0},dfs(s);
    else{
        int pos,sz=v[fa[s]].size();
        int makl=-1,makr=-1;
        for(int i=0;i<sz;i++) if(v[fa[s]][i]==s) pos=i;
        for(int i=pos;i<sz;i++) if(leaf[v[fa[s]][i]]){makr=i;break;}
        for(int i=pos;i>=0;i--) if(leaf[v[fa[s]][i]]){makl=i;break;}
        for(int i=0;i<sz;i++)
        if(pos>i) dp[v[fa[s]][i]][0]={pos-i,0,0};
        else dp[v[fa[s]][i]][0]={0,i-pos,0};
        for(int i=0;i<sz;i++) dp[v[fa[s]][i]][4]={pos,i,0};
        for(int i=0;i<sz;i++) dp[v[fa[s]][i]][2]={sz-i-1,sz-pos-1,0};
        for(int i=0;i<sz;i++)
        if(pos>i) dp[v[fa[s]][i]][6]={sz-1,sz-pos-1+i,0};
        else dp[v[fa[s]][i]][6]={sz-i-1+pos,sz-1,0};
        for(int i=pos;i>=0;i--){
            if(makl!=-1&&makl>=i) dp[v[fa[s]][i]][1]={pos-i,0,0};
            else if(makl!=-1&&makr!=-1)
            dp[v[fa[s]][i]][1]={pos-i+min(makr-pos,i-makl),min(makr-pos,i-makl),0};
            else if(makl!=-1)
            dp[v[fa[s]][i]][1]={pos-makl,i-makl,0};
            else if(makr!=-1)
            dp[v[fa[s]][i]][1]={makr-i,makr-pos,0};
        }
        for(int i=pos+1;i<sz;i++){
            if(makr!=-1&&makr<=i) dp[v[fa[s]][i]][1]={0,i-pos,0};
            else if(makl!=-1&&makr!=-1)
            dp[v[fa[s]][i]][1]={min(makr-i,pos-makl),i-pos+min(makr-i,pos-makl),0};
            else if(makr!=-1)
            dp[v[fa[s]][i]][1]={makr-i,makr-pos,0};
            else if(makl!=-1)
            dp[v[fa[s]][i]][1]={pos-makl,i-makl,0};
        }
        for(int i=pos;i>=0;i--){
            if(makl!=-1) dp[v[fa[s]][i]][5]={pos,i,0};
            else if(makr!=-1) dp[v[fa[s]][i]][5]={makr,i+makr-pos,0};
        }
        for(int i=pos+1;i<sz;i++){
            if((makr!=-1&&makr<=i)||makl!=-1) dp[v[fa[s]][i]][5]={pos,i,0};
            else if(makr!=-1) dp[v[fa[s]][i]][5]={pos+makr-i,makr,0};
        }
        for(int i=pos;i>=0;i--){
            if((makl!=-1&&makl>=i)||makr!=-1) dp[v[fa[s]][i]][3]={sz-i-1,sz-pos-1,0};
            else if(makl!=-1) dp[v[fa[s]][i]][3]={sz-makl-1,sz-pos-1+i-makl,0};
        }
        for(int i=pos+1;i<sz;i++){
            if(makr!=-1) dp[v[fa[s]][i]][3]={sz-i-1,sz-pos-1,0};
            else if(makl!=-1) dp[v[fa[s]][i]][3]={sz-i-1+pos-makl,sz-makl-1,0};
        }
        for(int i=pos;i>=0;i--) if(makl!=-1||makr!=-1) dp[v[fa[s]][i]][7]={sz-1,sz-pos-1+i,0};
        for(int i=pos+1;i<sz;i++) if(makl!=-1||makr!=-1) dp[v[fa[s]][i]][7]={sz-i-1+pos,sz-1,0};
        for(int i:v[fa[s]]) dfs(i);
    }
    len=n;
    for(int i=1;i<=n;i++){
        array<int,3> k;
        k=dp[i][0];px[0][i]={k[2],k[0],k[0]-k[1],i,0};
        k=dp[i][1];px[1][i]={k[2],k[0],k[0]-k[1],i,0};
        k=dp[i][2];px[2][i]={k[2],k[0],k[0]-k[1],i,0};
        k=dp[i][3];px[3][i]={k[2],k[0],k[0]-k[1],i,0};
        k=dp[i][4];px[4][i]={k[2],k[1],k[0]-k[1],i,0};
        k=dp[i][5];px[5][i]={k[2],k[1],k[0]-k[1],i,0};
        k=dp[i][6];px[6][i]={k[2],k[0],k[1],i,0};
        k=dp[i][7];px[7][i]={k[2],k[0],k[1],i,0};
    }
    for(int i=1;i<=q;i++){
        ql[i]=read(),qr[i]=read(),qd[i]=read();
        len++;
        ans[i]=0;
        px[0][len]={qd[i],ql[i],ql[i]-qr[i],i,1};
        px[1][len]={qd[i],ql[i],ql[i]-qr[i],i,1};
        px[2][len]={qd[i],ql[i],ql[i]-qr[i],i,1};
        px[3][len]={qd[i],ql[i],ql[i]-qr[i],i,1};
        px[4][len]={qd[i],qr[i],ql[i]-qr[i],i,1};
        px[5][len]={qd[i],qr[i],ql[i]-qr[i],i,1};
        px[6][len]={qd[i],ql[i],qr[i],i,1};
        px[7][len]={qd[i],ql[i],qr[i],i,1};
    }
    sort(px[0]+1,px[0]+len+1,cmp00);
    int cnt000=0;
    for(int i=1;i<=len;i++){
        if(px[0][i].a!=px[0][i-1].a
        ||px[0][i].c!=px[0][i-1].c||i==1) cnt000=0;
        if(px[0][i].q==0) cmax(cnt000,px[0][i].d);
        else cmax(ans[px[0][i].d],cnt000);
    }
    sort(px[1]+1,px[1]+len+1,cmp00);
    int j=1;
    for(int i=1;i<=len;i++){
        if(px[1][i].c!=px[1][i-1].c&&i!=1){
            for(int k=j;k<i;k++) add(px[1][k].b,-1);
            j=i;
        }
        if(px[1][i].q==0) add(px[1][i].b,px[1][i].d);
        else cmax(ans[px[1][i].d],ask(px[1][i].b));
    }
    for(int k=j;k<=len;k++) add(px[1][k].b,-1);
    sort(px[2]+1,px[2]+len+1,cmp010);
    j=1;
    for(int i=1;i<=len;i++){
        if(px[2][i].a!=px[2][i-1].a&&i!=1){
            for(int k=j;k<i;k++) add(px[2][k].b,-1);
            j=i;
        }
        if(px[2][i].q==0) add(px[2][i].b,px[2][i].d);
        else cmax(ans[px[2][i].d],ask(px[2][i].b));
    }
    for(int k=j;k<=len;k++) add(px[2][k].b,-1);
    sort(px[3]+1,px[3]+len+1,cmp010);
    cdq011(1,len);
    sort(px[4]+1,px[4]+len+1,cmp10);
    j=1;
    for(int i=1;i<=len;i++){
        if(px[4][i].a!=px[4][i-1].a&&i!=1){
            for(int k=j;k<i;k++) add(px[4][k].b,-1);
            j=i;
        }
        if(px[4][i].q==0) add(px[4][i].b,px[4][i].d);
        else cmax(ans[px[4][i].d],ask(px[4][i].b));
    }
    for(int k=j;k<=len;k++) add(px[4][k].b,-1);
    sort(px[5]+1,px[5]+len+1,cmp10);
    cdq101(1,len);
    sort(px[6]+1,px[6]+len+1,cmp10);
    j=1;
    for(int i=1;i<=len;i++){
        if(px[6][i].a!=px[6][i-1].a&&i!=1){
            for(int k=j;k<i;k++) add(px[6][k].b,-1);
            j=i;
        }
        if(px[6][i].q==0) add(px[6][i].b,px[6][i].d);
        else cmax(ans[px[6][i].d],ask(px[6][i].b));
    }
    for(int k=j;k<=len;k++) add(px[6][k].b,-1);
    sort(px[7]+1,px[7]+len+1,cmp10);
    cdq111(1,len);
    long long tmp=0;
    long long res=0;
    for(int i=1;i<=q;i++) tmp^=1ll*i*ans[i],res+=1ll*i*ans[i];
    write(tmp,' '),write(res,'\n');
    // cout<<accumulate(C,C+(M<<1),0)<<endl;
    
    return;
}
string RdFile="tmp";
bool en_memory;
 
signed main(){
    bg_clock=chrono::high_resolution_clock::now();
// #ifdef ONLINE_JUDGE
    // freopen((RdFile+"2.in").c_str(),"r",stdin);
    // freopen((RdFile+"2.out").c_str(),"w",stdout);
// #endif
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    pp=pbuf;
    Case=read();
    while(Case--) Main();
    en_clock=chrono::high_resolution_clock::now();
    auto duration_clock=chrono::duration_cast<chrono::microseconds>(en_clock-bg_clock);
    double duration_count=duration_clock.count()*0.001;
    double memory_used=(&en_memory-&bg_memory)/1024.0/1024;
    // cerr<<"Time:"<<duration_count<<"ms"<<endl;
    // cerr<<"Memory: "<<memory_used<<"MB"<<endl;
    return fwrite(pbuf,1,pp-pbuf,stdout),0;
}