#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
using point = pair<int, int>;

const i64 telePrice = pow(2, 34);

void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> H(n + 2, vector<int>(m + 2, 0));
    vector<point> teleporter;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> H[i][j];
        }
    }
    teleporter.push_back({1, 1});

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(i == 1 and j == 1)
                continue;
            if(H[i][j] > max({H[i + 1][j], H[i - 1][j], H[i][j - 1], H[i][j + 1]}))
                teleporter.push_back({i, j});
        }
    }

    i64 minRes = 0;
    
    sort(teleporter.begin(), teleporter.end(), 
        [&](const point& p1, const point& p2){
            return H[p1.first][p1.second] < H[p2.first][p2.second];
        });

    for(int i = 1; i < teleporter.size(); i++){
        auto [x1, y1] = teleporter[i];
        auto [x2, y2] = teleporter[i - 1];

        i64 weight = 114LL * abs(x1 - x2) + 5141LL * abs(y1 - y2) + 919810LL * abs(H[x1][y1] - H[x2][y2]);
        minRes += weight;
    }


    cout << minRes + 1LL * (teleporter.size() - 1) * telePrice << endl;
    
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while(T--){
        solve();
    }
}


