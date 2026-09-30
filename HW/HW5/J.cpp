#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n, m;
    std::cin >> n >> m;
    std::vector<std::string> field(n);
    for (uint64_t i = 0; i < n; ++i) std::cin >> field[i];
    std::vector<std::vector<uint64_t>> len(m + 2, std::vector<uint64_t>(m + 1));
    std::vector<std::vector<std::vector<uint8_t>>> dp(n + 1, std::vector<std::vector<uint8_t>>(m + 1, std::vector<uint8_t>(m + 1)));
    uint64_t ans = 0;
    for (uint64_t top = n; top > 0; --top) {
        for (uint64_t bottom = n; bottom >= top; --bottom) {
            for (uint64_t l = m; l > 0; --l) {
                for (uint64_t r = 1; r <= m; ++r) {
                    if (field[top - 1][l - 1] == field[bottom - 1][r - 1]) len[l][r] = len[l + 1][r - 1] + 1;
                    else len[l][r] = 0;
                }
            }
            for (uint64_t l = 1; l <= m; ++l) {
                for (uint64_t r = l; r <= m; ++r) {
                    bool flag = len[l][r] >= r - l + 1;
                    if (bottom - top > 1) flag = flag && dp[bottom - 1][l][r];
                    dp[bottom][l][r] = flag;
                    if (flag) ++ans;
                }
            }
        }
    }
    std::cout << ans << '\n';
}
