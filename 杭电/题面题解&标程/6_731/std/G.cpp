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

template <class Info, class Merge = plus<Info>>
struct SegmentTree
{
    const int n;
    const Merge merge;
    vector<Info> info;
    SegmentTree(int _n) : n(_n), merge(Merge()), info(4 * _n + 1) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size())
    {
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (l == r)
            {
                info[p] = init[l - 1];
                return;
            }
            int mid = l + r >> 1;
            build(p << 1, l, mid);
            build(p << 1 | 1, mid + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }
    void pull(int p)
    {
        info[p] = merge(info[p << 1], info[p << 1 | 1]);
    }
    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (l == r)
        {
            info[p] = v;
            return;
        }

        int mid = l + r >> 1;
        if (x <= mid)
            modify(p << 1, l, mid, x, v);
        else
            modify(p << 1 | 1, mid + 1, r, x, v);
        pull(p);
    }
    void modify(int p, const Info &v)
    {
        modify(1, 1, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l > y || r < x)
            return Info();
        if (l >= x && r <= y)
            return info[p];

        int mid = l + r >> 1;
        return merge(rangeQuery(p << 1, l, mid, x, y), rangeQuery(p << 1 | 1, mid + 1, r, x, y));
    }
    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 1, n, l, r);
    }
};

const int inf = 1e9;
array<array<int, 2>, 2> e{array<int, 2>{-inf, -inf}, array<int, 2>{-inf, -inf}};
struct Info {
    array<array<int, 2>, 2> m;
	Info() {
		m[0][0] = m[1][1] = 0;
		m[0][1] = m[1][0] = -inf;
	}
	Info(const array<array<int, 2>, 2> _m) : m(_m) {}
};

Info operator+(const Info &a, const Info &b) {
	Info res(e);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				res.m[i][j] = max(res.m[i][j], a.m[i][k] + b.m[k][j]);
			}
		}
	}
	return res;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

	int n, q;
	string s;
	cin >> n >> q >> s;
	set<int> pos;
	for (int i = 1; i <= n; i++) {
		if (s[i - 1] == 'R') {
			pos.insert(i);
		}
	}

	vector<Info> init(n);
	for (int i = 0; i < n; i++) {
		if (s[i] == 'R') {
			init[i].m = {array<int, 2>{0, -inf}, array<int, 2>{-inf, 1}};
		} else {
			init[i].m = {array<int, 2>{1, -inf}, array<int, 2>{0, 0}};
		}
	}
	SegmentTree<Info> tr(init);
	auto print = [&]() -> void {
		int res = 0;
		if (pos.empty()) res = 0;
		else {
			int mn = *pos.begin();
			if (n - mn + 1 == pos.size()) res = 0;
			else {
				auto tmp = tr.rangeQuery(mn, n).m;
				res = tmp[1][0];
			}
		}		
		cout << res << '\n';
	};

	while (q--) {
		int x;
		cin >> x;
		if (s[x - 1] == 'R') {
			s[x - 1] = 'L';
			pos.erase(x);
			tr.modify(x, Info({array<int, 2>{1, -inf}, array<int, 2>{0, 0}}));
		} else {
			s[x - 1] = 'R';
			pos.insert(x);
			tr.modify(x, Info({array<int, 2>{0, -inf}, array<int, 2>{-inf, 1}}));
		}
		print();
	}
}
/*
*/