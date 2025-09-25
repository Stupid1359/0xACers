#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
using ull = unsigned long long;
constexpr int N = 2E5, V = 64;
mt19937_64 rng(time(0));

ull rd[N + 1];

int f[V + 1][V + 1][V + 1];

int C(ll n, ll m) {
    if (n < 0 || m < 0) return 0;
    return ((n | m) == n) ? 1 : 0;
}

template<class T>
struct Tree {
    int n, k;
    vector<T> a;

    vector<int> rt, ls, rs;
    vector<ull> s;
    int idx {0};

    Tree() {}
    Tree(const vector<T> &init, int n_) {
        n = n_;
        k = __lg(n) + 2;
        assert(*max_element(init.begin() + 1, init.end()) <= n);
        assert(*min_element(init.begin() + 1, init.end()) >= 1);
        a = init;
        rt.resize((n + 1) * k + 1);
        ls.resize((n + 1) * k + 1);
        rs.resize((n + 1) * k + 1);
        s.resize((n + 1) * k + 1);

        for (int i = 1; i <= n; i++) {
            insert(rt[i - 1], rt[i], 1, n, a[i]);
        }
    }

    void insert(int x, int &y, int l, int r, T val) {
        y = ++idx;
        s[y] = s[x] ^ rd[val];
        ls[y] = ls[x];
        rs[y] = rs[x];
        if (l == r) return;
        int mid = l + r >> 1;
        if (val <= mid) {
            insert(ls[x], ls[y], l, mid, val);
        }
        else {
            insert(rs[x], rs[y], mid + 1, r, val);
        }
    }

    int query(int l, int r, int v) {
        return query(rt[l - 1], rt[r], 1, n, v);
    }

    int query(int x, int y, int l, int r, int L) {
        if (r < L) {
            return 0;
        }
        if (l == r) {
            if (s[y] ^ s[x]) {
                return l;
            }
            else {
                return 0;
            }
        }

        if (l >= L) {
            if (s[y] == s[x]) {
                return 0;
            }
        }

        int mid = l + r >> 1;

        int ans = query(ls[x], ls[y], l, mid, L);

        if (ans == 0) {
            ans = query(rs[x], rs[y], mid + 1, r, L);
        }

        return ans;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto c = a;
    sort(c.begin(), c.end()); 
    c.erase(unique(c.begin(), c.end()), c.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
    }

    Tree tree(a, n);

    const int mv = c.size() - 1;

    int q;
    cin >> q;

    int preans = 0;

    while (q--) {
        int L, R;
        ll k, v;
        cin >> L >> R >> k >> v;

        L ^= preans, R ^= preans, k ^= preans, v ^= preans;

        vector<int> idx;
        int val = 1;
        ll mx = 0;
        int cnt = 0;
        while (val <= mv && cnt < V) {
            int g = tree.query(L, R, val);
            if (g == 0) {
                break;
            }

            mx = max(mx, (ll)c[g]);
            cnt++;
            val = g + 1;
        }

        int ans = 0;
        int c = __builtin_popcountll(k);
        if (mx <= v) {
            if (k & 1) { // 有一个选奇数
                c--;

                for (int i = 0; i <= c; i++) {
                    ans ^= f[i][cnt][i] * C(c, i);
                }

                if ((v - cnt) % 2 == 0) {
                    ans = 0;
                }
            }
            else { // 全偶数
                ans = f[c][cnt][c];
            }
        }

        if (cnt > c) {
            ans = 0;
        }

        preans += ans;

        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int i = 1; i <= N; i++) {
        rd[i] = rng();
    }

    for (int s = 0; s <= V; s++) {
        f[s][0][0] = 1;
        for (int i = 1; i <= s; i++) {
            for (int j = 0; j <= s; j++) {
                for (int k = 1; j + k <= s; k++) {
                    f[s][i][j + k] ^= f[s][i - 1][j] * C(s - j - 1, k - 1);
                }
            }
        }
    }

    int tt = 1;
    cin >> tt;
    // cout << tt << endl;
    while (tt--) solve();
    return 0;
}