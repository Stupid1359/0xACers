#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
namespace fstdlib {

using ll = long long;
int mod = 998244353, grt = 3;

class poly {
 public:
  std::vector<int> data;

  void out(void) {
    for (int i = 0; i < (int)data.size(); ++i) cerr<<data[i]<<' ';
    cerr<<endl;
  }

 public:
  poly(std::size_t len = std::size_t(0)) { data = std::vector<int>(len); }

  poly(const std::vector<int> &b) { data = b; }

  poly(const poly &b) { data = b.data; }

  void resize(std::size_t len, int val = 0) { data.resize(len, val); }

  std::size_t size(void) const { return data.size(); }

  void clear(void) { data.clear(); }
#if __cplusplus >= 201103L
  void shrink_to_fit(void) { data.shrink_to_fit(); }
#endif
  int &operator[](std::size_t b) { return data[b]; }

  const int &operator[](std::size_t b) const { return data[b]; }

  poly operator*(const poly &h) const;
  poly operator*=(const poly &h);
  poly operator*(const int &h) const;
  poly operator*=(const int &h);
  poly operator+(const poly &h) const;
  poly operator+=(const poly &h);
  poly operator-(const poly &h) const;
  poly operator-=(const poly &h);
  poly operator<<(const std::size_t &b) const;
  poly operator<<=(const std::size_t &b);
  poly operator>>(const std::size_t &b) const;
  poly operator>>=(const std::size_t &b);
  poly operator/(const int &h) const;
  poly operator/=(const int &h);
  poly operator==(const poly &h) const;
  poly operator!=(const poly &h) const;
  poly operator+(const int &h) const;
  poly operator+=(const int &h);
  poly inv(void) const;
  poly inv(const int &h) const;
  friend poly sqrt(const poly &h);
  friend poly log(const poly &h);
  friend poly exp(const poly &h);
};

int qpow(int a, int b, int p = mod) {
  int res = 1;
  while (b) {
    if (b & 1) res = (ll)res * a % p;
    a = (ll)a * a % p, b >>= 1;
  }
  return res;
}

std::vector<int> rev;

void dft_for_module(std::vector<int> &f, int n, int b) {
  static std::vector<int> w;
  w.resize(n);
  for (int i = 0; i < n; ++i)
    if (i < rev[i]) std::swap(f[i], f[rev[i]]);
  for (int i = 2; i <= n; i <<= 1) {
    w[0] = 1, w[1] = qpow(grt, (mod - 1) / i);
    if (b == -1) w[1] = qpow(w[1], mod - 2);
    for (int j = 2; j < i / 2; ++j) w[j] = (ll)w[j - 1] * w[1] % mod;
    for (int j = 0; j < n; j += i)
      for (int k = 0; k < i / 2; ++k) {
        int p = f[j + k], q = (ll)f[j + k + i / 2] * w[k] % mod;
        f[j + k] = (p + q) % mod, f[j + k + i / 2] = (p - q + mod) % mod;
      }
  }
}

poly poly::operator*(const poly &h) const {
  int N = 1;
  while (N < (int)(size() + h.size() - 1)) N <<= 1;
  std::vector<int> f(this->data), g(h.data);
  f.resize(N), g.resize(N);
  rev.resize(N);
  for (int i = 0; i < N; ++i)
    rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
  dft_for_module(f, N, 1), dft_for_module(g, N, 1);
  for (int i = 0; i < N; ++i) f[i] = (ll)f[i] * g[i] % mod;
  dft_for_module(f, N, -1), f.resize(size() + h.size() - 1);
  for (int i = 0, inv = qpow(N, mod - 2); i < (int)f.size(); ++i)
    f[i] = (ll)f[i] * inv % mod;
  return f;
}

poly poly::operator*=(const poly &h) { return *this = *this * h; }

poly poly::operator*(const int &h) const {
  std::vector<int> f(this->data);
  for (int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * h % mod;
  return f;
}

poly poly::operator*=(const int &h) {
  for (int i = 0; i < (int)size(); ++i) data[i] = (ll)data[i] * h % mod;
  return *this;
}

poly poly::operator+(const poly &h) const {
  std::vector<int> f(this->data);
  if (f.size() < h.size()) f.resize(h.size());
  for (int i = 0; i < (int)h.size(); ++i) f[i] = (f[i] + h[i]) % mod;
  return f;
}

poly poly::operator+=(const poly &h) {
  std::vector<int> &f = this->data;
  if (f.size() < h.size()) f.resize(h.size());
  for (int i = 0; i < (int)h.size(); ++i) f[i] = (f[i] + h[i]) % mod;
  return f;
}

poly poly::operator-(const poly &h) const {
  std::vector<int> f(this->data);
  if (f.size() < h.size()) f.resize(h.size());
  for (int i = 0; i < (int)h.size(); ++i) f[i] = (f[i] - h[i] + mod) % mod;
  return f;
}

poly poly::operator-=(const poly &h) {
  std::vector<int> &f = this->data;
  if (f.size() < h.size()) f.resize(h.size());
  for (int i = 0; i < (int)h.size(); ++i) f[i] = (f[i] - h[i] + mod) % mod;
  return f;
}

poly poly::operator<<(const std::size_t &b) const {
  std::vector<int> f(size() + b);
  for (int i = 0; i < (int)size(); ++i) f[i + b] = data[i];
  return f;
}

poly poly::operator<<=(const std::size_t &b) { return *this = (*this) << b; }

poly poly::operator>>(const std::size_t &b) const {
  std::vector<int> f(size() - b);
  for (int i = 0; i < (int)f.size(); ++i) f[i] = data[i + b];
  return f;
}

poly poly::operator>>=(const std::size_t &b) { return *this = (*this) >> b; }

poly poly::operator/(const int &h) const {
  std::vector<int> f(this->data);
  int inv = qpow(h, mod - 2);
  for (int i = 0; i < (int)f.size(); ++i) f[i] = (ll)f[i] * inv % mod;
  return f;
}

poly poly::operator/=(const int &h) {
  int inv = qpow(h, mod - 2);
  for (int i = 0; i < (int)data.size(); ++i) data[i] = (ll)data[i] * inv % mod;
  return *this;
}

poly poly::inv(void) const {
  int N = 1;
  while (N < (int)(size() + size() - 1)) N <<= 1;
  std::vector<int> f(N), g(N), d(this->data);
  d.resize(N), f[0] = qpow(d[0], mod - 2);
  for (int w = 2; w < N; w <<= 1) {
    for (int i = 0; i < w; ++i) g[i] = d[i];
    rev.resize(w << 1);
    for (int i = 0; i < w * 2; ++i)
      rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? w : 0);
    dft_for_module(f, w << 1, 1), dft_for_module(g, w << 1, 1);
    for (int i = 0; i < w * 2; ++i)
      f[i] = (ll)f[i] * (2 + mod - (ll)f[i] * g[i] % mod) % mod;
    dft_for_module(f, w << 1, -1);
    for (int i = 0, inv = qpow(w << 1, mod - 2); i < w; ++i)
      f[i] = (ll)f[i] * inv % mod;
    for (int i = w; i < w * 2; ++i) f[i] = 0;
  }
  f.resize(size());
  return f;
}

poly poly::operator==(const poly &h) const {
  if (size() != h.size()) return 0;
  for (int i = 0; i < (int)size(); ++i)
    if (data[i] != h[i]) return 0;
  return 1;
}

poly poly::operator!=(const poly &h) const {
  if (size() != h.size()) return 1;
  for (int i = 0; i < (int)size(); ++i)
    if (data[i] != h[i]) return 1;
  return 0;
}

poly poly::operator+(const int &h) const {
  poly f(this->data);
  f[0] = (f[0] + h) % mod;
  return f;
}

poly poly::operator+=(const int &h) { return *this = (*this) + h; }

poly poly::inv(const int &h) const {
  poly f(*this);
  f.resize(h);
  return f.inv();
}

}  // namespace fstdlib

