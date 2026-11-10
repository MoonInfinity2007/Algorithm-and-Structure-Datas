#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    std::map<char, std::vector<int64_t>> mp;
    for (int64_t i = 0; i < s1.size(); i++) mp[s1[i]].push_back(i);
    std::vector<int64_t> a, b;
    for (int64_t i = 0; i < s2.size(); i++) {
        if (mp.contains(s2[i])) {
            for (int64_t j = mp[s2[i]].size() - 1; j >= 0; j--) {
                a.push_back(mp[s2[i]][j]);
                b.push_back(i);
            }
        }
    }
    int64_t n = a.size();
    std::vector<int64_t> dp(n + 2);
    dp[0] = -1e9;
    for (int64_t i = 1; i < n + 2; i++) dp[i] = 1e9;
    auto bs = [&](int64_t x) -> int64_t{
        int64_t l = 0, r = n + 1;
        while (r - l > 1) {
            int64_t mid = (l + r) / 2;
            if (dp[mid] >= x) r = mid;
            else l = mid;
        }
        return r;
    };
    int64_t ans = 0;
    std::vector<int64_t> pos(n + 1, -1), prev(n);
    for (int64_t i = 0; i < n; i++) {
        int64_t j = bs(a[i]);
        if (dp[j - 1] < a[i] && a[i] < dp[j]) {
            dp[j] = a[i];
            ans = std::max(ans, j);
            pos[j] = i;
            prev[i] = pos[j - 1];
        }
    }
    std::cout << ans << "\n";
    std::vector<int64_t> res1, res2;
    int64_t p = pos[ans];
    while (p != -1) {
        res1.push_back(a[p]);
        res2.push_back(b[p]);
        p = prev[p];
    }
    std::reverse(res1.begin(), res1.end());
    std::reverse(res2.begin(), res2.end());
    for (auto u : res1) std::cout << u + 1 << " ";
    std::cout << "\n";
    for (auto u : res2) std::cout << u + 1 << " ";
}