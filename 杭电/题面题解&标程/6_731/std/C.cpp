#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <int mod>
unsigned int down(unsigned int x)
{
    return x >= mod ? x - mod : x;
}
template <int mod>
struct Modint
{
    unsigned int x;
    Modint() = default;
    Modint(unsigned int x) : x(x) {}
    friend istream &operator>>(istream &in, Modint &a) { return in >> a.x; }
    friend ostream &operator<<(ostream &out, Modint a) { return out << a.x; }
    friend Modint operator+(Modint a, Modint b) { return down<mod>(a.x + b.x); }
    friend Modint operator-(Modint a, Modint b) { return down<mod>(a.x - b.x + mod); }
    friend Modint operator*(Modint a, Modint b) { return 1ULL * a.x * b.x % mod; }
    friend Modint operator/(Modint a, Modint b) { return a * ~b; }
    friend Modint operator^(Modint a, long long b)
    {
        Modint ans = 1;
        for (; b; b >>= 1, a *= a)
            if (b & 1)
                ans *= a;
        return ans;
    }
    friend Modint operator~(Modint a) { return a ^ (mod - 2); }
    friend Modint operator-(Modint a) { return down<mod>(mod - a.x); }
    friend Modint &operator+=(Modint &a, Modint b) { return a = a + b; }
    friend Modint &operator-=(Modint &a, Modint b) { return a = a - b; }
    friend Modint &operator*=(Modint &a, Modint b) { return a = a * b; }
    friend Modint &operator/=(Modint &a, Modint b) { return a = a / b; }
    friend Modint &operator^=(Modint &a, long long b) { return a = a ^ b; }
    friend Modint &operator++(Modint &a) { return a += 1; }
    friend Modint operator++(Modint &a, int)
    {
        Modint x = a;
        a += 1;
        return x;
    }
    friend Modint &operator--(Modint &a) { return a -= 1; }
    friend Modint operator--(Modint &a, int)
    {
        Modint x = a;
        a -= 1;
        return x;
    }
    friend bool operator==(Modint a, Modint b) { return a.x == b.x; }
    friend bool operator!=(Modint a, Modint b) { return !(a == b); }
};
const int mod = 998244353;
typedef Modint<mod> mint;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    const int N = 5e5 + 1;
    vector<mint> inv(N), fac(N);
    vector<mint> sum1(N), sum2(N), sum3(N);    
    fac[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = mint(1) / i;
        fac[i] = fac[i - 1] * i;
        sum1[i] = sum1[i - 1] + inv[i];
        sum2[i] = sum2[i - 1] + sum1[i - 1] * inv[i];
        sum3[i] = sum3[i - 1] + sum2[i - 1] * inv[i];
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        auto ans = sum1[n] + sum2[n] * 6 + sum3[n] * 6;
        ans *= fac[n];
        cout << ans << '\n';
    }
}