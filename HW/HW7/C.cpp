#include <iostream>
#include <cstdint>
#include <algorithm>
#include <array>

int64_t dp[50][50];

int64_t solve(int64_t x, int64_t y, const auto &valid, const auto& steps){
    if (!valid(x, y)) return 0;
    if (dp[x][y] != -1) return dp[x][y];
    dp[x][y] = 0;
    for (auto [dx, dy] : steps) dp[x][y] += solve(x - dx, y - dy, valid, steps);
    return dp[x][y];
};

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    std::array<std::pair<int64_t, int64_t>, 4> steps = {{
        {2, 1},
        {2, -1},
        {1, 2},
        {-1, 2} 
    }};
    auto valid = [&] (int64_t x, int64_t y) -> bool {
        if (x < 0 || x >= n || y >= m || y < 0) return false;
        return true;
    };
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < m; j++) dp[i][j] = -1;
    }
    dp[0][0] = 1;
    std::cout << solve(n - 1, m - 1, valid, steps);
}