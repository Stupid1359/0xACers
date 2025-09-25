#pragma GCC optimize(3, "unroll-loops", "no-stack-protector")
#define atsum(l, r) accumulate(l, r, 0)
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int inf = 0x3f3f3f3f;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
template <typename T>
inline void chkmin(T &x, T y) {
    x = min(x, y);
}
template <typename T>
inline void chkmax(T &x, T y) {
    x = max(x, y);
}
namespace FastIO {
// ------------------------------
#define IN_HAS_NEG
#define OUT_HAS_NEG
#define CHK_EOF
#define DISABLE_MMAP
// ------------------------------
#if __cplusplus < 201400
#error Please use C++14 or higher.
#endif
#if __cplusplus > 201700
#define INLINE_V inline
#else
#define INLINE_V
#endif
#if (defined(LOCAL) || defined(_WIN32)) && !defined(DISABLE_MMAP)
#define DISABLE_MMAP
#endif
#ifndef DISABLE_MMAP
#include <sys/mman.h>
#endif
#ifdef LOCAL
inline char gc() { return getchar(); }
inline void pc(char c) { putchar(c); }
#else
#ifdef DISABLE_MMAP
INLINE_V constexpr int _READ_SIZE = 1 << 18;
INLINE_V static char _read_buffer[_READ_SIZE], *_read_ptr = nullptr,
                                               *_read_ptr_end = nullptr;
inline char gc() {
    if (__builtin_expect(_read_ptr == _read_ptr_end, false)) {
        _read_ptr = _read_buffer;
        _read_ptr_end =
            _read_buffer + fread(_read_buffer, 1, _READ_SIZE, stdin);
#ifdef CHK_EOF
        if (__builtin_expect(_read_ptr == _read_ptr_end, false)) return EOF;
#endif
    }
    return *_read_ptr++;
}
#else
INLINE_V static const char *_read_ptr =
    (const char *)mmap(nullptr, INT_MAX, 1, 2, 0, 0);
inline char gc() { return *_read_ptr++; }
#endif
INLINE_V constexpr int _WRITE_SIZE = 1 << 18;
INLINE_V static char _write_buffer[_WRITE_SIZE], *_write_ptr = _write_buffer;
inline void pc(char c) {
    *_write_ptr++ = c;
    if (__builtin_expect(_write_buffer + _WRITE_SIZE == _write_ptr, false)) {
        fwrite(_write_buffer, 1, _write_ptr - _write_buffer, stdout);
        _write_ptr = _write_buffer;
    }
}
INLINE_V struct _auto_flush {
    ~_auto_flush() {
        fwrite(_write_buffer, 1, _write_ptr - _write_buffer, stdout);
    }
} _auto_flush;
#endif
#ifdef CHK_EOF
inline bool _isdigit(char c) { return (c & 16) && c != EOF; }
inline bool _isgraph(char c) { return c > 32 && c != EOF; }
#else
inline bool _isdigit(char c) { return c & 16; }
inline bool _isgraph(char c) { return c > 32; }
#endif
template <class T>
INLINE_V constexpr bool _is_integer = numeric_limits<T>::is_integer;
template <class T>
INLINE_V constexpr bool _is_signed = numeric_limits<T>::is_signed;
template <class T>
INLINE_V constexpr bool _is_unsigned = _is_integer<T> && !_is_signed<T>;
template <>
INLINE_V constexpr bool _is_integer<__int128> = true;
template <>
INLINE_V constexpr bool _is_integer<__uint128_t> = true;
template <>
INLINE_V constexpr bool _is_signed<__int128> = true;
template <>
INLINE_V constexpr bool _is_unsigned<__uint128_t> = true;
#undef INLINE_V
inline void read(char &c) {
    do c = gc();
    while (!_isgraph(c));
}
inline void read_cstr(char *s) {
    char c = gc();
    while (!_isgraph(c)) c = gc();
    while (_isgraph(c)) *s++ = c, c = gc();
    *s = 0;
}
inline void read(string &s) {
    char c = gc();
    s.clear();
    while (!_isgraph(c)) c = gc();
    while (_isgraph(c)) s.push_back(c), c = gc();
}
#ifdef IN_HAS_NEG
template <class T, enable_if_t<_is_signed<T>, int> = 0>
inline void read(T &x) {
    char c = gc();
    bool f = true;
    x = 0;
    while (!_isdigit(c)) {
        if (c == 45) f = false;
        c = gc();
    }
    if (f)
        while (_isdigit(c)) x = x * 10 + (c & 15), c = gc();
    else
        while (_isdigit(c)) x = x * 10 - (c & 15), c = gc();
}
template <class T, enable_if_t<_is_unsigned<T>, int> = 0>
#else
template <class T, enable_if_t<_is_integer<T>, int> = 0>
#endif
inline void read(T &x) {
    char c = gc();
    while (!_isdigit(c)) c = gc();
    x = 0;
    while (_isdigit(c)) x = x * 10 + (c & 15), c = gc();
}
inline void write(char c) { pc(c); }
inline void write_cstr(const char *s) {
    while (*s) pc(*s++);
}
inline void write(const string &s) {
    for (char c : s) pc(c);
}
#ifdef OUT_HAS_NEG
template <class T, enable_if_t<_is_signed<T>, int> = 0>
inline void write(T x) {
    char buffer[numeric_limits<T>::digits10 + 1];
    int digits = 0;
    if (x >= 0) do
            buffer[digits++] = (x % 10) | 48, x /= 10;
        while (x);
    else {
        pc(45);
        do buffer[digits++] = -(x % 10) | 48, x /= 10;
        while (x);
    }
    while (digits) pc(buffer[--digits]);
}
template <class T, enable_if_t<_is_unsigned<T>, int> = 0>
#else
template <class T, enable_if_t<_is_integer<T>, int> = 0>
#endif
inline void write(T x) {
    char buffer[numeric_limits<T>::digits10 + 1];
    int digits = 0;
    do buffer[digits++] = (x % 10) | 48, x /= 10;
    while (x);
    while (digits) pc(buffer[--digits]);
}
template <int N>
struct _tuple_io_helper {
    template <class... T>
    static inline void _read(tuple<T...> &x) {
        _tuple_io_helper<N - 1>::_read(x), read(get<N - 1>(x));
    }
    template <class... T>
    static inline void _write(const tuple<T...> &x) {
        _tuple_io_helper<N - 1>::_write(x), pc(32), write(get<N - 1>(x));
    }
};
template <>
struct _tuple_io_helper<1> {
    template <class... T>
    static inline void _read(tuple<T...> &x) {
        read(get<0>(x));
    }
    template <class... T>
    static inline void _write(const tuple<T...> &x) {
        write(get<0>(x));
    }
};
template <class... T>
inline void read(tuple<T...> &x) {
    _tuple_io_helper<sizeof...(T)>::_read(x);
}
template <class... T>
inline void write(const tuple<T...> &x) {
    _tuple_io_helper<sizeof...(T)>::_write(x);
}
template <class T1, class T2>
inline void read(pair<T1, T2> &x) {
    read(x.first), read(x.second);
}
template <class T1, class T2>
inline void write(const pair<T1, T2> &x) {
    write(x.first), pc(32), write(x.second);
}
template <class T1, class... T2>
inline void read(T1 &x, T2 &...y) {
    read(x), read(y...);
}
template <class... T>
inline void read_cstr(char *x, T *...y) {
    read_cstr(x), read_cstr(y...);
}
template <class T1, class... T2>
inline void write(const T1 &x, const T2 &...y) {
    write(x), write(y...);
}
template <class... T>
inline void write_cstr(const char *x, const T *...y) {
    write_cstr(x), write_cstr(y...);
}
template <class T>
inline void print(const T &x) {
    write(x);
}
inline void print_cstr(const char *x) { write_cstr(x); }
template <class T1, class... T2>
inline void print(const T1 &x, const T2 &...y) {
    print(x), pc(32), print(y...);
}
template <class... T>
inline void print_cstr(const char *x, const T *...y) {
    print_cstr(x), pc(32), print_cstr(y...);
}
inline void println() { pc(10); }
inline void println_cstr() { pc(10); }
template <class... T>
inline void println(const T &...x) {
    print(x...), pc(10);
}
template <class... T>
inline void println_cstr(const T *...x) {
    print_cstr(x...), pc(10);
}
}  // namespace FastIO
using namespace FastIO;
template <typename T>
inline void clear(T &x) {
    T y;
    swap(x, y);
}
const int N = 415, G = 1 << 9, P = 28;

