#include <bits/stdc++.h>
using namespace std;
 
int dp[2][2][2][3][2], ndp[2][2][2][3][2];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t;
    cin >> t;
 
    int mod = 998244353;
 
    auto add = [&] (int &x, int y) -> void {
        x += y;
        if (x >= mod) x -= mod;
    };
 
    while (t --) {
        string l, s;
        cin >> l >> s;
    
        int n = max(l.size(), s.size());
        l = string(n - l.size(), '0') + l;
        s = string(n - s.size(), '0') + s;
    
        for (int ab = 0; ab < 2; ab ++) {
            for (int bc = 0; bc < 2; bc ++) {
                for (int cs = 0; cs < 2; cs ++) {
                    for (int abc = 0; abc < 3; abc ++) {
                        for (int xorl = 0; xorl < 2; xorl ++) {
                            dp[ab][bc][cs][abc][xorl] = 0;
                        }
                    }
                }
            }
        }
        dp[0][0][0][1][0] = 1;
 
        for (int i = 0; i < n; i ++) {
            for (int ab = 0; ab < 2; ab ++) {
                for (int bc = 0; bc < 2; bc ++) {
                    for (int cs = 0; cs < 2; cs ++) {
                        for (int abc = 0; abc < 3; abc ++) {
                            for (int xorl = 0; xorl < 2; xorl ++) {
                                if (!dp[ab][bc][cs][abc][xorl]) continue;
                                for (int na = 0; na < 2; na ++) {
                                    for (int nb = 0; nb < 2; nb ++) {
                                        for (int nc = 0; nc < 2; nc ++) {
                                            if (!ab && na > nb) continue;
                                            if (!bc && nb > nc) continue;
                                            if (!cs && nc > s[i] - '0') continue;
                                            if (!xorl && (na ^ nb ^ nc) > l[i] - '0') continue;
    
                                            int nab = ab | (na < nb);
                                            int nbc = bc | (nb < nc);
                                            int ncs = cs | (nc < s[i] - '0');
                                            int nxorl = xorl | ((na ^ nb ^ nc) < l[i] - '0');
                                            int nabc = 2 * (abc - 1) + na + nb - nc;
                                            if (nabc < -1) continue;
                                            nabc = min(nabc + 1, 2);
                                            add(ndp[nab][nbc][ncs][nabc][nxorl], dp[ab][bc][cs][abc][xorl]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for (int ab = 0; ab < 2; ab ++) {
                for (int bc = 0; bc < 2; bc ++) {
                    for (int cs = 0; cs < 2; cs ++) {
                        for (int abc = 0; abc < 3; abc ++) {
                            for (int xorl = 0; xorl < 2; xorl ++) {
                                dp[ab][bc][cs][abc][xorl] = ndp[ab][bc][cs][abc][xorl];
                                ndp[ab][bc][cs][abc][xorl] = 0;
                            }
                        }
                    }
                }
            }
        }
    
        int ans = 0;
        for (int i = 0; i < 2; i ++) {
            for (int j = 0; j < 2; j ++) {
                for (int k = 0; k < 2; k ++) {
                    for (int l = 0; l < 2; l ++) {
                        add(ans, dp[i][j][k][2][l]);
                    }
                }
            }
        }
    
        for (int i = 0; i < 2; i ++) {
            for (int j = 0; j < 2; j ++) {
                add(ans, dp[1][1][i][2][j]);
            }
        }
    
        cout << ans << '\n';
    }
 
    return 0;
}
