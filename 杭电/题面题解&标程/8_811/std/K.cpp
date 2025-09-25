#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ll long long

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

enum M_ST { OK, CFL, ADM, WG };

struct Team { int id, gid; string name; };
struct Msg { int u, v, su, sv; M_ST st; };
struct Rk {
    int id;
    int win;
    ll net;
    string name;

    bool operator<(const Rk& other) const {
        if (win != other.win) return win > other.win;
        if (net != other.net) return net > other.net;
        return name < other.name;
    }
};

const int MAX_T = 3001;

vector<Team> teams;
vector<Msg> msgs;
vector<int> nxt;
int true_id[MAX_T][MAX_T];

vector<ordered_set<Rk>> grp_rk; 
vector<Rk> t_data;

void upd_rk(const Msg& msg, int mult) {
    int gid = teams[msg.u].gid;
    
    grp_rk[gid].erase(t_data[msg.u]);
    grp_rk[gid].erase(t_data[msg.v]);

    ll net_u = (ll)msg.su - msg.sv;
    t_data[msg.u].net += net_u * mult;
    t_data[msg.v].net -= net_u * mult;

    if (msg.su > msg.sv) t_data[msg.u].win += mult;
    else t_data[msg.v].win += mult;

    grp_rk[gid].insert(t_data[msg.u]);
    grp_rk[gid].insert(t_data[msg.v]);
}

void solve() {
    int n, k;
    cin >> n >> k;
    int tot_t = 3 * n;

    teams.assign(tot_t + 1, Team());
    msgs.clear(); msgs.reserve(k);
    nxt.assign(k + 1, 0);
    
    int* last[MAX_T];
    for(int i = 0; i < MAX_T; ++i) {
        last[i] = new int[MAX_T]();
        for(int j = 0; j < MAX_T; ++j) true_id[i][j] = 0;
    }
    
    // 初始化数据结构
    grp_rk.assign(4, ordered_set<Rk>());
    t_data.assign(tot_t + 1, Rk());
    map<string, int> name2id;

    for (int i = 1; i <= tot_t; ++i) {
        teams[i].id = i;
        cin >> teams[i].name;
        name2id[teams[i].name] = i;
        for (int j = 0; j < 5; ++j) {
            string pname; cin >> pname;
            name2id[pname] = i;
        }
        cin >> teams[i].gid;
        
        t_data[i] = {i, 0, 0, teams[i].name};
        grp_rk[teams[i].gid].insert(t_data[i]);
    }

    for (int i = 1; i <= k; ++i) {
        int op; cin >> op;

        if (op == 1) {
            string tmp, s_nA, s_nB, s_sc;
            cin >> tmp >> tmp >> tmp >> s_nA;
            cin >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;
            cin >> s_nB >> tmp >> s_sc;

            string nA = s_nA.substr(0, s_nA.length() - 1);
            string nB = s_nB;
            string sc_s = s_sc.substr(0, s_sc.length() - 1);
            
            int u = name2id.at(nA), v = name2id.at(nB);
            int su, sv;
            sscanf(sc_s.c_str(), "%d-%d", &su, &sv);

            msgs.emplace_back(Msg{u, v, su, sv, OK});
            int cur = msgs.size();

            pair<int, int> p = minmax(u, v);
            int& last_idx = last[p.first][p.second];
            if(last_idx != 0) nxt[last_idx] = cur;
            last_idx = cur;

            if (teams[u].gid != teams[v].gid) {
                msgs.back().st = WG;
            } else {
                if (true_id[p.first][p.second] != 0) {
                    msgs.back().st = CFL;
                } else {
                    msgs.back().st = OK;
                    true_id[p.first][p.second] = cur;
                    upd_rk(msgs.back(), 1);
                }
            }
        } else if (op == 2) {
            int x; cin >> x;
            if (x > (int)msgs.size()) continue;

            Msg& msg = msgs[x-1];
            M_ST orig_st = msg.st;
            msg.st = ADM;

            if (orig_st == OK) {
                upd_rk(msg, -1);
                pair<int, int> p = minmax(msg.u, msg.v);
                true_id[p.first][p.second] = 0;

                int nxt_idx = nxt[x];
                while(nxt_idx != 0) {
                    Msg& cand = msgs[nxt_idx - 1];
                    if (cand.st == CFL) {
                        cand.st = OK;
                        true_id[p.first][p.second] = nxt_idx;
                        upd_rk(cand, 1);
                        break;
                    }
                    nxt_idx = nxt[nxt_idx];
                }
            }
        } else if (op == 3) {
            int x; cin >> x;
            int gid = teams[x].gid;
            const Rk& team_to_find = t_data[x];
            int better_teams_count = grp_rk[gid].order_of_key(team_to_find);
            cout << better_teams_count + 1 << "\n";
        }
    }

    for(int i = 0; i < MAX_T; ++i) delete[] last[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}