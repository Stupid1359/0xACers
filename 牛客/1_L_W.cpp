#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 使用树状数组维护范围内的数字个数,sum[n]表示范围[1,n]中数字的个数
// 类似于求解 sum[i]<=n/2 中i的最大值
void solve()
{
    int n, q;
    cin >> n >> q;

    vector<ll> nums(n);
    for (auto &x : nums)
    {
        cin >> x;
    }

    vector<ll> vis = nums, cur = nums;
    vector<pair<int, int>> updates(q);
    for (auto &[idx, val] : updates)
    {
        cin >> idx >> val;
        idx--;
        cur[idx] += val;
        vis.emplace_back(cur[idx]);
    }

    // 离散化
    sort(vis.begin(), vis.end());
    vis.erase(unique(vis.begin(), vis.end()), vis.end());
    int k = vis.size();
    // 树状数组 存区块中数字的个数
    vector<int> tree(k + 1, 0);

    // 数值离散化后对应的下标
    auto getidx = [&](ll val) -> int
    {
        return lower_bound(vis.begin(), vis.end(), val) - vis.begin();
    };
    // 树状数组的add函数
    auto add = [&](int idx, int val) -> void
    {
        idx++; // 输入的idx从0开始
        while (idx <= k)
        {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    };
    // 树状数组的sum函数
    auto ans = [&](int rank) -> int
    {
        int res = 0, idx = 0;
        for (int i = 25; i >= 0; i--)
        {
            if ((idx | (1 << i)) <= k && res + tree[idx | (1 << i)] <= rank)
            {
                idx |= (1 << i);
                res += tree[idx];
            }
        }
        return res;
    };

    for (auto &x : nums)
    {
        add(getidx(x), 1);
    }

    for (auto &[idx, val] : updates)
    {
        add(getidx(nums[idx]), -1);
        nums[idx] += val;
        add(getidx(nums[idx]), 1);
        cout << ans(n - n / 2) << "\n";
    }
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