#define poly fstdlib::poly

#pragma GCC optimize("Ofast,inline,unroll-loops")
char buf[1<<23],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	int x=0;char ch=0;
	while((ch<'0'||ch>'9'))ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch-'0'),ch=getchar();
	return x;
}
inline void write(int x,char tl=0){
	static int sta[10];
	int top=0;
	do{sta[top++]=x%10,x/=10;}while(x);
	while(top)putchar(sta[--top]+48);
	if(tl)putchar(tl);
}
const int mod=998244353,N=100009;
int n,mn,a[N],b[N],sz[N],fa[N];
vector<array<int,3> > g[N];
void dfs(int u,int f){
	sz[u]=1;fa[u]=f;
	for(auto p:g[u])if(p[0]!=f){
		int v=p[0],x=p[1],y=p[2];
		a[v]=p[2],b[v]=p[1];
		dfs(v,u);
		sz[u]+=sz[v];
	}
}
poly mul(vector<int> &vec,int l,int r){
	if(l>r)return vector<int>(1,1);
	if(l==r){
		poly s(vector<int>(vec[l]+1,0));
		s[0]=s[vec[l]]=1;
		return s;
	}
	int sum=0;
	for(int i=l;i<=r;i++)sum+=vec[i];
	array<int,2> mn={sum,0};
	for(int i=l,psum=0;i<=r;i++){
		psum+=vec[i];
		mn=min(mn,array<int,2>{max(psum,sum-psum),i});
	}
	return mul(vec,l,mn[1])*mul(vec,mn[1]+1,r);
}
signed main(){
	freopen("input.in","r",stdin);
	freopen("std.out","w",stdout);
	int cas=read();
	while(cas--){
		mn=n=read();
		for(int i=1;i<=n;i++)g[i].clear();
		for(int i=1;i<n;i++){
			int u=read(),v=read(),x=read(),y=read();
			g[u].push_back({v,x,y});
			g[v].push_back({u,y,x});
		}
		dfs(1,0);
		for(int i=2;i<=n;i++)a[i]=max(a[i],sz[i]-a[i]),b[i]=max(b[i],n-sz[i]-b[i]);
		for(int i=2;i<=n;i++)mn=min(mn,a[i]+b[i]);
		if(mn*2<n){cout<<"0\n";continue;}
		int ans=0;
		if(n%2==0){
			a[1]=n/2;
			bool fl=1;
			for(int i=1;i<=n;i++)if(a[i]+n-sz[i]-b[i]!=n/2){fl=0;break;}
			int res=1;
			for(int i=1;i<=n;i++){
				int son=0;
				for(auto j:g[i])if(j[0]!=fa[i])if(a[j[0]]*2-sz[j[0]]>=a[son]*2-sz[son])son=j[0];
				if(!son){
					if(a[i]!=1){fl=0;break;}
					else continue;
				}
				int x=0;
				for(auto j:g[i])if(j[0]!=son&&j[0]!=fa[i])x+=sz[j[0]]-a[j[0]];
				vector<int> tmp={};int cf=1;
				for(auto j:g[i])if(j[0]!=son&&j[0]!=fa[i]){
					int y=a[j[0]]-(sz[j[0]]-a[j[0]]);
					if(!y){(cf*=2)%=mod;continue;}
					tmp.push_back(y);
				}
				sort(tmp.begin(),tmp.end());
				auto t=mul(tmp,0,(int)tmp.size()-1);
				int s1=a[i]-1-x-a[son],s2=a[i]-1-x-sz[son]+a[son],f=0;
				if(s1<(int)t.size()&&s1>=0)(f+=t[s1]*cf)%=mod;
				if(s2<(int)t.size()&&s2>=0)(f+=t[s2]*cf)%=mod;
				if(a[i]*2>sz[i]){
					int s3=sz[i]-a[i]-1-x-a[son],s4=sz[i]-a[i]-1-x-sz[son]+a[son];
					if(s3<(int)t.size()&&s3>=0)(f+=t[s3]*cf)%=mod;
					if(s4<(int)t.size()&&s4>=0)(f+=t[s4]*cf)%=mod;
				}
				(res*=f)%=mod;
			}
			if(fl)(ans+=res*2)%=mod;
		}
		if(mn*2>n){
			a[1]=mn;
			bool fl=1;
			for(int i=1;i<=n;i++){
				if(a[i]+n-sz[i]-b[i]!=mn&&a[i]+b[i]!=mn){
					if(sz[i]-a[i]+b[i]==mn)a[i]=sz[i]-a[i];
					else {fl=0;break;}
				}
			}
			for(int i=1;i<=n;i++){
				int sum=0;
				for(auto j:g[i])if(j[0]!=fa[i])sum+=a[j[0]];
				if(sum+1!=a[i]&&sum!=a[i]){fl=0;break;}
			}
			(ans+=2*fl)%=mod;
		}
		write(ans,'\n');
	}
	return 0;
}
