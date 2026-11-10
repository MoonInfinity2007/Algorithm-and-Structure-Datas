#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int main() {
    int64_t n;
    std::cin >> n;
    int64_t dp[n + 4];
    int64_t p[n + 4];
    dp[0] = 0;
    dp[1] = 0;
    p[1] = 1;
    for (int64_t i = 2; i < n + 1; i++) {
        int64_t dp1 = dp[i - 1];
        int64_t dp2 = (i % 2 == 0) ? dp[i / 2] : 1e9;
        int64_t dp3 = (i % 3 == 0) ? dp[i / 3] : 1e9;
        if (dp1 <= dp2 && dp1 <= dp3) {
            dp[i] = dp1 + 1;
            p[i] = i - 1;
        } else if (dp2 <= dp3 && dp2 <= dp1) {
            dp[i] = dp2 + 1;
            p[i] = i/2;
        } else {
            dp[i] = dp3 + 1;
            p[i] = i/3;
        }
    }
    std::cout << dp[n] << "\n";
    int64_t prev = p[n];
    std::vector<int64_t> ans;
    ans.push_back(n);
    while (prev != 1) {
        ans.push_back(prev);
        prev = p[prev];
    }
    if (n != 1) ans.push_back(1);
    std::reverse(ans.begin(), ans.end());
    for (int64_t i = 0; i < ans.size(); i++) std::cout << ans[i] << " ";
}