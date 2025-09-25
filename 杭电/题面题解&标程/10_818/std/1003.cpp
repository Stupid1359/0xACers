#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mkp make_pair
#define eb emplace_back
#define mem(a,b) memset(a,b,sizeof(a))
#define mpy(a,b) memcpy(a,b,sizeof(b))
#define dbg(...) cerr<<"#"<<__LINE__<<": "<<__VA_ARGS__<<endl
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fio(s) Fi(s".in"),Fo(s".out")
#define SZ(S) (int)S.size()
#define mod 998244353
//#define mod 1000000007
#define inf 0x3f3f3f3f
#define linf 0x3f3f3f3f3f3f3f3f
using namespace std;

template<int P>
class mod_int{
    using Z=mod_int;
private:
    static int mo(int x){return x<0?x+P:x;}
public:
    int x;
    int val()const{return x;}
    mod_int():x(0){}
    template<class T>mod_int(const T&x_):x(x_>=0&&x_<P?static_cast<int>(x_):mo(static_cast<int>(x_%P))){}
    bool operator==(const Z&rhs)const{return x==rhs.x;}
    bool operator!=(const Z&rhs)const{return x!=rhs.x;}
    Z operator-()const{return Z(x?P-x:0);}
    Z pow(long long k)const{Z res=1,t=*this;while(k){if(k&1)res*=t;if(k>>=1)t*=t;}return res;}
    Z&operator++(){x<P-1?++x:x=0;return *this;}
    Z&operator--(){x?--x:x=P-1;return *this;}
    Z operator++(int){Z ret=x;x<P-1?++x:x=0;return ret;}
    Z operator--(int){Z ret=x;x?--x:x=P-1;return ret;}
    Z inv()const{return pow(P-2);}
    Z&operator+=(const Z&rhs){(x+=rhs.x)>=P&&(x-=P);return *this;}
    Z&operator-=(const Z&rhs){(x-=rhs.x)<0&&(x+=P);return *this;}
    Z&operator*=(const Z&rhs){x=1ULL*x*rhs.x%P;return *this;}
    Z&operator/=(const Z&rhs){return *this*=rhs.inv();}
#define setO(T,o) friend T operator o(const Z&lhs,const Z&rhs){Z res=lhs;return res o##=rhs;}
    setO(Z,+)setO(Z,-)setO(Z,*)setO(Z,/)
#undef setO
};
const int P = 998244353;
using Z = mod_int<P>;

ll qpow(ll x, ll k){
    ll ret = 1;
    while(k){
        if(k & 1) (ret *= x) %= mod;
        (x *= x) %= mod, k >>= 1;
    }
    return ret;
}

