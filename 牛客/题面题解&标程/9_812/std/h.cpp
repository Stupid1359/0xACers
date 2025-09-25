#include <bits/stdc++.h>
using namespace std;

int zeller (int y, int m, int d) {
    if (m < 3) {
        m += 12;
        y--;
    }
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307;
}

int main() {
    int n;
    scanf ("%d", &n);
    vector<pair<int, int>> submissions(n);
    for (int i = 0; i < n; i++) {
        int y, m, d, h, mi, s;
        scanf ("%d-%d-%d %d:%d:%d", &y, &m, &d, &h, &mi, &s);
        if (h >= 20) h -= 20;
        else h += 4, d -= 1;
        submissions[i] = {zeller(y, m, d), h};
    }
    const int INF = 0x3f3f3f3f;
    vector < vector <int> > f (n, vector <int> (3, -INF));
    int ans = 1;
    for (int i = n - 1; i >= 0; i--) {
        auto [day, hour] = submissions[i];
        for (int j = 0; j < 3; j++) {
            if (j == 2 && hour + 26 < 48) {
                continue;
            }
            auto it = lower_bound(submissions.begin() + i + 1, submissions.end(), make_pair(day + j + 1 - 2, 22));
            if (it == submissions.end() || it->first > day + j + 1) {
                f[i][j] = 1;
            } else {
                f[i][j] = max(f[i][j], f[it - submissions.begin()][day + j + 1 - it->first] + 1);
            }
            ans = max(ans, f[i][j]);
        }
    }
    cout << ans << ' ' << 1 << '\n';
}