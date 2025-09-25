#include <bits/stdc++.h>
using ll = long long;
using namespace std;
int low(int x){return x&-x;}
const int Mod=998244353,gn=3,inv=332748118;
const int Nmx=100001,Kmx=17;
int ppc[1<<Kmx];
ll fpw(ll x,ll y){
	ll ans=1,push=x;
	while(y){
		if(y&1)ans=ans*push%Mod;
		push=push*push%Mod;
		y>>=1;
	}
	return ans;
}using ll = long long;
template <unsigned umod>
struct modint {
	static constexpr int mod = umod;
	unsigned v;
	modint() : v(0) {}
	template <class T, enable_if_t<is_integral<T>::value>* = nullptr>
	modint(T x) {
		x %= mod;
		if (x < 0) x += mod;
		v = x;
	}
	friend int raw(const modint& self) { return self.v; }
	friend ostream& operator<<(ostream& os, const modint& self) {
		return os << raw(self);
	}
	modint& operator+=(const modint& rhs) {
		v += rhs.v;
		if (v >= umod) v -= umod;
		return *this;
	}
	modint& operator-=(const modint& rhs) {
		v -= rhs.v;
		if (v >= umod) v += umod;
		return *this;
	}
	modint& operator*=(const modint& rhs) {
		v = static_cast<unsigned>(1ull * v * rhs.v % umod);
		return *this;
	}
	modint& operator/=(const modint& rhs) {
		static constexpr size_t ilim = 1 << 20;
		static modint inv[ilim + 10];
		static int sz = 0;
		assert(rhs.v);
		if (rhs.v > ilim) return *this *= qpow(rhs, mod - 2);
		if (!sz) inv[1] = sz = 1;
		while (sz < (int)rhs.v) {
			for (int i = sz + 1; i <= sz << 1; i++) inv[i] = -mod / i * inv[mod % i];
			sz <<= 1;
		}
		return *this *= inv[rhs.v];
	}
	template <class T>
	friend modint qpow(modint a, T b) {
		modint r = 1;
		for (; b; b >>= 1, a *= a)
			if (b & 1) r *= a;
		return r;
	}
	friend modint operator+(modint lhs, const modint& rhs) { return lhs += rhs; }
	friend modint operator-(modint lhs, const modint& rhs) { return lhs -= rhs; }
	friend modint operator*(modint lhs, const modint& rhs) { return lhs *= rhs; }
	friend modint operator/(modint lhs, const modint& rhs) { return lhs /= rhs; }
	friend bool operator==(const modint& lhs, const modint& rhs) {
		return lhs.v == rhs.v;
	}
	friend bool operator!=(const modint& lhs, const modint& rhs) {
		return lhs.v != rhs.v;
	}
};
typedef modint<998244353> mint;
int glim(const int& x) { return 1 << (32 - __builtin_clz(x - 1)); }
int bitctz(const int& x) { return __builtin_ctz(x); }
struct poly : vector<mint> {
	poly() {}
	explicit poly(int n) : vector<mint>(n) {}
	poly(const vector<mint>& vec) : vector<mint>(vec) {}
	poly(initializer_list<mint> il) : vector<mint>(il) {}
	mint operator()(const mint& x) const;
	poly& cut(int lim);
	void ntt(int op);
};
poly& poly::cut(int lim) {
	resize(lim);
	return *this;
}
void poly::ntt(int op) {
	static bool wns_flag = false;
	static vector<mint> wns;
	if (!wns_flag) {
		wns_flag = true;
		for (int j = 1; j <= 23; j++) {
			wns.push_back(qpow(mint(3), raw(mint(-1)) >> j));
		}
	}
	vector<mint>& a = *this;
	int n = a.size();
	for (int i = 1, r = 0; i < n; i++) {
		r ^= n - (1 << (bitctz(n) - bitctz(i) - 1));
		if (i < r) std::swap(a[i], a[r]);
	}
	vector<mint> w(n);
	for (int k = 1, len = 2; len <= n; k <<= 1, len <<= 1) {
		mint wn = wns[bitctz(k)];
		for (int i = raw(w[0] = 1); i < k; i++) w[i] = w[i - 1] * wn;
		for (int i = 0; i < n; i += len) {
			for (int j = 0; j < k; j++) {
				mint x = a[i + j], y = a[i + j + k] * w[j];
				a[i + j] = x + y, a[i + j + k] = x - y;
			}
		}
	}
	if (op == -1) {
		mint iz = mint(1) / n;
		for (int i = 0; i < n; i++) a[i] *= iz;
		reverse(a.begin() + 1, a.end());
	}
}
poly concalc(int n, vector<poly> vec,
	const function<mint(vector<mint>)>& func) {
		int lim = glim(n);
		int m = vec.size();
		for (auto& f : vec) f.resize(lim), f.ntt(1);
		vector<mint> tmp(m);
		poly ret(lim);
		for (int i = 0; i < lim; i++) {
			for (int j = 0; j < m; j++) tmp[j] = vec[j][i];
			ret[i] = func(tmp);
		}
		ret.ntt(-1);
		return ret;
	}