bool o1;
int z;
ll tab[N][P], stb[N];
int n, m, change[N];
// f <= 3^m * n
// f[i][j][k] 表示现在 合成 i star
ll f[G][P], g[G][P], h[G][P];
ll t[G][N];
bool o3;
#define low(s) ((s) & -(s))
ll ans = 0;
inline void cosume(int p, ll cot) {
    memset(t, 0, sizeof(t)), memcpy(h, f, sizeof(h));
    for (int j = 0; j < n; j++)
        for (int t = 0; t < (1 << n); t++)
            if (t >> j & 1)
                for (int l = 0; l <= n; l++) chkmax(h[t ^ (1 << j)][l], h[t][l] + tab[p][j + 1]);
    for (int j = p + 1; j < m; j++)
        for (int k = 0; k < n; k++) t[1 << k][j - p - 1] = tab[j][k + 1];
    for (int s = 0; s < (1 << n); s++)
        for (int i = 0; i <= min(m - p, z); i++)
            for (int j = 0; i + j <= z; j++) chkmax(t[s][i + j], t[low(s)][i] + t[s ^ low(s)][j]);
    for (int j = 0; j < (1 << n); j++)
        for (int l = 0; l <= n; l++) if (h[j][l] >= 0){
            int gt = cot - l;
            chkmin(gt, __builtin_popcount(j) * 2);
            if (gt >= 0 && (gt + z) / 2 >= __builtin_popcount(j)) 
                chkmax(ans, t[j][(gt + z) / 2 - __builtin_popcount(j)] + h[j][l]);
        }
}
int main() {
    int T;
    read(T);
    for (int _ = 1; _ <= T; _++) {
        ans = 0;
        memset(tab, 0, sizeof(tab)), memset(stb, 0, sizeof(stb)), memset(change, 0, sizeof(change));
        memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
        read(n, m);
        string cnt;
        read(cnt, z);
        for (char v : cnt) {
            for (int i = N - 3; ~i; i--) stb[i + 2] += stb[i];
            stb[0] += v - '0';
            for (int i = 0; i + 1 < N; i++) stb[i + 1] += stb[i] / 3, stb[i] %= 3;
        }
        for (int i = 0; i + 1 < N; i++) stb[i + 1] += stb[i] / 3, stb[i] %= 3;
        for (int i = 0; i < m; i++)
            for (int j = 1; j <= n; j++) read(tab[i][j]);
        memset(f, -0x3f, sizeof(f));
        f[(1 << n) - 1][0] = 0;
        ll res = 0;
        ll cur = 1;
        for (int i = m; i < N; i++)
            cur *= 3, chkmin(cur, 1000000ll), res += cur * stb[i];
        for (int i = 0; i < m; i++) {
            ll cot = 0, cur = 1;
            for (int j = i; j < N; j++) cot += cur * stb[j], cur *= 3, chkmin(cur, 1000000ll);
            if (cot <= 3 * n) cosume(i, cot);
            for (int j = 0; j <= 3 * n; j++) {
                if (j <= stb[i])
                    change[j] = 0;
                else
                    change[j] = (j - stb[i] + 2) / 3;
            }
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < (1 << n); j++) {
                    memcpy(g[j], f[j], sizeof(g[j]));
                    if ((j >> k) & 1) memset(f[j], -0x3f, sizeof(f[j]));
                }
                for (int j = 0; j < (1 << n); j++) {
                    if (j >> k & 1) {
                        for (int t = 0; t <= 3 * n; t++)
                            if (g[j][t] >= 0) {
                                chkmax(f[j][t + 2], g[j][t]);
                                chkmax(f[j ^ (1 << k)][t], g[j][t] + tab[i][k + 1]);
                            }
                    }
                }
            }
            for (int j = 0; j < (1 << n); j++)
                memcpy(g[j], f[j], sizeof(g[j])), memset(f[j], -0x3f, sizeof(f[j]));
            for (int j = 0; j < (1 << n); j++)
                for (int t = 0; t <= 3 * n; t++) chkmax(f[j][change[t]], g[j][t]);
            if (!cot) break;    
        }
        for (int t = 0; t <= min(3ll * n, res); t++) chkmax(ans, f[0][t]);
        println(ans);
    }
    // cerr << double(clock()) / CLOCKS_PER_SEC << endl;
    return 0;
}
