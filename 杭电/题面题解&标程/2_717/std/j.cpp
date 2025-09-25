#include <bits/stdc++.h>
#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
 
 
#ifdef _MSC_VER
#include <intrin.h>
#endif
 
#if __cplusplus >= 202002L
#include <bit>
#endif
 
namespace atcoder {
 
namespace internal {
 
#if __cplusplus >= 202002L
 
using std::bit_ceil;
 
#else
 
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}
 
#endif
 
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}
 
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}
 
}  // namespace internal
 
}  // namespace atcoder
 
 
namespace atcoder {
 
#if __cplusplus >= 201703L
 
template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");
 
#else
 
template <class S, S (*op)(S, S), S (*e)()> struct segtree {
 
#endif
 
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
 
    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
 
    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }
 
    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;
 
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
 
    S all_prod() const { return d[1]; }
 
    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
 
    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
 
  private:
    int _n, size, log;
    std::vector<S> d;
 
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};
 
}
using namespace std;
auto rng = mt19937(random_device()());
auto rngl = mt19937_64(random_device()());
typedef pair<long double, long double> node;
long double value = 40000, eps = 1e-5;
 
struct op_node {
    long double cur_val;
    int sqrt_cnt;
    array<node, 21> linear_ops;
    array<node, 21> sum_ops;
    long double sum_afterwards;
};
 
op_node e() {
    op_node ans;
    ans.cur_val = value;
    ans.sqrt_cnt = 0;
    ans.linear_ops[0] = {1, 0};
    ans.sum_ops[0] = {0, 0};
    ans.sum_afterwards = 0;
    return ans;
}
 
op_node op(op_node x, op_node y) {
    op_node ans;
    if (y.sqrt_cnt == 20) ans.cur_val = y.cur_val;
    else {
        ans.cur_val = x.cur_val;
        for (int i = 0; i <= y.sqrt_cnt; i ++) {
            if (i) ans.cur_val = sqrtl(ans.cur_val);
            ans.cur_val = ans.cur_val * y.linear_ops[i].first + y.linear_ops[i].second;
        }
    }
    ans.sqrt_cnt = min(20, x.sqrt_cnt + y.sqrt_cnt);
 
    auto [x1, y1] = x.linear_ops[x.sqrt_cnt];
    auto [x2, y2] = y.linear_ops[0];
 
    for (int i = 0; i < x.sqrt_cnt; i ++) 
        ans.linear_ops[i] = x.linear_ops[i];
 
    ans.linear_ops[x.sqrt_cnt] = {x1 * x2, y1 * x2 + y2};
 
    for (int i = 1; i <= y.sqrt_cnt; i ++) {
        if (x.sqrt_cnt + i <= 20) {
            ans.linear_ops[x.sqrt_cnt + i] = y.linear_ops[i];
        }
    }
 
    auto [a1, b1] = x.sum_ops[x.sqrt_cnt];
    auto [a2, b2] = y.sum_ops[0];
 
    for (int i = 0; i < x.sqrt_cnt; i ++) 
        ans.sum_ops[i] = x.sum_ops[i];
 
    ans.sum_ops[x.sqrt_cnt] = {a1 + a2 * x1, b1 + a2 * y1 + b2};
 
    for (int i = 1; i <= y.sqrt_cnt; i ++) {
        if (x.sqrt_cnt + i <= 20) {
            ans.sum_ops[x.sqrt_cnt + i] = y.sum_ops[i];
        }
    }
 
    ans.sum_afterwards = x.sqrt_cnt == 20 ? x.sum_afterwards : 0;
    auto v = x.cur_val;
 
    for (int i = 0; i <= min(19, y.sqrt_cnt); i ++) {
        if (x.sqrt_cnt + i >= 20)
            ans.sum_afterwards += v * y.sum_ops[i].first + y.sum_ops[i].second;
        v = v * y.linear_ops[i].first + y.linear_ops[i].second;
        v = sqrtl(v);
    }
    ans.sum_afterwards += y.sum_afterwards;
 
    return ans;
}
 
op_node e1(node x) {
    op_node ans;
    if (x.first < -eps) {
        ans.cur_val = sqrtl(value);
        ans.sqrt_cnt = 1;
        ans.linear_ops[0] = {1, 0};
        ans.linear_ops[1] = {1, 0};
        ans.sum_ops[0] = {0, 0};
        ans.sum_ops[1] = {1, 0};
        ans.sum_afterwards = 0;
    }
    else {
        ans.cur_val = value * x.first + x.second;
        ans.sqrt_cnt = 0;
        ans.linear_ops[0] = x;
        ans.sum_ops[0] = x;
        ans.sum_afterwards = 0;
    }
    return ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int n;
    cin >> n;
 
    vector<node> ops(n);
 
    for (int i = 0; i < n; i ++) {
        int t;
        cin >> t;
 
        if (t == 1)
            cin >> ops[i].first >> ops[i].second;
        else
            ops[i].first = -1, ops[i].second = -1;
    }
 
    vector<op_node> op_nodes(n);
    for (int i = 0; i < n; i ++)
        op_nodes[i] = e1(ops[i]);
    
    atcoder::segtree<op_node, op, e> seg(op_nodes);
    
    int q;
    cin >> q;
 
    cout << fixed << setprecision(15);
 
    while (q --) {
        int t;
        cin >> t;
 
        if (t == 1) {
            int l, r;
            long double ans = 0, val;
            
            cin >> l >> r >> val;
 
            auto res = seg.prod(l - 1, r);
 
            for (int i = 0; i <= min(19, res.sqrt_cnt); i ++) {
                if (i) val = sqrtl(val);
                ans += val * res.sum_ops[i].first + res.sum_ops[i].second;
                val = val * res.linear_ops[i].first + res.linear_ops[i].second;
            }
 
            ans += res.sum_afterwards;
            cout << (res.sqrt_cnt == 20 ? res.cur_val : val) << ' ' << ans << '\n';
        }
        else {
            int idx;
            cin >> idx;
            idx --;
 
            int opt;
            cin >> opt;
 
            node val = {-1, -1};
            if (opt == 1)
                cin >> val.first >> val.second;
 
            seg.set(idx, e1(val));
        }
    }
 
    return 0;
}
