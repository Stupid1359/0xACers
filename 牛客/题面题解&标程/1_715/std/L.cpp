#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        int n, q;
        cin >> n >> q;

        vector<long long> nums(n);
        for (auto &x : nums)
            cin >> x;

        vector<long long> vis = nums, cur = nums;

        vector<pair<int, int>> updates(q);
        for (auto &[idx, val] : updates)
        {
            cin >> idx >> val;
            idx--;

            cur[idx] += val;
            vis.emplace_back(cur[idx]);
        }

        sort(vis.begin(), vis.end());

        vis.erase(unique(vis.begin(), vis.end()), vis.end());
        int k = vis.size();

        vector<int> fen(k + 1, 0);

        auto getidx = [&](long long val) -> int
        {
            return lower_bound(vis.begin(), vis.end(), val) - vis.begin();
        };

        auto add = [&](int idx, int val) -> void
        {
            idx++;
            while (idx <= k)
            {
                fen[idx] += val;
                idx += idx & -idx;
            }
        };

        auto not_exceed = [&](int val) -> int
        {
            int res = 0, idx = 0;
            for (int i = 20; i >= 0; i--)
            {
                if ((idx | (1 << i)) <= k && res + fen[idx | (1 << i)] <= val)
                {
                    idx |= 1 << i;
                    res += fen[idx];
                }
            }
            return res;
        };

        for (auto &v : nums)
            add(getidx(v), 1);

        for (auto &[idx, val] : updates)
        {
            add(getidx(nums[idx]), -1);
            nums[idx] += val;
            add(getidx(nums[idx]), 1);
            cout << not_exceed(n - n / 2) << '\n';
        }
    }
    return 0;
}
