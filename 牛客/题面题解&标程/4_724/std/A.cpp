#include<bits/stdc++.h>
using namespace std;

std::vector<std::vector<std::pair<int, int>>> decompose_kn(int n) {
    if (n <= 1) {
        return {};
    }

    std::vector<std::vector<std::pair<int, int>>> decomposition;
    auto make_canonical_edge = [](int u, int v) {
        return std::make_pair(std::min(u, v), std::max(u, v));
    };

    if (n % 2 != 0) {
        for (int r = 0; r < n; ++r) {
            std::vector<std::pair<int, int>> current_matching;
            std::vector<bool> matched(n, false);
            for (int u = 0; u < n; ++u) {
                if (matched[u]) continue;
                int v = (r - u + n) % n;
                if (u != v && !matched[v]) {
                    current_matching.push_back(make_canonical_edge(u, v));
                    matched[u] = true;
                    matched[v] = true;
                }
            }
            decomposition.push_back(current_matching);
        }
    } else {
        int center_vertex = n - 1;
        int num_circle_vertices = n - 1;
        for (int i = 0; i < num_circle_vertices; ++i) {
            std::vector<std::pair<int, int>> current_matching;
            current_matching.push_back(make_canonical_edge(i, center_vertex));

            for (int j = 1; j <= num_circle_vertices / 2; ++j) {
                int u = (i - j + num_circle_vertices) % num_circle_vertices;
                int v = (i + j) % num_circle_vertices;
                current_matching.push_back(make_canonical_edge(u, v));
            }
            decomposition.push_back(current_matching);
        }
    }

    return decomposition;
}

const int N=107;
int n;
string s[N];
vector<int> dice[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n;
	for (int i=0;i<n;++i) cin>>s[i];
	auto ret=decompose_kn(n);
	vector<int> lst;
	for (auto matching:ret){
		vector<int> vis(n,0);
		vector<int> perm1,perm2;
		for (auto e:matching) {
			vis[e.first]=vis[e.second]=1;
			if (s[e.first][e.second]=='1') perm1.push_back(e.first), perm1.push_back(e.second), perm2.push_back(e.second), perm2.push_back(e.first);
			else perm2.push_back(e.first), perm2.push_back(e.second), perm1.push_back(e.second), perm1.push_back(e.first);
		}
		for (int i=0;i<n;++i) if (!vis[i]) perm1.push_back(i), perm2.push_back(i);
		reverse(perm1.begin(), perm1.end());
		for (auto c:perm1) lst.push_back(c);
		for (auto c:perm2) lst.push_back(c);
	}
	for (int i=0;i<lst.size();++i) dice[lst[i]].push_back(i+1);
	for (int i=0;i<n;++i){
		cout<<dice[i].size()<<" ";
		for (auto c:dice[i]) cout<<c<<" ";
		cout<<endl;
	}
}