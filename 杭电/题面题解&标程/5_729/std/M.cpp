// #include <iostream>
// #include<vector>
// #include<set>
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 7;
const int inf = 0x3f3f3f3f;
int n, m, x, q;
vector<array<int, 3>> add[N], Q[N];
vector<pair<int, int>> upd[N], ask[N];
multiset<pair<int, int>> se[N];
vector<int> v;
vector<pair<int, int>> seg[N << 2];
vector<array<int, 4>> change[N << 2];

struct BIT
{
	struct node
	{
		int l, r;
		int mn, mx;
	} Tree[N << 2];

	void build(int k, int l, int r)
	{
		Tree[k].l = l;
		Tree[k].r = r;
		Tree[k].mn = inf;
		Tree[k].mx = 0;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
	}

	void update(int k, int pos)
	{
		if (Tree[k].l == Tree[k].r)
		{
			Tree[k].mx = Tree[k].mn = (se[pos].size() ? (*se[pos].rbegin()).first : 0);
			return;
		}
		int mid = (Tree[k].l + Tree[k].r) >> 1;
		if (pos <= mid)
			update(k << 1, pos);
		else
			update(k << 1 | 1, pos);
		Tree[k].mn = min(Tree[k << 1].mn, Tree[k << 1 | 1].mn);
		Tree[k].mx = max(Tree[k << 1].mx, Tree[k << 1 | 1].mx);
	}

	void update(int k, int pos, int v)
	{
		if (Tree[k].l == Tree[k].r)
		{
			Tree[k].mn = min(Tree[k].mn, v);
			Tree[k].mx = max(Tree[k].mx, v);
			return;
		}
		int mid = (Tree[k].l + Tree[k].r) >> 1;
		if (pos <= mid)
			update(k << 1, pos, v);
		else
			update(k << 1 | 1, pos, v);
		Tree[k].mn = min(Tree[k << 1].mn, Tree[k << 1 | 1].mn);
		Tree[k].mx = max(Tree[k << 1].mx, Tree[k << 1 | 1].mx);
	}

	int query(int k, int l, int r)
	{
		if (Tree[k].l >= l && Tree[k].r <= r)
		{
			return Tree[k].mn;
		}
		int mid = (Tree[k].l + Tree[k].r) >> 1;
		if (r <= mid)
			return query(k << 1, l, r);
		if (l > mid)
			return query(k << 1 | 1, l, r);
		return min(query(k << 1, l, r), query(k << 1 | 1, l, r));
	}

	int find(int k, int l, int r, int v)
	{
		if (Tree[k].mx < v)
			return x + 1;
		if (Tree[k].l == Tree[k].r)
			return Tree[k].l;
		int mid = (Tree[k].l + Tree[k].r) >> 1;
		int ans = x + 1;
		if (l <= mid)
			ans = find(k << 1, l, r, v);
		if (ans != x + 1)
			return ans;
		if (r > mid)
			ans = find(k << 1 | 1, l, r, v);
		return ans;
	}
} T1, T2, T3, T4;

void clear()
{
	for (int i = 1; i <= x; i++)
	{
		add[i].clear();
		Q[i].clear();
		upd[i].clear();
		ask[i].clear();
	}
	for (int i = 0; i < v.size(); i++)
	{
		seg[i].clear();
		change[i].clear();
	}
	v.clear();
}

int get(int x)
{
	return lower_bound(v.begin(), v.end(), x) - v.begin();
}

void solve()
{
	cin >> n >> m >> x >> q;
	for (int i = 1; i <= n; i++)
	{
		int t, l, r;
		cin >> t >> l >> r;
		add[r - l + 1].push_back({l, r, t});
		upd[r].push_back({l, t});
	}
	vector<int> T(m + 1, inf);
	vector<pair<int, int>> a(m + 1);
	for (int i = 1; i <= m; i++)
	{
		int l, r, k;
		cin >> l >> r >> k;
		Q[k].push_back({l, r, i});
		ask[r].push_back({l, i});
		a[i] = {l, r};
	}
	T1.build(1, 1, x);
	T2.build(1, 1, x);
	for (int k = x; k >= 1; k--)
	{
		for (auto [l, r, t] : add[k])
		{
			T1.update(1, l, t);
			T2.update(1, r, t);
		}
		for (auto [l, r, id] : Q[k])
		{
			T[id] = min(T[id], T1.query(1, l, r - k + 1));
			T[id] = min(T[id], T2.query(1, l + k - 1, r));
		}
	}
	T3.build(1, 1, x);
	for (int i = x; i >= 1; i--)
	{
		for (auto [pos, v] : upd[i])
			T3.update(1, pos, v);
		for (auto [l, id] : ask[i])
			T[id] = min(T[id], T3.query(1, 1, l));
	}
	for (int i = 1; i <= m; i++)
		v.push_back(T[i]);
	vector<array<int, 4>> b(q + 1);
	vector<int> ans(q + 1, inf);
	for (int i = 1; i <= q; i++)
	{
		cin >> b[i][0] >> b[i][1] >> b[i][2] >> b[i][3];
		v.push_back(b[i][0]);
		v.push_back(b[i][1]);
	}
	v.push_back(inf);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	T4.build(1, 1, x);
	int siz = v.size();
	for (int i = 1; i <= m; i++)
	{
		T[i] = get(T[i]);
		seg[T[i]].push_back({a[i].first, a[i].second});
	}
	for (int i = 1; i <= q; i++)
	{
		auto &[tl, tr, l, r] = b[i];
		tl = get(tl);
		tr = get(tr);
		change[tl].push_back({1, l, r, i});
		change[tr + 1].push_back({-1, l, r, i});
	}
	for (int i = 0; i < siz; i++)
	{
		for (auto [fl, l, r, id] : change[i])
		{
			if (fl == 1)
				se[l].insert({r, id});
			else
			{
				auto it = se[l].find({r, id});
				if (it != se[l].end())
					se[l].erase(it);
			}
			T4.update(1, l);
		}
		for (auto [l, r] : seg[i])
		{
			while (1)
			{
				int pos = T4.find(1, 1, l, r);
				if (pos == x + 1)
					break;
				int id = (*se[pos].rbegin()).second;
				ans[id] = v[i];
				se[pos].erase(*se[pos].rbegin());
				T4.update(1, pos);
			}
		}
	}
	for (int i = 1; i <= q; i++)
	{
		cout << (ans[i] == inf ? -1 : ans[i]) << "\n";
	}
	clear();
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		solve();
	return 0;
}

/*
1
1 1 5 1
1 1 2
2 3 1
1 5 2 3
*/