namespace Poly_space{
    Z inv2 = (P + 1) / 2;
    vector<int> rev;
    vector<Z> gg = {0, 1};
    Z rt = 3;
    void setroot(Z x){rt = x;}
    void dft(vector<Z> &a){
        int n = a.size();
        if((int)rev.size() != n){
            int k = __builtin_ctz(n) - 1; rev.resize(n);
            for(int i = 0; i < n; i++){rev[i] = rev[i >> 1] >> 1 | (i & 1 ? (1 << k) : 0);}
        }
        for(int i = 0; i < n; i++) if(i < rev[i]) swap(a[i], a[rev[i]]);
        if((int)gg.size() < n){
            int k = __builtin_ctz(gg.size()); gg.resize(n);
            while((1 << k) < n){
                Z e = rt.pow((P - 1) >> (k + 1));
                for(int i = (1 << (k - 1)); i < (1 << k); i++) gg[i << 1] = gg[i], gg[(i << 1) | 1] = gg[i] * e;
                k++;
            }
        }
        for(int mid = 1; mid < n; mid <<= 1) for(int i = 0; i < n; i += (mid << 1)) for(int j = 0; j < mid; j++){
            Z x = a[i + j], y = a[i + j + mid] * gg[mid + j];
            a[i + j] = x + y, a[i + j + mid] = x - y;
        }
    }
    void idft(vector<Z> &a){
        int n = a.size(); reverse(a.begin() + 1, a.end()), dft(a);
        Z inv = Z(1 - P) / Z(n); for(int i = 0; i < n; i++) a[i] *= inv;
    }
    struct Poly{
        vector<Z> a;
        Poly(){} Poly(const vector<Z> &x): a(x){} Poly(const initializer_list<Z> &x): a(x){}
        int size()const{return a.size();} void resize(int x){a.resize(x);}
        Z operator [](int ind)const{if(ind < 0 || ind >= size()) return 0; return a[ind];}
        Z&operator [](int ind){return a[ind];}
        Poly modxk(int k)const{k = min(k, size()); return Poly(vector<Z>(a.begin(), a.begin() + k));}
        Poly mulxk(int k)const{vector<Z> b = a; b.insert(b.begin(), k, 0); return b;}
        Poly divxk(int k)const{if(size() <= k) return Poly(); return Poly(vector<Z>(a.begin() + k, a.end()));}
        friend Poly operator + (const Poly &a, const Poly &b){
            vector<Z> ret(max(a.size(), b.size()));
            for(int i = 0; i < ret.size(); i++) ret[i] = a[i] + b[i];
            return Poly(ret);
        }
        friend Poly operator - (const Poly &a, const Poly &b){
            vector<Z> ret(max(a.size(), b.size()));
            for(int i = 0; i < ret.size(); i++) ret[i] = a[i] - b[i];
            return Poly(ret);
        }
        friend Poly operator * (const Poly &a, const Z &b){
            vector<Z> ret(a.size());
            for(int i = 0; i < ret.size(); i++) ret[i] = a[i] * b;
            return Poly(ret);
        }
        friend Poly operator * (Poly a, Poly b){
            if(a.size() == 0 || b.size() == 0) return Poly();
            int sz = 1, n = a.size() + b.size() - 1;
            while(sz < n) sz <<= 1;
            a.resize(sz), b.resize(sz), dft(a.a), dft(b.a);
            for(int i = 0; i < sz; i++) a.a[i] = a[i] * b[i];
            idft(a.a), a.resize(n); return a;
        }
        Poly inv(int deg)const{
            if(deg == 1) return Poly({a[0].pow(P - 2)});
            Poly res = inv((deg + 1) >> 1), tmp = *this;
            int sz = 1; while(sz < (deg << 1)) sz <<= 1;
            tmp = tmp.modxk(deg), tmp.resize(sz), res.resize(sz);
            dft(tmp.a), dft(res.a);
            for(int i = 0; i < sz; i++) res[i] = 2 * res[i] - res[i] * res[i] * tmp[i];
            idft(res.a), res.resize(deg);
            return res;
        }
        Poly derivative()const{
            if(size() == 1) return Poly();
            Poly ret(vector<Z>(size() - 1));
            for(int i = 1; i < size(); i++) ret.a[i - 1] = a[i] * i;
            return ret;
        }
        Poly integrate()const{
            Poly ret(vector<Z>(size() + 1));
            for(int i = 1; i < ret.size(); i++) ret.a[i] = a[i - 1] * Z(i).inv();
            return ret;
        }
        Poly ln(int deg){
            Poly res = derivative(), tmp = inv(deg);
            res = (res * tmp).integrate(), res.resize(deg);
            return res;
        }
        Poly exp(int deg){
            Poly ret(vector<Z>(1)); ret[0] = 1; int i = 1;
            while(i < deg) i <<= 1, ret = (ret * (Poly({1}) - ret.ln(i) + modxk(i))).modxk(i);
            return ret.modxk(deg);
        }
    };
}
using namespace Poly_space;

Z power(Z p,ll k){
    Z ans = 1;
    while(k){
        if(k % 2 == 1) ans *= p;
        p *= p;
        k /= 2;
    }
    return ans;
}
#define poly vector <Z>
void printpoly(poly &p){
    printf("poly:\n");
    rep(i,0,SZ(p) - 1) printf("%d ",p[i].val());
    printf("\n");
}
poly module(poly p,poly q){
    while(!q.empty() && q.back().val() == 0) q.pop_back();
    assert(!q.empty());
    int n = SZ(p) - 1,m = SZ(q) - 1;
    if(n < m) return p;
    assert(q[m].val());
    Z rr = Z(1) / q[m];
    Poly f,g;
    rep(i,0,n - m) f.a.eb(p[n - i] * rr);
    g.a.eb(1);
    rep(i,1,n - m) g.a.eb(q[m - i] * rr);
    g = g.inv(n - m + 1);
    f = f * g;
    poly c(n - m + 1);
    rep(i,0,n - m) c[n - m - i] = f.a[i].val();

    f.a.clear();g.a.clear();
    rep(i,0,m) f.a.eb(q[i]);
    rep(i,0,n - m) g.a.eb(c[i]);
    f = f * g;
    poly res(m + 1);
    rep(i,0,m - 1) res[i] = p[i] - f.a[i];
    return res;
}

