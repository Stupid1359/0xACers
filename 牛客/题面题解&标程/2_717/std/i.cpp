#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t;
    cin >> t;
 
    while (t --) {
        int x, y;
        cin >> x >> y;
 
        if ((x == 1) ^ (y == 1)) cout << -1 << '\n';
        else cout << 1 << '\n';
    }
 
    return 0;
}
