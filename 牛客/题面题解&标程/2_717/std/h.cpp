#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t;
    cin >> t;
    while (t --) {
        int n, m;
        cin >> n >> m;
    
        vector<vector<int>> path(n), rev_path(n);
        vector<long long> ws;
        vector<int> us, vs, ts;
    
        for (int i = 0; i < m; i ++) {
            int u, v, t;
            long long w;
 
            cin >> u >> v >> w >> t;
            u --, v --;
            us.emplace_back(u);
            vs.emplace_back(v);
            ws.emplace_back(w);
            ts.emplace_back(t);
            path[u].emplace_back(i);
            rev_path[v].emplace_back(i);
        }
    
        long long inf = 5e18;
        vector<long long> dis1(n, inf), dis2(n, inf);
        priority_queue<pair<long long, int>> pq;
    
        pq.push({0, 0}), dis1[0] = 0;
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            d = -d;
            if (dis1[u] == d) {
                for (auto &eid: path[u]) {
                    if (dis1[vs[eid]] > dis1[us[eid]] + ws[eid]) {
                        dis1[vs[eid]] = dis1[us[eid]] + ws[eid];
                        pq.push({-dis1[vs[eid]], vs[eid]});
                    }
                }
            }
        }
    
        pq.push({0, n - 1}), dis2[n - 1] = 0;
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            d = -d;
            if (dis2[u] == d) {
                for (auto &eid: rev_path[u]) {
                    if (dis2[us[eid]] > dis2[vs[eid]] + ws[eid]) {
                        dis2[us[eid]] = dis2[vs[eid]] + ws[eid];
                        pq.push({-dis2[us[eid]], us[eid]});
                    }
                }
            }
        }
    
        vector<pair<int, long long>> lines;
        for (int i = 0; i < m; i ++) {
            if (dis1[us[i]] != inf && dis2[vs[i]] != inf) {
                lines.emplace_back(-ts[i], dis1[us[i]] + dis2[vs[i]] + ws[i]);
            }
        }
 
        sort(lines.rbegin(), lines.rend());
    
        vector<pair<int, long long>> convex_hull;
        convex_hull.emplace_back(0, dis1[n - 1]);
 
        for (auto [k, y]: lines) {
            while (convex_hull.size() > 1) {
                auto [k1, y1] = convex_hull[convex_hull.size() - 2];
                auto [k2, y2] = convex_hull[convex_hull.size() - 1];
                if ((__int128_t)1 * (y1 - y2) * (k2 - k) <= (__int128_t)1 * (y2 - y) * (k1 - k2)) convex_hull.pop_back();
                else break;
            }
            convex_hull.emplace_back(k, y);
        }
 
        int l = convex_hull.size();
    
        auto f = [&] (int i, int t) -> long long {
            if (i < 0 || i >= l) return inf;
            return 1ll * t * convex_hull[i].first + convex_hull[i].second;
        };
    
        int q;
        cin >> q;
 
        while (q --) {
            int time;
            cin >> time;
    
            int left = 0, right = l - 2;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (f(mid, time) >= f(mid + 1, time)) left = mid + 1;
                else right = mid - 1;
            }
 
            cout << f(left, time) << '\n';
        }
    }
 
    return 0;
}
