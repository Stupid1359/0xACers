#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

struct SuffixArray {
    int n;
    int k;
    string s;
    vector<int> sa, rk, oldrk, id, cnt, lc; 

    SuffixArray(const string &s) {
        SuffixArray::s = s;
        n = s.size() - 1;
        sa.resize(n + 1);
        rk.resize((n << 1) + 1);
        oldrk.resize((n << 1) + 1);
        id.resize(n + 1);
        cnt.resize(max(n + 1, 128));
        getsa(s);
        getlcp(s);
    }

    void getsa(const string &s) {
        int m = 127;
        for (int i = 1; i <= n; i++) ++cnt[rk[i] = s[i]];
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
        oldrk = rk;

        for (int p = 0, i = 1; i <= n; ++i) {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]]) {
                rk[sa[i]] = p;
            } 
            else {
                rk[sa[i]] = ++p;
            }
        }

        for (int w = 1; w < n; w <<= 1, m = n) {
            cnt.assign(max(n, m) + 1, 0);
            id = sa;
            for (int i = 1; i <= n; ++i) ++cnt[rk[id[i] + w]];
            for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i) sa[cnt[rk[id[i] + w]]--] = id[i];

            cnt.assign(max(n, m) + 1, 0);
            id = sa;
            for (int i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
            for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];

            oldrk = rk;
            for (int p = 0, i = 1; i <= n; ++i) {
                if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                    oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
                    rk[sa[i]] = p;
                }
                else {
                    rk[sa[i]] = ++p;
                }
            }
        }
    }

    void getlcp(const string &s) {
        lc.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            rk[sa[i]] = i;
        }

        int h = 0;
        lc[1] = 0;

        for (int i = 1; i <= n; i++) {
            int j = sa[rk[i] - 1];
            if (h > 0) h--;
            while (i + h <= n && j + h <= n) {
                if (s[i + h] != s[j + h]) break;
                h++;
            }
            lc[rk[i]] = h;
        }
    }

    bool find(const string &t) {
        bool ans = 0;
        int lo = 1, hi = n;

        auto check = [&](int idx, const string &t) {
            int p = 0;
            while (1) {
                if (s[idx] != t[p]) {
                    if (s[idx] < t[p]) return -1;
                    return 1;
                }
                idx++;
                p++;
                if (idx > n || p == t.size()) break;
            }
            if (p == t.size()) return 0;
            return 1;
        };

        while (lo <= hi && !ans) {
            int mid = lo + hi >> 1;
            int f = check(sa[mid], t);
            if (f == 0) {
               ans = 1;
            }
            else if (f == 1) {
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        return ans;
    }
};

void solve() {
	int n;
	cin >> n;
	ll ans = 0;
	vector<int> pre(n + 1);

	string s = " ";
	for (int i = 0; i < n; i++) {
		string t;
		cin >> t;
		s += t;
		s += '#';

		ll k = t.size();
		pre[i + 1] = pre[i] + int(t.size()) + 1;
	};

	const int k = s.size() - 1;

	SuffixArray sa(s);
	vector<int> pos(k + 1);
	int cnt = 0;
	for (int i = 1; i <= k; i++) {
		pos[i] = cnt;
		if (s[i] == '#') {
			cnt++;
		}

	}

	stack<pair<int, array<int, 50>>> stk;

	auto calc = [&](const array<int, 50>& a) {
		ll res = 0;
		int cnt = 0;
		for (int i = 0; i < 50; i++) {
			res += a[i];
			cnt += (a[i] != 0);
		}

		if (cnt < 2) {
			return 0ll;
		}

		return res;
	};

	auto work = [&](array<int, 50> &a, const array<int, 50> b) {
		for (int i = 0; i < 50; i++) {
			a[i] = max(a[i], b[i]);
		}
	};

	for (int i = 2; i <= k; i++) {
		int p1 = sa.sa[i - 1], p2 = sa.sa[i];
		if (s[p1] == '#' || s[p2] == '#') continue;


		int len = sa.lc[i];
		len = min(len, pre[pos[p1 + 1] + 1] - p1);
		len = min(len, pre[pos[p2 + 1] + 1] - p2);

		array<int, 50> a {};

		while (stk.size() && stk.top().first >= len) {
			auto [cur, b] = stk.top();
			stk.pop();
			work(a, b);
			ans = max(ans, cur * calc(a));
		}

		a[pos[p1]] = max(a[pos[p1]], p1 - pre[pos[p1]]);
		a[pos[p2]] = max(a[pos[p2]], p2 - pre[pos[p2]]);

		stk.push({len, a});
		ans = max(ans, len * calc(a));
	}

	while (stk.size() > 1) {
		auto b = stk.top().second;
		stk.pop();
		work(stk.top().second, b);

		auto [len, a] = stk.top();
		stk.pop();
		ans = max(ans, len * calc(a));
		stk.push({len, a});
	}

	if (stk.size()) {
		stk.pop();
	}

	for (int i = k; i >= 2; i--) {
		int p1 = sa.sa[i - 1], p2 = sa.sa[i];
		if (s[p1] == '#' || s[p2] == '#') continue;


		int len = sa.lc[i];
		len = min(len, pre[pos[p1 + 1] + 1] - p1);
		len = min(len, pre[pos[p2 + 1] + 1] - p2);

		array<int, 50> a {};

		while (stk.size() && stk.top().first >= len) {
			auto [cur, b] = stk.top();
			stk.pop();
			work(a, b);
			ans = max(ans, cur * calc(a));
		}

		a[pos[p1]] = max(a[pos[p1]], p1 - pre[pos[p1]]);
		a[pos[p2]] = max(a[pos[p2]], p2 - pre[pos[p2]]);

		stk.push({len, a});
		ans = max(ans, len * calc(a));
	}

	while (stk.size() > 1) {
		auto b = stk.top().second;
		stk.pop();
		work(stk.top().second, b);

		auto [len, a] = stk.top();
		stk.pop();
		ans = max(ans, len * calc(a));
		stk.push({len, a});
	}

	cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}