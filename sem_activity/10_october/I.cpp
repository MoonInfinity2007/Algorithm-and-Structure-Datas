#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    int64_t S, n;
    std::cin >> S >> n;
    int64_t a[n];
    for (int64_t i = 0; i < n; i++) std::cin >> a[i];
    std::sort(a, a + n);
    int64_t dp[n + 1][S + 1];
    for (int64_t i = 0; i < n + 1; i++) dp[i][0] = 0;
    for (int64_t i = 0; i <= S; i++) dp[0][i] = 0;
    for (int64_t i = 1; i <= n; i++) {
        for (int64_t j = 0; j <= S; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= a[i - 1]) dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - a[i - 1]] + a[i - 1]);
        }
    }
    std::cout << dp[n][S];
}