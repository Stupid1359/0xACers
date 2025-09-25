#include <bits/stdc++.h>

inline int h(unsigned x) { return x == 0 ? 0 : 32 - __builtin_clz(x); }
inline int gbit(unsigned x, int k) { return ((x >> k - 1) & 1); }

void solve() {
	unsigned a, b, c; std::cin >> a >> b >> c;
	if (a == 0 && b == 0) 
		return (void)(std::cout << (c > 0 ? "-1\n" : "0\n"));
	std::vector<int> op;
	if (h(a) > h(b)) op.push_back(4), b ^= a;
	if (h(a) < h(b)) op.push_back(3), a ^= b;
	if (h(a) > h(c)) {
		while (h(b) > h(c)) {
			if (h(b) == h(a)) op.push_back(3), a ^= b;
			op.push_back(2), b >>= 1;
		}
	}
	if (h(a) < h(b)) op.push_back(3), a ^= b;
	while (h(a) < h(c)) {
		if (gbit(c, h(c) - h(a) + h(b)) != gbit(a, h(b))) op.push_back(3), a ^= b;
		// std::cerr << "a = " << a << '\n';
		op.push_back(1), a <<= 1;
	} while (h(b) > 0) {
		if (gbit(c, h(b)) != gbit(a, h(b))) op.push_back(3), a ^= b;
		// std::cerr << "b = " << b << '\n';
		op.push_back(2), b >>= 1;
	} op.push_back(4), b ^= a;
	std::cout << op.size() << '\n';
	for (int u : op) std::cout << u << ' ';
	std::cout << '\n';
}

int main() {
	int t; std::cin >> t; while (t--) solve(); return 0;
}