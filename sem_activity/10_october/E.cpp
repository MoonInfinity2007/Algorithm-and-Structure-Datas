#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    int64_t dp[n][m], a[n][m];
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < m; j++) std::cin >> a[i][j];
    }
    int64_t p[n + 4];
    dp[0][0] = a[0][0];
    for (int64_t i = 1; i < n; i++) dp[i][0] = dp[i - 1][0] + a[i][0];
    for (int64_t i = 1; i < m; i++) dp[0][i] = dp[0][i - 1] + a[0][i];
    for (int64_t i = 1; i < n; i++) {
        for (int64_t j = 1; j < m; j++) dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + a[i][j];
    }
    std::cout << dp[n - 1][m - 1] << "\n";
}
