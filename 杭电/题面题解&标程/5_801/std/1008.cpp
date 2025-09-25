#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int C = 1000005;
const int BASE = 26;

struct ACAutomaton {
    struct Node {
        int son[BASE];
        int fail;
        int idx;
        int len;

        void init() {
            memset(son, 0, sizeof(son));
            idx = fail = 0;
        }
    } tr[C];

    int tot = 0;

    void init() {
        for (int i = 0; i <= tot; i++) tr[i].init();
        tot = 0;
    }

    void insert(const string &s, int idx) {
        int u = 0;
        for (int i = 0; i < (int)s.length(); i++) {
            int &son = tr[u].son[s[i] - 'a'];
            if (!son) son = ++tot, tr[son].init();
            u = son;
        }
        tr[u].idx = idx;
        tr[u].len = s.length();
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < BASE; i++)
            if (tr[0].son[i]) q.push(tr[0].son[i]);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < BASE; i++) {
                if (tr[u].son[i]) {
                    tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                    q.push(tr[u].son[i]);
                } else
                    tr[u].son[i] = tr[tr[u].fail].son[i];
            }
        }
    }

    vector<vector<int>> querypos(const string &t, int num_pattern) {
        vector<vector<int>> pos(num_pattern + 1);
        int u = 0, res = 0;
        for (int i = 0; i < (int)t.length(); i++) {
            u = tr[u].son[t[i] - 'a'];
            for (int j = u; j; j = tr[j].fail) {
                if (tr[j].idx) {
                    pos[tr[j].idx].push_back(i - tr[j].len + 1);
                    res++;
                }
            }
        }
        return pos;
    }

    int querycnt(const string &t) {
        int u = 0, res = 0;
        for (int i = 0; i < (int)t.length(); i++) {
            u = tr[u].son[t[i] - 'a'];
            for (int j = u; j; j = tr[j].fail) {
                if (tr[j].idx) {
                    res++;
                }
            }
        }
        return res;
    }

    vector<int> do_collect(int u = 0) {
        queue<int> q;
        vector<int> ret;
        q.push(u);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (tr[u].idx) {
                ret.push_back(tr[u].idx);
                continue;
            }
            for (int c = 0; c < BASE; c++) {
                if (tr[u].son[c]) q.push(tr[u].son[c]);
            }
        }
        return ret;
    }
} pre_aca, suf_aca;

std::string v_pre[C], v_suf[C];
int sum[C];

void solve() {
    pre_aca.init(), suf_aca.init();
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> v_pre[i], pre_aca.insert(v_pre[i], i);
    for (int i = 1; i <= m; i++) std::cin >> v_suf[i], std::reverse(v_suf[i].begin(), v_suf[i].end()), suf_aca.insert(v_suf[i], i);
    std::string S;
    std::cin >> S;
    for (int i = 0; i < S.length(); ++i) sum[i] = 0;
    auto v_pre_flag = pre_aca.do_collect(), v_suf_flag = suf_aca.do_collect();
    pre_aca.init(), suf_aca.init();
    for (auto i : v_pre_flag)
        pre_aca.insert(v_pre[i], i);
    for (auto i : v_suf_flag)
        reverse(v_suf[i].begin(), v_suf[i].end()), suf_aca.insert(v_suf[i], i);

    pre_aca.build(), suf_aca.build();

    auto result_pre = pre_aca.querypos(S, n);
    auto result_suf = suf_aca.querypos(S, m);

    for (size_t i = 0; i < v_suf_flag.size(); i++)
        for (auto pos : result_suf[v_suf_flag[i]])
            sum[pos]++;
    for (size_t i = S.length() - 1; i > 0; i--) sum[i - 1] += sum[i];
    long long ans = 0;

    for (size_t i = 0; i < v_pre_flag.size(); i++) {
        int pi = v_pre_flag[i];
        for (auto pos : result_pre[pi])
            ans += sum[pos];
        auto inter_cnt = suf_aca.querycnt(v_pre[pi].substr(0, v_pre[pi].length() - 1));
        ans -= inter_cnt * result_pre[pi].size();
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--) solve();
    return 0;
}