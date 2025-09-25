#include <bits/stdc++.h>

void solve() {
	int n, a; std::string s;
	std::cin >> n >> a >> s;
	bool flag = false;
	for (int i = 0, lst = -1, c = 0; i < n; ++i) {
		c = (s[i] != lst ? 1 : c + 1), lst = s[i];
		if (c >= a + (lst == '0')) flag = true;
	}
	if (flag) std::cout << n << '\n';
	else std::cout << std::accumulate(s.begin(), s.end(), -'0' * n) << '\n';
}

int main() { int t; std::cin >> t; while (t--) solve(); return 0; }
