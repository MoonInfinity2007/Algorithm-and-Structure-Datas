#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>

int main() {
    int64_t n, k, m;
    std::cin >> n >> k >> m;
    int64_t L[m];
    for (int64_t i  = 0; i < m; i++) std::cin >> L[i];
    int64_t dp[n + 4];
    dp[0] = 0;
    dp[1] = 1;
    for (int64_t i = 2; i < n + 1; i++) {
        dp[i] = 0;
        for (int64_t j = std::max<int64_t>(i - k, 0); j < i; j++) {
            if (std::find(L, L + m, j) == L + m) dp[i] += dp[j];
        }
    }
    std::cout << dp[n];
}