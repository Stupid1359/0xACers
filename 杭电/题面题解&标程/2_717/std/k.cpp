#include <bits/stdc++.h>
using namespace std;
 
string s;
int n, k, lcp[10002], stats[10001], mod = 998244353;
int trie[2][50000002], cnt[50000002], pt = 0, total = 0;
 
void insert_words(int i) {
    int cur = 0;
    cnt[cur] += stats[i];
    for (int idx = i; idx < n; idx ++) {
        int c = s[idx] - '0';
        if (!trie[c][cur])
            trie[c][cur] = ++pt;
        cur = trie[c][cur];
        cnt[cur] += stats[idx];
    }
}
 
int find_kth(int val) {
    int cur = 0;
    int hsh = 0;
    while (true) {
        int node_cnt = cnt[cur];
        if (trie[0][cur]) node_cnt -= cnt[trie[0][cur]];
        if (trie[1][cur]) node_cnt -= cnt[trie[1][cur]];
        if (val < node_cnt) break;
        val -= node_cnt;
        hsh += hsh;
        if (hsh >= mod) hsh -= mod;
        if (trie[0][cur] && val < cnt[trie[0][cur]]) {
            cout << '0';
            cur = trie[0][cur];
        }
        else {
            if (trie[0][cur]) val -= cnt[trie[0][cur]];
            cout << '1';
            cur = trie[1][cur];
            hsh ++;
            if (hsh == mod) hsh = 0;
        }
    }
    return hsh;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    cin >> n >> k >> s;
 
    for (int i = n - 1; i >= 0; i --) {
		for (int j = i + 1; j < n; j ++) {
			if (s[j] == s[i]) lcp[j] = lcp[j + 1] + 1;
			else lcp[j] = 0;
		}
 
        for (int j = i + 1; j < n; j ++) {
            if (lcp[j] && j - i - k <= lcp[j]) {
                stats[j + max(0, j - i - 1 - k)] ++;
                stats[j + min(lcp[j], j - i)] --;
            }
        }
 
        for (int j = i + 1; j <= n; j ++)
            stats[j] += stats[j - 1];
 
        for (int j = n - 1; j >= i; j --) {
            stats[j] = (stats[j] > 0);
            stats[j] += stats[j + 1];
        }
 
        total += stats[i];
        insert_words(i);
        for (int j = i; j <= n; j ++)
            stats[j] = 0;
    }
 
    int q, last = 0;
    cin >> q;
 
    while (q --) {
        int k;
        cin >> k;
        k = (k + last - 1) % total;
        last = find_kth(k);
        cout << '\n';
    }
 
    return 0;
}
