#include<bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;

mt19937_64 rnd(random_device{}());

const int mod = 998244353;
const int N = 3e5 + 5;
const int M = 3e5 + 5;

template<class Info, class Tag>
struct LazySegmentTree {
    int o, n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree() {}
    LazySegmentTree(int O, int N) : o(O), n(N) {
        info.resize(4 * n);
        tag.resize(4 * n);
    }
    LazySegmentTree(vector<Info>& Q, int O, int N) {
    	init(Q, O, N);
    }
    void init(vector<Info>& Q, int O, int N) {
    	o = O, n = N;
    	info.resize(4 * n);
        tag.resize(4 * n);
        auto build = [&](auto&& self, int p, int l, int r) -> void {
            if(l == r) {
                info[p] = Q[l];
                return;
            }
            int m = l + r >> 1;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m + 1, r);
            push_up(p);
        };
        build(build, 1, o, n);
	}
    void push_up(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag& t) {
        info[p].apply(t);
        tag[p].apply(t);
    }
    void push_down(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void update(int x, int p, int l, int r, const Info& y) {
        if(l == r) {
            info[p] = y;
            return;
        }
        push_down(p);
        int m = l + r >> 1;
        if(x <= m) update(x, 2 * p, l, m, y);
        else update(x, 2 * p + 1, m + 1, r, y);
        push_up(p);
    }
    void update(int x, const Info& y) {
        update(x, 1, o, n, y);
    }
    void update(int L, int R, int p, int l, int r, const Tag& t) {
    	if(L > R) return;
        if(L <= l && r <= R) {
            apply(p, t);
            return;
        }
        push_down(p);
        int m = l + r >> 1;
        if(L <= m) update(L, R, 2 * p, l, m, t);
        if(R > m) update(L, R, 2 * p + 1, m + 1, r, t);
        push_up(p);
    }
    void update(int L, int R, const Tag& t) {
        update(L, R, 1, o, n, t);
    }
    Info query(int L, int R, int p, int l, int r) {
    	if(L > R) return Info();
        if(L <= l && r <= R) {
            return info[p];
        }
        push_down(p);
        int m = l + r >> 1;
        if(R <= m) return query(L, R, 2 * p, l, m);
        if(L > m) return query(L, R, 2 * p + 1, m + 1, r);
        return query(L, R, 2 * p, l, m) + query(L, R, 2 * p + 1, m + 1, r);
    }
    Info query(int L, int R = -1) {
    	if(R == -1) R = L; 
        return query(L, R, 1, o, n);
    }
};

struct Tag {
    void apply(const Tag& t) {}
};

struct Info {
	i64 left = 0;
	i64 need = 0;
	i64 ans = 0;
	Info init() {
		Info res;
		int add = min(left, need);
		res.left = left - add;
		res.need = need - add;
		res.ans = add;
		return res;
	}
    void apply(const Tag& t) {}
};

Info operator + (const Info& a, const Info& b) {
    Info c = Info();
    i64 add = min(a.left, b.need);
    c.left = a.left + b.left - add;
    c.need = a.need + b.need - add;
    c.ans = a.ans + b.ans + add;
    return c;
}

struct Edge {
	int op;
	int x;
	int y;
	int nxtDay;
};

void solve(int tc)
{
	int n, m;
	cin >> n >> m;
	
	vector<Info> a(n + 1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i].left;
	}
	
	for(int i = 1; i <= n; i++) {
		cin >> a[i].need;
	}
	
	vector<Info> coef(n + 1);
	for(int i = 1; i <= n; i++) {
		coef[i] = a[i].init();
	}
	
	LazySegmentTree<Info, Tag> seg(coef, 1, n);
	
	vector<vector<Edge>> e(m + 1);
	vector<bool> vis(m + 1); 
	vector<vector<int>> angry(m + 1);
	for(int i = 1; i <= m; i++) {
		Edge edge;
		auto& [op, x, y, nxtDay] = edge;
		cin >> op >> x;
		nxtDay = i;
		if(op == 1 || op == 2) {
			cin >> y;
		}
		if(op == 3) {
			e[x].push_back(edge);
		} else {
			e[i - 1].push_back(edge);
		}
		if(op == 4) {
			vis[i] = 1;
			for(int j = 1; j <= x; j++) {
				int pos;
				cin >> pos;
				angry[i].push_back(pos);
			}
		}
	}
	
	vector<i64> res(m + 1, -1);
	auto dfs = [&](auto&& self, int cur) -> void {
		if(vis[cur]) {
			Info merge;
			int L = 1, R; 
			for(int i = 0; i < angry[cur].size(); i++) {
				int pos = angry[cur][i];
				R = pos - 1;
				merge = merge + seg.query(L, R);
				merge.left += a[pos].left;
				merge.ans += (merge.left + 1) / 2;
				merge.left /= 2;
				L = pos + 1;
			}
			merge = merge + seg.query(L, n);
			res[cur] = merge.ans;
		}
		for(auto& [op, x, y, nxtDay] : e[cur]) {
			Info pre;
			if(op <= 2) {
				pre = a[x];
				if(op == 1) {
					a[x].left = y;
				} else {
					a[x].need = y;
				}
				seg.update(x, a[x].init());
			}
			self(self, nxtDay);
			if(op <= 2) {
				a[x] = pre;
				seg.update(x, a[x].init());
			}
		}
	};
	dfs(dfs, 0);
	
	for(int i = 1; i <= m; i++) {
		if(res[i] != -1) {
			cout << res[i] << '\n';
		}
	}
}

signed main()
{ 
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;

	for(int tc = 1; tc <= T; tc++) {
	   solve(tc);
	}

	return 0;
}