poly conv(poly &p,poly &q){
    int n = SZ(p) - 1,m = SZ(q) - 1;
    Poly f,g;
    rep(i,0,n) f.a.eb(p[i]);
    rep(i,0,m) g.a.eb(q[i]);
    f = f * g;
    poly res(n + m + 1);
    rep(i,0,n + m) res[i] = f.a[i];
    return res;
}
int T,n,m,k;
int _A[1005][1005];
mt19937_64 rnd(0);

Z _cur[2005],cur[1005],nxt[1005],a[1005];
Z w[1005][2005];
int idx[1005];

int ins(int id){
    rep(i,1,n) _cur[i] = cur[i];
    rep(i,n + 1,2 * n + 1) _cur[i] = 0;
    _cur[n + 1 + id] = 1;
//    printf("try ins:\n");
//    rep(i,1,n) printf("%d ",cur[i].val());
    rep(i,1,n) a[i] = 0;
    rep(i,1,n){
        if(!_cur[i].val()) continue;
        if(!w[i][i].val()){
            rep(j,1,2 * n + 1) w[i][j] = _cur[j];
            idx[i] = id;
            return 1; 
        }
        Z cof = _cur[i] / w[i][i];
        a[i] = cof;
        rep(j,1,2 * n + 1) _cur[j] -= w[i][j] * cof;
    }
    return 0;
}

ull val[1005];
poly low[2005],high[2005];
map <ull,int> buc;
ull gethsh(poly &f){
//    printf("get hsh of:\n");
//    rep(i,0,k) printf("%d ",f[i].val());
//    printf("\n");
    ull msk = 0;
    rep(i,0,k) msk += f[i].val() * val[i];
//    printf("msk=%llu\n",msk);
    return msk;
}

void solve(){
    scanf("%d%d",&n,&m);
    rep(i,1,n){
        rep(j,1,n) scanf("%d",&_A[i][j]);
    }
//    cur[1] = 1;cur[2] = 2;
    rep(i,1,n) cur[i] = rnd() % mod;
    rep(i,1,n){
        rep(j,1,2 * n + 1) w[i][j] = 0;
        idx[i] = -1;
    }
    k = 0;
    while(ins(k)){
        rep(i,1,n){
            rep(j,1,n) nxt[i] += Z(_A[i][j]) * cur[j];
        }
        rep(i,1,n){
            cur[i] = nxt[i];
            nxt[i] = 0;
        }
        k++;
//        rep(i,1,n) printf("%d ",cur[i].val());
//        printf("\n");
    }
/*    printf("fin k=%d\n",k);
    rep(i,1,n) printf("%d ",idx[i]);
    printf("\n");
    rep(i,1,n) printf("%d ",a[i].val());
    printf("\n");*/
    poly f(k + 1);
    rep(i,0,k) f[i] = 0;
    f[k] = 1;
    rep(i,1,n){
        rep(j,0,k) f[j] -= w[i][n + 1 + j] * a[i];
    }
//    printf("get f=:\n");
//    printpoly(f);
    if(!k || !f[0].val()){
        printf("-1\n");
        return;
    }

    int B = max(1,(int)sqrt(m));
    low[0] = vector<Z>(k + 1);
    rep(i,1,k) low[0][i] = 0;
    low[1] = low[0];
    low[0][0] = 1;
    low[1][1] = 1;
    high[0] = low[0];
    rep(i,2,B){
        low[i] = conv(low[i - 1],low[1]);
        low[i] = module(low[i],f);
    }
    high[1] = low[B];
    rep(i,2,(m + B - 1) / B){
        high[i] = conv(high[i - 1],high[1]);
        high[i] = module(high[i],f);
    }
/*    rep(i,0,B){
        printf("low[%d]\n",i);
        printpoly(low[i]);
    }
    rep(i,0,B){
        printf("high[%d]\n",i);
        printpoly(high[i]);
    }*/

    rep(i,0,n) val[i] = rnd();
    buc.clear();
    rep(i,0,B - 1){
        ull msk = gethsh(low[i]);
        buc[msk] = i;
    }
    int res = m + 1;
    rep(i,1,(m + B - 1) / B){
        ull msk = gethsh(high[i]);
//        printf("tst %llu\n",msk);
        if(buc.find(msk) != buc.end()){
            res = i * B - buc[msk];
            break;
        }
    }
    if(res <= m) printf("%d\n",res);
    else printf("-1\n");
}

int main(){
    scanf("%d",&T);
    while(T--) solve();
  return 0;
}