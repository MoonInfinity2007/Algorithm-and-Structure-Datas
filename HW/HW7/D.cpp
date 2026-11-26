#include <iostream>
#include <cstdint>

int64_t dp[100][100];

bool check(int64_t x, int64_t y, int64_t n, int64_t m) {
    for (int64_t i = x + 1; i < n; i++) {
        if (dp[i][y] == 0) return true; 
    }
    for (int64_t i = y + 1; i < m; i++) {
        if (dp[x][i] == 0) return true; 
    }
    for (int64_t i = 1; x + i < n && y + i < m; i++) {
        if (dp[x + i][i + y] == 0) return true; 
    }
    return false;
}

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    dp[n - 1][m - 1] = 0;
    for (int64_t i = n - 1; i > -1; i--) {
        for (int64_t j = m - 1; j > -1; j--) {
            if (i == n - 1 && j == m - 1) continue;
            if (check(i, j, n, m)) dp[i][j] = 1;
            else dp[i][j] = 0;
        }
    }
    std::cout << (dp[0][0] ? 1 : 2);
}