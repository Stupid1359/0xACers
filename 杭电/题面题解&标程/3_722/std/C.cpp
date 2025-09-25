#include <cstdio>
#include <algorithm>
#include <set>
#include <cassert>

#define odd(x) ((x) & 1)
#define even(x) (odd(x) ^ 1)

using namespace std;

const int N = 5e5 + 5;
const int C = N << 2;

int n, q;
char s[N];
set <int> pos[26];
int pre[N], suf[N];
int last[26], tot;
int mx[C], mxpos[C];

void setval(int u, int l, int r, int q, int v) {
	if (l == r) {
		mx[u] = v;
		mxpos[u] = q;
		return;
	}
	int mid = (l + r) >> 1;
	if (q <= mid)
		setval(u << 1, l, mid, q, v);
	else
		setval(u << 1 ^ 1, mid + 1, r, q, v);
	mx[u] = max(mx[u << 1], mx[u << 1 ^ 1]);
	if (mx[u] == mx[u << 1])
		mxpos[u] = mxpos[u << 1];
	else
		mxpos[u] = mxpos[u << 1 ^ 1];
}

void updpos(int p) {
	setval(1, 1, n, p, p - pre[p]);
}

void updlast(int c) {
	if (last[c])
		tot--;
	last[c] = 0;
	if (pos[c].size())
		last[c] = *(--pos[c].end());
	if (last[c])
		tot++;
}

void qrymax(int &l, int &r) {
	r = mxpos[1];
	l = pre[r];
	for (int i = 0; i < 26; i++)
		if (last[i] && n + 1 - last[i] > r - l) {
			l = last[i];
			r = n + 1;
		}
}

int getansodd(int l, int r, int cnt) {
	fprintf(stderr, "odd %d %d %d\n", l, r, cnt);
	int len = r - l + 1;
	assert(odd(cnt));

	if (odd(len))
		return len;
	if (suf[l] <= r || pre[r] >= l)
		return len - 1;

	int i = l, j = r, ci = cnt, cj = cnt;
	while (i + 1 <= r && suf[i] > r)
		i++, ci--;
	while (j - 1 >= l && pre[j] < l)
		j--, cj--;

	int ans = 1;
	if (i < r) {
		assert(suf[i] <= r);
		if (odd(r - i) && odd(ci))
			ans = max(ans, r - i);
		if (pre[r] <= i)
			ci--;
		if (odd(r - i - 1) && odd(ci))
			ans = max(ans, r - i - 1);
	}

	if (l < j) {
		assert(pre[j] >= l);
		if (odd(j - l) && odd(cj))
			ans = max(ans, j - l);
		if (suf[l] >= j)
			cj--;
		if (odd(j - l - 1) && odd(cj))
			ans = max(ans, j - l - 1);
	}

	return ans;
}

int getanseven(int l, int r, int cnt) {
	fprintf(stderr, "even %d %d %d\n", l, r, cnt);
	int len = r - l + 1;
	assert(cnt & 1 ^ 1);
	assert(l == 1 && r == n);
	int ql, qr;
	qrymax(ql, qr);

	if (odd(qr - ql - 1) && odd(cnt - 1))
		return qr - ql - 1;

	int cl, cr;
	do {
		int i = ql + 1, j = qr - 1;
		int c = cnt - 1;
		if (pre[j] < i)
			c--;
		j--;
		while (i >= l) {
			if (odd(c))
				return j - i + 1;
			if (i == l)
				cl = c;
			i--;
			if (suf[i] > j)
				c++;
			if (pre[j] < i)
				c--;
			j--;
		}
	} while (0);

	do {
		int i = ql + 1, j = qr - 1;
		int c = cnt - 1;
		if (suf[i] > j)
			c--;
		i++;
		while (j <= r) {
			if (odd(c))
				return j - i + 1;
			if (j == r)
				cr = c;
			j++;
			if (pre[j] < i)
				c++;
			if (suf[i] > j)
				c--;
			i++;
		}
	} while (0);

	int d = qr - ql - 1;
	int lx = l, rx = l + d - 2;
	int ly = r - d + 2, ry = r;
	while (even(cl)) {
		rx++;
		if (pre[rx] < lx)
			cl++;
	}
	while (even(cr)) {
		ly--;
		if (suf[ly] > ry)
			cr++;
	}

	return max(
		getansodd(lx, rx, cl),
		getansodd(ly, ry, cr)
	);
}

int getans() {
	if (odd(tot))
		return getansodd(1, n, tot);
	return getanseven(1, n, tot);
}

int main() {
	scanf("%d%d", &n, &q);
	scanf("%s", s + 1);

	for (int i = 1; i <= n; i++)
		suf[i] = n + 1;
	for (int i = 1; i <= n; i++) {
		int c = s[i] - 'a';
		if (last[c])
			suf[last[c]] = i;
		pre[i] = last[c];
		updpos(i);
		if (!last[c])
			tot++;
		last[c] = i;
		pos[c].insert(i);
	}

	printf("%d\n", getans());
	while (q--) {
		int p;
		char o, c;
		scanf("%d %c", &p, &c);
		if (suf[p] <= n) {
			int s = suf[p];
			pre[s] = pre[p];
			updpos(s);
		}
		if (pre[p])
			suf[pre[p]] = suf[p];
		o = s[p] - 'a';
		pos[o].erase(p);
		updlast(o);

		s[p] = c;
		pre[p] = 0;
		suf[p] = n + 1;
		c -= 'a';
		auto it = pos[c].lower_bound(p);
		if (it != pos[c].end()) {
			suf[p] = *it;
			pre[*it] = p;
			updpos(*it);
		}
		if (it != pos[c].begin()) {
			it--;
			pre[p] = *it;
			suf[*it] = p;
		}
		pos[c].insert(p);
		updpos(p);
		updlast(c);
		printf("%d\n", getans());
	}
	return 0;
}