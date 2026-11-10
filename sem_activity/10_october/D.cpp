#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    int64_t dp[n + 4][m + 4];
    int64_t p[n + 4];
    dp[0][0] = 1;
    n--; m--;
    for (int64_t i = 1; i < n + 1; i++) dp[i][0] = dp[i - 1][0];
    for (int64_t i = 1; i < m + 1; i++) dp[0][i] = dp[0][i - 1];
    for (int64_t i = 1; i < n + 1; i++) {
        for (int64_t j = 1; j < m + 1; j++) dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
    std::cout << dp[n][m] << "\n";
}