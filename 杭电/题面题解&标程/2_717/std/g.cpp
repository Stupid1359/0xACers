#include <bits/stdc++.h>
using namespace std;
 
typedef array<int, 2> vec;
 
vec dir(vec x1, vec x2) {return {x2[0] - x1[0], x2[1] - x1[1]};}
long long cross(vec x1, vec x2) {return 1ll * x1[0] * x2[1] - 1ll * x1[1] * x2[0];}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t;
    cin >> t;
    cout << fixed << setprecision(15);
 
    long double pi = acosl(-1);
 
    while (t --) {
        int n;
        vec pt;
        cin >> n >> pt[0] >> pt[1];
 
        vector<vec> pts(n);
        for (auto &[a, b]: pts) cin >> a >> b;
 
        bool flg = true;
        for (int i = 0; i < n; i ++) {
            if (cross(dir(pts[i], pts[(i + 1) % n]), dir(pts[i], pt)) < 0) {
                flg = false;
                break;
            }
        }
 
        if (!flg) cout << 2 * pi << '\n';
        else {
            long long max_dis = 0;
            for (auto &[x, y]: pts)
                max_dis = max(max_dis, 1ll * (pt[0] - x) * (pt[0] - x) + 1ll * (pt[1] - y) * (pt[1] - y));
            
            vector<long double> angles;
            for (auto &[x, y]: pts)
                if (1ll * (pt[0] - x) * (pt[0] - x) + 1ll * (pt[1] - y) * (pt[1] - y) == max_dis)
                    angles.emplace_back(atan2l(y - pt[1], x - pt[0]));
            
            sort(angles.begin(), angles.end());
 
            long double res = 0;
 
            for (int i = 0; i < angles.size() - 1; i ++)
                res = max(res, angles[i + 1] - angles[i]);
            
            res = max(res, angles[0] - angles.back() + 2 * pi);
            cout << res << '\n';
        }
    }
 
    return 0;
}