poly getInv(const poly& a, int lim) {
	poly b{1 / a[0]};
	for (int len = 2; len <= glim(lim); len <<= 1) {
		poly c = vector<mint>(a.begin(), a.begin() + min(len, (int)a.size()));
		b = concalc(len << 1, {b, c}, [](vector<mint> vec) {
			return vec[0] * (2 - vec[0] * vec[1]);
		}).cut(len);
	}
	return b.cut(lim);
}
poly operator+=(poly& a, const poly& b) {
	if (a.size() < b.size()) a.resize(b.size());
	for (size_t i = 0; i < b.size(); i++) a[i] += b[i];
	return a;
}
poly operator-=(poly& a, const poly& b) {
	if (a.size() < b.size()) a.resize(b.size());
	for (size_t i = 0; i < b.size(); i++) a[i] -= b[i];
	return a;
}
poly operator*=(poly& a, const mint& k) {
	if (k == 1) return a;
	for (size_t i = 0; i < a.size(); i++) a[i] *= k;
	return a;
}
poly operator/=(poly& a, const mint& k) { return a *= 1 / k; }
poly operator*(const poly& a, const poly& b) {
	if (a.empty() || b.empty()) return {};
	int rlen = a.size() + b.size() - 1;
	int len = glim(rlen);
	if (1ull * a.size() * b.size() <= 1ull * len * bitctz(len)) {
		poly ret(rlen);
		for (size_t i = 0; i < a.size(); i++)
			for (size_t j = 0; j < b.size(); j++) ret[i + j] += a[i] * b[j];
		return ret;
	} else {
		return concalc(len, {a, b},
			[](vector<mint> vec) { return vec[0] * vec[1]; })
		.cut(rlen);
	}
}
poly operator-(poly a, const poly& b) { return a -= b; }
poly operator*=(poly& a, const poly& b) { return a = a * b; }
poly operator+(poly a, const poly& b) { return a += b; }
poly operator*(poly a, const mint& k) { return a *= k; }
poly operator*(const mint& k, poly a) { return a *= k; }
poly operator/(poly a, const mint& k) { return a /= k; }

ll fact[Nmx+5],invf[Nmx+5];

void FWT(int n,ll a[]){
	for(int i=1;i<(1<<n);i<<=1)
		for(int j=0;j<(1<<n);j++)
			if(i&j)a[j]+=a[i^j];
	else j+=i-1;
	for(int i=0;i<(1<<n);i++)
		a[i]%=Mod;
}
void iFWT(int n,ll a[]){
	for(int i=1;i<(1<<n);i<<=1)
		for(int j=0;j<(1<<n);j++)
			if(i&j)a[j]-=a[i^j];
			else j+=i-1;
	for(int i=0;i<(1<<n);i++){
		a[i]%=Mod;
	}
}
int T,n,m,K,lns[1<<Kmx],rns[1<<Kmx],lt[1<<Kmx],v[1<<Kmx];
ll c[Kmx+1][1<<Kmx],f[2][Kmx+1][1<<Kmx];
void mulcv(int k,ll a[Kmx+1][1<<Kmx],ll res[Kmx+1][1<<Kmx]){
	for(int i=0;i<=k;i++)
		FWT(k,a[i]);
	memset(res,0,sizeof(ll)*(Kmx+1)<<Kmx);
	for(int i=0;i<=k;i++)
		for(int j=0;j<=i;j++){
			for(int S=0;S<(1<<k);S++)
				res[i][S]=(res[i][S]+a[i-j][S]*c[j][S])%Mod;
		}
	for(int i=0;i<=k;i++)
		iFWT(k,res[i]);
	for(int i=0;i<=k;i++)
		for(int S=0;S<(1<<k);S++){
			if(i!=ppc[S] || !v[S])
				res[i][S]=0;
		}
}
poly invG0(Nmx+1),G[Kmx+1];
int main(){
	fact[0]=1;
	for(int i=1;i<=Nmx;i++)
		fact[i]=fact[i-1]*1ll*i%Mod;
	invf[Nmx]=fpw(fact[Nmx],Mod-2);
	for(int i=Nmx-1;i>=0;i--){
		invf[i]=invf[i+1]*(i+1ll)%Mod;
		invG0[i]=(Mod-invf[i])*2;
	}
	invG0[0]=(3+invG0[0]);
	G[0]=getInv(invG0,Nmx);
	poly mul(Nmx+1);
	for(int i=0;i<=Nmx;i++)
		mul[i]=invf[i];
	mul*=G[0];
	for(int k=1;k<=Kmx;k++)
		G[k]=(G[k-1]*mul).cut(Nmx);
	for(int k=0;k<=Kmx;k++)
		for(int i=0;i<=Nmx;i++)
			G[k][i]*=fact[i];
	for(int i=1;i<(1<<Kmx);i++)
		ppc[i]=ppc[i>>1]+(i&1);
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		u--;v--;w--;
		if(u==v)continue;
		if(w==u) lns[1<<v]|=(1<<u);
		else rns[1<<u]|=(1<<v);
	}
	for(int S=1;S<(1<<K);S++){
		lns[S]=lns[S^low(S)] | lns[low(S)];
		rns[S]=rns[S^low(S)] | rns[low(S)];
		if(low(S)==S) lt[S]=lns[S] | rns[S];
		else lt[S]=lt[S^low(S)] | lt[low(S)];
		int cnt=2;
		if(lns[S] & S) cnt--;
		if(rns[S] & S) cnt--;
		if((lt[S] | S) == S) v[S]=1;
		else v[S]=0;
		c[ppc[S]][S]=cnt;
		f[1][ppc[S]][S]=v[S]*cnt;
	}
	f[1][0][0]=0;
	v[0]=1;
	for(int i=0;i<=K;i++)
		FWT(K,c[i]);
	mint ans=f[1][K][(1<<K)-1]*G[1][n-K];
	for(int i=2;i<=K;i++){
		int C=i%2,R=1-C;
		mulcv(K,f[R],f[C]);
		ans=ans+G[i][n-K]*f[C][K][(1<<K)-1];
	}
	cout<<ans<<endl;
	return 0;
}
