#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int N = 2e5 + 5;

struct node {
    int len, link;
    int nxt[26];
} st[N << 1];
int tot, last, ed[N << 1], mx[N << 1], mn[N << 1];
vector<int> adj[N << 1];
void sam_init() {
    tot = 1, last = 0;
    st[0].len = 0, st[0].link = -1;
}
void sam_extend(char c, int pos) {
    int cur = tot++;
    st[cur].len = st[last].len + 1;
    ed[cur] = pos;
    int p = last;
    while (p != -1 && !st[p].nxt[c - 'a']) {
        st[p].nxt[c - 'a'] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    }
    else {
        int q = st[p].nxt[c - 'a'];
        if (st[p].len + 1 == st[q].len) st[cur].link = q;
        else {
            int clo = tot++;
            st[clo].len = st[p].len + 1;
            st[clo].link = st[q].link;
            memcpy(st[clo].nxt, st[q].nxt, sizeof(st[q].nxt));
            while (p != -1 && st[p].nxt[c - 'a'] == q) {
                st[p].nxt[c - 'a'] = clo;  
                p = st[p].link;
            }
            st[q].link = st[cur].link = clo;
        }
    }
    last = cur;
}

int ans[N];
vector<pair<int, int>> upd[N], qry[N];
struct SegmentTree {
    struct node {
        int tag, mx;
    } tr[N << 2];
    #define lc cur << 1
    #define rc cur << 1 | 1
    void pushup(int cur) {
        tr[cur].mx = max(tr[lc].mx, tr[rc].mx);
    }
    void pushdown(int cur) {
        if (!tr[cur].tag) return;
        int x = tr[cur].tag;
        tr[cur].tag = 0;
        tr[lc].tag = max(tr[lc].tag, x);
        tr[rc].tag = max(tr[rc].tag, x);
        tr[lc].mx = max(tr[lc].mx, x);
        tr[rc].mx = max(tr[rc].mx, x);
    }
    void update(int cur, int l, int r, int a, int b, int x) {
        if (a > b or tr[cur].tag >= x) return;
        if (a <= l and r <= b) {
            tr[cur].mx = max(tr[cur].mx, x);
            tr[cur].tag = max(tr[cur].tag, x);
            return;
        }
        int mid = l + r >> 1;
        pushdown(cur);
        if (a <= mid) update(lc, l, mid, a, b, x);
        if (b > mid) update(rc, mid + 1, r, a, b, x);
        pushup(cur);
    }
    int query1(int cur, int l, int r, int p) {
        if (l == r) return tr[cur].mx;
        int mid = l + r >> 1;
        pushdown(cur);
        if (p <= mid) return query1(lc, l, mid, p);
        return query1(rc, mid + 1, r, p);
    }
    int query2(int cur, int l, int r, int a, int b) {
        if (a > r or b < l) return 0;
        if (a <= l and r <= b) return tr[cur].mx;
        int mid = l + r >> 1;
        pushdown(cur);
        return max(query2(lc, l, mid, a, b), query2(rc, mid + 1, r, a, b));
    }
} tr1, tr2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    sam_init();
    for (int i = 0; i < n; i++) sam_extend(s[i], i + 1);
    for (int i = 1, l, r; i <= q; i++) {
        cin >> l >> r;
        qry[l].push_back({r, i});
    }

    for (int i = 1; i < tot; i++) adj[st[i].link].push_back(i);
    auto dfs = [&](auto &dfs, int cur) -> void {
        mx[cur] = 0, mn[cur] = n + 1;
        if (ed[cur]) {
            mx[cur] = mn[cur] = ed[cur];
        }
        for (int i : adj[cur]) {
            dfs(dfs, i);
            mx[cur] = max(mx[cur], mx[i]);
            mn[cur] = min(mn[cur], mn[i]);
        }
        if (mn[cur] <= mx[cur] and st[cur].len) {
            upd[mn[cur]].push_back({mx[cur], st[cur].len});
        }
    };
    dfs(dfs, 0);

    for (int i = 1; i <= n; i++) {
        for (auto [mx, len] : upd[i]) {
            tr1.update(1, 1, n, 1, mx - len, len);
            tr2.update(1, 1, n, mx - len + 1, mx - len + 1, mx + 1);
        }
        for (auto [r, id] : qry[i]) {
            ans[id] = max(tr1.query1(1, 1, n, r), tr2.query2(1, 1, n, 1, r) - r);
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
}