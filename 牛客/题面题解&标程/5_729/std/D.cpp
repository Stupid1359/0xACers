#include<bits/stdc++.h>
using namespace std;
vector<int> v[25];

int prime[1 << 21];
bool isPrime[1 << 21];
int cnt;

void Euler(int n) {
    for (int i = 2; i <= n; i++) {
        if (!isPrime[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++) {
            if (prime[j] * i > n) break;
            isPrime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
void init()
{
    v[2] = {0,2,1,3};
    for(int i = 3; i <= 20; i++){
        int x = (1 << (i - 1));
        int y = 0;
        for(int j = 0; j < x; j++){
            if(!isPrime[x + j]){
                y = j;
                break;
            }
        }
        int d = y^v[i - 1][(1 << (i - 1)) - 1];
        for(int j = 0; j < x; j++){
            v[i].push_back(v[i - 1][j] ^ d);
        }
        for(int j = 0; j < x; j++){
            v[i].push_back(v[i - 1][j] ^ v[i - 1][0] ^ x);
        }
    }
}
struct node{
    int id,fi;
};
int main(){
    Euler(1<<20);
    init();
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        if (n == 2) {
            cout << -1 << endl;
            continue;
        }
        if (n == 10) {
            cout << "8 3 1 2 0 7 5 6 4 9" << endl;
            continue;
        }
        int m = n - n % 4;
        vector<node> ans;
        int lst = 0;
        if (n % 4 == 1)lst = n - 1;
        if (n % 4 == 2)lst = n - 2;
        if (n % 4 == 3)lst = n - 3;
        for (int i = 2; i <= 20; i++) {
            if (!((1 << i) & m))continue;
            node nw;
            nw.id = i;

            int fi = m - (1 << i);
            if (lst != 0) {
                for (int j = fi; j < m; j++) {
                    if (!isPrime[j ^ lst]) {
                        nw.fi = j;
                        break;
                    }
                }
            } else {
                nw.fi = fi ^ v[i][(1 << i) - 1];
            }
            lst = v[i][0] ^ v[i][(1 << i) - 1] ^ nw.fi;
            ans.push_back(nw);
            m = m - (1 << i);
        }

        vector<int> vec;
        for (auto [id, fi]: ans) {
            for (auto x: v[id]) {
                vec.push_back(x ^ v[id][0] ^ fi);
            }
        }

        if (n % 4 == 1) {
            vec.insert(vec.begin(), n - 1);
        } else if (n % 4 == 2) {
            vec.insert(vec.begin(), n - 2);
            for (int i = 1; i <= vec.size(); i++) {
                if (!isPrime[vec[i - 1] ^ (n - 1)] && (i == vec.size() || !isPrime[vec[i] ^ (n - 1)])) {
                    vec.insert(vec.begin() + i, n - 1);
                    break;
                }
            }
        } else if (n % 4 == 3) {
            vec.insert(vec.begin(), n - 3);
            vec.insert(vec.begin(), n - 1);
            vec.insert(vec.begin(), n - 2);
        }

        for (auto y: vec) {
            cout << y << ' ';
        }
        cout << endl;
    }
}

//0 2 1 3 4

//4 + 8 + 16
//0
//0 1 ?
//0 2 1    n%4 == 3
//0 2 1 3  n%4 == 4

//01100
//10011
//11111

//10110
//11011
//01101

//11000
//10101#include<bits/stdc++.h>
