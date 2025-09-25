#include <bits/stdc++.h>

using s64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

/* 取 min */
template <class T>
inline void chmin(T &x, const T &y) {
    if (x > y) {
        x = y;
    }
}
/* 取 max */
template <class T>
inline void chmax(T &x, const T &y) {
    if (x < y) {
        x = y;
    }
}

/* ----- ----- ----- 正文 ----- ----- ----- */

const int N = 1000100;

int n, m;
std::string str;
int a[N];

struct Info {
    int len;
    int le0, rg0;
    int cnt1;

    int over;
    int st, ed;

    Info() {}
    Info(int x) {
        len = 1;
        le0 = rg0 = x == 0;
        cnt1 = x == 1;

        over = 0;
        st = ed = -1;
    }

    int answer() {
        if (cnt1 == 0) {
            return 0;
        }
        if (cnt1 == 1) {
            return rg0;
        }

        if (ed == rg0 + 1) {
            return st + 2 * (st - ed + 1);
        } else {
            return rg0;
        }
    }
};

Info operator + (Info lhs, Info rhs) {
    Info self;

    self.len = lhs.len + rhs.len;
    self.le0 = lhs.le0 == lhs.len ? lhs.len + rhs.le0 : lhs.le0;
    self.rg0 = rhs.rg0 == rhs.len ? rhs.len + lhs.rg0 : rhs.rg0;
    self.cnt1 = lhs.cnt1 + rhs.cnt1;

    /* 区间 1 的个数 < 2 */
    if (self.cnt1 < 2) {
        self.over = 0;
        self.st = self.ed = -1;
        return self;
    }

    /* 右区间全是 0：继承左区间信息 */
    if (rhs.cnt1 == 0) {
        self.over = lhs.over;
        self.st = lhs.st, self.ed = lhs.ed;
        return self;
    }
    /* 左区间全是 0：继承右区间信息 */
    if (lhs.cnt1 == 0) {
        self.over = rhs.over;
        self.st = rhs.st, self.ed = rhs.ed;
        return self;
    }

    /* 右区间已完结：继承右区间信息 */
    if (rhs.over) {
        self.over = 1;
        self.st = rhs.st, self.ed = rhs.ed;
        return self;
    }

    int ml = lhs.rg0 + rhs.le0;

    /* 左右区间均有一个 1 */
    if (lhs.cnt1 == 1 && rhs.cnt1 == 1) {
        self.over = 0;
        self.st = self.ed = ml;
        return self;
    }

    /* 左区间有一个 1，右区间有 >1 个 1 */
    if (lhs.cnt1 == 1) {
        if (ml == rhs.st + 1) {
            self.over = 0;
            self.st = ml, self.ed = rhs.ed;
        } else {
            self.over = 1;
            self.st = rhs.st, self.ed = rhs.ed;
        }
        return self;
    }
    /* 右区间有一个 1，左区间有 >1 个 1 */
    if (rhs.cnt1 == 1) {
        if (lhs.ed == ml + 1) {
            self.over = lhs.over;
            self.st = lhs.st, self.ed = ml;
        } else {
            self.over = 1;
            self.st = self.ed = ml;
        }
        return self;
    }

    /* 左右区间均有 >1 个 1 */
    if (lhs.ed == ml + 1 && ml == rhs.st + 1) {
        self.over = lhs.over;
        self.st = lhs.st, self.ed = rhs.ed;
    } else if (ml == rhs.st + 1) {
        self.over = 1;
        self.st = ml, self.ed = rhs.ed;
    } else {
        self.over = 1;
        self.st = rhs.st, self.ed = rhs.ed;
    }
    return self;    
}

namespace SGT {
    struct node {
        Info info;
    } t[N * 4];

    void upd(int p) {
        t[p].info = t[p * 2].info + t[p * 2 + 1].info;
    }

    void build(int p, int l, int r) {
        if (l == r) {
            t[p].info = Info(a[l]);
            return;
        }
        int mid = (l + r) >> 1;
        build(p * 2, l, mid), build(p * 2 + 1, mid + 1, r);
        upd(p);
    }

    void change(int p, int l, int r, int x, int y) {
        if (l == r) {
            t[p].info = Info(y);
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            change(p * 2, l, mid, x, y);
        } else {
            change(p * 2 + 1, mid + 1, r, x, y);
        }
        upd(p);
    }

    Info ask(int p, int l, int r, int s, int e) {
        if (s <= l && r <= e) {
            return t[p].info;
        }
        int mid = (l + r) >> 1;
        if (s <= mid && mid < e) {
            return ask(p * 2, l, mid, s, e) + ask(p * 2 + 1, mid + 1, r, s, e);
        }
        if (s <= mid) {
            return ask(p * 2, l, mid, s, e);
        } else {
            return ask(p * 2 + 1, mid + 1, r, s, e);
        }
    }
}

void work() {
    std::cin >> n >> m;
    std::cin >> str, str = " " + str;

    for (int i = 1; i <= n; i ++) {
        a[i] = str[i] - '0';
    }

    SGT::build(1, 1, n);

    while (m --) {
        int opt, x, y;
        std::cin >> opt;

        if (opt == 1) {
            std::cin >> x >> y;
            std::cout << SGT::ask(1, 1, n, x, y).answer() << '\n';
        } else {
            std::cin >> x;
            SGT::change(1, 1, n, x, a[x] ^= 1);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;

    while (T --) {
        work();
    }
    
    return 0;
}
