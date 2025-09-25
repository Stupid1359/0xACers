#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 524292
#define ll long long
#define p 998244353
using namespace std;

inline int add(const int& x,const int& y){ return x+y>=p?x+y-p:x+y; }
inline int dec(const int& x,const int& y){ return x<y?x-y+p:x-y; }

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int siz;
int rev[N],rt[N],inv[N],fac[N],ifac[N];

void init(int n){
    int lim = 1;
    while(lim<=n) lim <<= 1,++siz;
    for(int i=0;i!=lim;++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<(siz-1));
    int w = power(3,(p-1)>>siz);
    fac[0] = ifac[0] = rt[lim>>1] = 1;
    for(int i=(lim>>1)+1;i!=lim;++i) rt[i] = (ll)rt[i-1]*w%p;
    for(int i=(lim>>1)-1;i;--i) rt[i] = rt[i<<1];

	for(int i=1;i<=n;++i) fac[i] = (ll)fac[i-1]*i%p;
	ifac[n] = power(fac[n],p-2);
	for(int i=n-1;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
    for(int i=1;i<=n;++i) inv[i] = (ll)fac[i-1]*ifac[i]%p;
}

inline void dft(int *f,int n){
    static unsigned long long a[N];
    int x,shift = siz-__builtin_ctz(n);
    for(int i=0;i!=n;++i) a[rev[i]>>shift] = f[i];
    for(int mid=1;mid!=n;mid<<=1)
    for(int j=0;j!=n;j+=(mid<<1))
    for(int k=0;k!=mid;++k){
        x = a[j|k|mid]*rt[mid|k]%p;
        a[j|k|mid] = a[j|k]+p-x;
        a[j|k] += x;
    }
    for(int i=0;i!=n;++i) f[i] = a[i]%p;
}

inline void idft(int *f,int n){
    reverse(f+1,f+n);
    dft(f,n);
    int x = p-((p-1)>>__builtin_ctz(n));
    for(int i=0;i!=n;++i) f[i] = (ll)f[i]*x%p;
}

inline int getlen(int n){
    return 1<<(32-__builtin_clz(n));
}

inline void inverse(const int *f,int n,int *r){
    static int g[N],h[N],st[30];
    memset(g,0,getlen(n<<1)<<2);
    int lim = 1,top = 0;
    while(n){
        st[++top] = n;
        n >>= 1;
    }
    g[0] = 1;
    while(top--){
        n = st[top+1];
        while(lim<=(n<<1)) lim <<= 1;
        memcpy(h,f,(n+1)<<2);
        memset(h+n+1,0,(lim-n)<<2);
        dft(g,lim),dft(h,lim);
        for(int i=0;i!=lim;++i) g[i] = g[i]*(2-(ll)g[i]*h[i]%p+p)%p;
        idft(g,lim);
        memset(g+n+1,0,(lim-n)<<2);
    }
    memcpy(r,g,(n+1)<<2);
}

inline void log(const int *f,int n,int *r){
    static int g[N],h[N];
    inverse(f,n,g);
    for(int i=0;i!=n;++i) h[i] = (ll)f[i+1]*(i+1)%p;
    h[n] = 0;
    int lim = getlen(n<<1);
    memset(g+n+1,0,(lim-n)<<2);
    memset(h+n+1,0,(lim-n)<<2);
    dft(g,lim),dft(h,lim);
    for(int i=0;i!=lim;++i) g[i] = (ll)g[i]*h[i]%p;
    idft(g,lim);
    for(int i=1;i<=n;++i) r[i] = (ll)g[i-1]*inv[i]%p;
    r[0] = 0;
}

inline void exp(const int *f,int n,int *r){
    static int g[N],h[N],st[30];
    memset(g,0,getlen(n<<1)<<2);
    int lim = 1,top = 0;
    while(n){
        st[++top] = n;
        n >>= 1;
    }
    g[0] = 1;
    while(top--){
        n = st[top+1];
        while(lim<=(n<<1)) lim <<= 1;
        memcpy(h,g,(n+1)<<2);
        memset(h+n+1,0,(lim-n)<<2);
        log(g,n,g);
        for(int i=0;i<=n;++i) g[i] = dec(f[i],g[i]);
        g[0] = add(g[0],1);
        dft(g,lim),dft(h,lim);
        for(int i=0;i!=lim;++i) g[i] = (ll)g[i]*h[i]%p;
        idft(g,lim);
        memset(g+n+1,0,(lim-n)<<2);
    }
    memcpy(r,g,(n+1)<<2);
}

int f[N],g[N];
int T,k,n;

int main(){
    scanf("%d%d",&T,&k);
    n = 200000;
	init((n+1)<<1);
	for(int i=0;i<=n;++i) g[i] = power(ifac[i],k+1);
	log(g,n,g);
	for(int i=1;i<=n;++i){
		int pw = 1,c = power(inv[i],k+1);
		for(int j=0;i*j<=n;++j){
			f[i*j] = (f[i*j] + (ll)g[j]*pw)%p;
			pw = (ll)pw*c%p;
		}
	}
	exp(f,n,f);
	for(int i=0;i<=n;++i) f[i] = (ll)f[i]*power(fac[i],k+1)%p;
	while(T--){
		scanf("%d",&n);
		printf("%d\n",f[n]);
	}
    return 0;   
}