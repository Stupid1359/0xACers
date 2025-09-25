#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
template <unsigned M_> struct ModInt {
    static constexpr unsigned M = M_;
    unsigned x;
    constexpr ModInt() = default;
    constexpr ModInt(unsigned x_) : x(x_ % M) {}
    constexpr ModInt(unsigned long long x_) : x(x_ % M) {}
    constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
    constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
    constexpr ModInt operator++() { (*this) += 1; return *this; }
    constexpr ModInt operator--() { (*this) -= 1; return *this; }
    constexpr ModInt operator++(int) { const ModInt temp = *this; ++(*this); return temp; }
    constexpr ModInt operator--(int) { const ModInt temp = *this; --(*this); return temp; }
    ModInt &operator+=(const ModInt &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
    ModInt &operator-=(const ModInt &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
    ModInt &operator*=(const ModInt &a) { x = (static_cast<unsigned long long>(x) * a.x) % M; return *this; }
    ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
    ModInt pow(long long e) const {
        if (e < 0) return inv().pow(-e);
        ModInt a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
    }
    ModInt inv() const {
        unsigned a = M, b = x; int y = 0, z = 1;
        for (; b; ) { const unsigned q = a / b; const unsigned c = a - q * b; a = b; b = c; const int w = y - static_cast<int>(q) * z; y = z; z = w; }
        assert(a == 1U); return ModInt(y);
    }
    ModInt operator+() const { return *this; }
    ModInt operator-() const { ModInt a; a.x = x ? (M - x) : 0U; return a; }
    ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
    ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
    ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
    ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
    template <class T> friend ModInt operator+(T a, const ModInt &b) { return (ModInt(a) += b); }
    template <class T> friend ModInt operator-(T a, const ModInt &b) { return (ModInt(a) -= b); }
    template <class T> friend ModInt operator*(T a, const ModInt &b) { return (ModInt(a) *= b); }
    template <class T> friend ModInt operator/(T a, const ModInt &b) { return (ModInt(a) /= b); }
    explicit operator bool() const { return x; }
    bool operator==(const ModInt &a) const { return (x == a.x); }
    bool operator!=(const ModInt &a) const { return (x != a.x); }
    bool operator<(const ModInt &a) const { return (x < a.x); }
    bool operator>(const ModInt &a) const { return (x > a.x); }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
    friend std::istream &operator>>(std::istream &is, ModInt &a) { return is >> a.x; }
};
using Mint = ModInt<MOD>;
const Mint INV2 = (MOD + 1) / 2;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    const int W = 100;

    vector A(n + 1, vector<Mint>(W)), P(n + 1, vector<Mint>(W)), S(n + 1, vector<Mint>(W));

    A[1][1] = P[1][1] = S[1][1] = 1;

    auto add_shift = [&](vector<Mint> &dst, const vector<Mint> &src, int sh) {
        for (int k = 1; k + sh < W; k++) {
            if (src[k]) {
                dst[k + sh] += src[k];
            }
        }
    };

    for (int m = 2; m <= n; m++) {
        auto build = [&](int L, int R, vector<Mint> &AM, vector<Mint> &PM, vector<Mint> &SM) {
            const vector<Mint> &AL = A[L], &AR = A[R];
            const vector<Mint> &PL = P[L], &PR = P[R];
            const vector<Mint> &SL = S[L], &SR = S[R];

            AM.assign(W, 0);
            PM.assign(W, 0);
            SM.assign(W, 0);
            AM[1] = PM[1] = SM[1] = 1;
            add_shift(AM, AL, 1);
            add_shift(AM, AR, 1);

            for (int a = 1; a < W; a++) {
                for (int b = 1; a + b + 1 < W; b++) {
                    AM[a + b + 1] += SL[a] * PR[b];
                }
            }

            AM[3] -= 1;
            add_shift(PM, PL, 1);
            for (int k = 2; k + 2 < W; ++k) {
                PM[k + 2] += PR[k];
            }

            add_shift(SM, SR, 1);
            for (int k = 2; k + 2 < W; ++k) {
                SM[k + 2] += SL[k];
            }
        };

        if (m % 2 == 0) {
            int s = m / 2;
            build(s, s, A[m], P[m], S[m]);
        } else {
            int s = m / 2;
            vector<Mint> A1, P1, S1, A2, P2, S2;
            build(s, s + 1, A1, P1, S1);
            build(s + 1, s, A2, P2, S2);
            for (int k = 1; k < W; ++k) {
                A[m][k] += (A1[k] + A2[k]) * INV2;
                P[m][k] += (P1[k] + P2[k]) * INV2;
                S[m][k] += (S1[k] + S2[k]) * INV2;
            }
        }
    }

    for (int k = 1; k <= 2 * n; k++) {
        Mint ans = (k < W) ? A[n][k] : 0;
        cout << ans << '\n';
    }
    return 0;
}
