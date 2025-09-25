#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    int lim = min(4 * n, k);
    vector<int> a(n), cnt(n);
    int mx = 0;
    for (auto &x : a)
        cin >> x, mx = max(mx, x);
    queue<int> q;
    int now = 0, tot = 0;
    for (int i = 1; i < n; i++) q.push(i);
    while(lim--) {
        k--;
        int x = q.front(); q.pop();
        cnt[x]++, cnt[now]++;
        tot++;
        if (a[x] >= a[now] || tot == n)
            q.push(now), now = x, tot = 1;
        else q.push(x);
    }
    while(k) {
        int x = q.front();
        if (a[x] == mx) break;
        k--; q.pop();
        cnt[x]++, cnt[now]++;
        tot++;
        if (a[x] >= a[now] || tot == n)
            q.push(now), now = x, tot = 1;
        else q.push(x);
    }
    int round = k / (2 * n - 2);
    k -= (2 * n - 2) * round;
    for (int i = 0; i < n; i++)
        if (i != now && i != q.front()) cnt[i] += 2 * round;
        else cnt[i] += n * round;
    while(k--) {
        int x = q.front(); q.pop();
        cnt[x]++, cnt[now]++;
        tot++;
        if (a[x] >= a[now] || tot == n)
            q.push(now), now = x, tot = 1;
        else q.push(x);
    }
    for (int i = 1; i <= n; i++) cout << cnt[i - 1] << (i == n ? '\n' : ' ');
}

int main() {
    int T; cin >> T;
    while(T--) solve();
}