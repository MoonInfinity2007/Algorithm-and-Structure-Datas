#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>

int main() {
    int64_t n;
    std::cin >> n;
    int64_t a[n];
    for (int64_t i  = 0; i < n; i++) std::cin >> a[i];
    int64_t dp[n + 2];
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
    for (int64_t i = 0; i < n; i++) {
        int64_t j = bs(a[i]);
        if (dp[j - 1] < a[i] && a[i] < dp[j]) {
            dp[j] = a[i];
            ans = std::max(ans, j);
        }
    }
    std::cout << ans;
}