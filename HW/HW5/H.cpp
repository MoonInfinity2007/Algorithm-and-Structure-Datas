#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n, m;
    std::cin >> n >> m;
    std::vector<std::string> field(n + 2, std::string(m + 2, '0'));
    for (uint64_t i = 1; i <= n; ++i) {
        for (uint64_t j = 1; j <= m; ++j) std::cin >> field[i][j];
    }
    uint64_t base = 1e9 + 9;
    std::vector<uint64_t> k(std::min(n, m) + 1, 1);
    for (uint64_t i = 1; i < k.size(); ++i) k[i] = k[i - 1] * base;
    std::vector<std::vector<uint64_t>> pref1(n + 2, std::vector<uint64_t>(m + 2));
    std::vector<std::vector<uint64_t>> pref2(n + 2, std::vector<uint64_t>(m + 2));
    std::vector<std::vector<uint64_t>> pref3(n + 2, std::vector<uint64_t>(m + 2));
    std::vector<std::vector<uint64_t>> pref4(n + 2, std::vector<uint64_t>(m + 2));
    for (uint64_t i = 1; i <= n; ++i) {
        for (uint64_t j = 1; j <= m; ++j) {
            pref1[i][j] = pref1[i][j - 1] * base + field[i][j];
            pref3[i][j] = pref3[i - 1][j] * base + field[i][j];
        }
    }
    for (uint64_t i = n; i > 0; --i) {
        for (uint64_t j = m; j > 0; --j) {
            pref2[i][j] = pref2[i][j + 1] * base + field[i][j];
            pref4[i][j] = pref4[i + 1][j] * base + field[i][j];
        }
    }
    uint64_t ans = 0, x = 1, y = 1;
    for (uint64_t i = 1; i <= n; ++i) {
        for (uint64_t j = 1; j <= m; ++j) {
            uint64_t limit = std::min({i - 1, n - i, j - 1, m - j});
            if (limit <= ans) continue;
            uint64_t len = ans + 1;
            uint64_t right = pref1[i][j + len] - pref1[i][j] * k[len];
            uint64_t left = pref2[i][j - len] - pref2[i][j] * k[len];
            uint64_t down = pref3[i + len][j] - pref3[i][j] * k[len];
            uint64_t up = pref4[i - len][j] - pref4[i][j] * k[len];
            if (right != left || right != down || right != up) continue;
            uint64_t size = 0;
            for (uint64_t t = 1; t <= limit; ++t) {
                if (field[i][j + t] != field[i][j - t] || field[i][j + t] != field[i + t][j] || field[i][j + t] != field[i - t][j]) break;
                size = t;
            }
            if (size > ans) {
                ans = size;
                x = i;
                y = j;
            }
        }
    }
    std::cout << ans << ' ' << x << ' ' << y << '\n';
}
