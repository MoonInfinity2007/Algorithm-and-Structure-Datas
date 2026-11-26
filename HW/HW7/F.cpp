#include <iostream>
#include <cstdint>
#include <string>

int main() {
    int64_t n;
    std::cin >> n;
    std::string s1, s2;
    for (int64_t i = 0; i < n; i++) {
        std::cin >> s1 >> s2;
        int64_t n = s1.size(), m = s2.size();
        int64_t dp[n + 1][m + 1];
        int64_t A;
        dp[0][0] = 0;
        for (int64_t i = 0; i <= n; i++) dp[i][0] = i;
        for (int64_t j = 0; j <= m; j++) dp[0][j] = j;
        for (int64_t i = 1; i <= n; i++) {
            for (int64_t j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) A = dp[i - 1][j - 1];
                else A = std::min(std::min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + 1);
                if (i > 1 && j > 1 &&s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) dp[i][j] = std::min(A, dp[i - 2][j - 2] + 1);
                else dp[i][j] = A;
            }
        }
        std::cout << dp[n][m] << " ";
    }
}