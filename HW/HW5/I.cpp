#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::string> field(n);
    for (uint64_t i = 0; i < n; ++i) std::cin >> field[i];
    std::vector<uint64_t> hashes((n - k + 1) * (m - k + 1));
    std::vector<std::vector<int64_t>> pref(n + 1, std::vector<int64_t>(m + 1));
    for (int64_t mod : {1000000007LL, 1000000009LL}) {
        int64_t base1 = (mod == 1000000007LL ? 911382323 : 97266353);
        int64_t base2 = (mod == 1000000007LL ? 972663749 : 911382323);
        int64_t k1 = 1, k2 = 1;
        for (uint64_t i = 0; i < k; ++i) {
            k1 = (k1 * base1) % mod;
            k2 = (k2 * base2) % mod;
        }
        for (uint64_t i = 1; i <= n; ++i) {
            int64_t row = 0;
            for (uint64_t j = 1; j <= m; ++j) {
                row = (row * base2 + field[i - 1][j - 1]) % mod;
                pref[i][j] = (pref[i - 1][j] * base1 + row) % mod;
            }
        }
        auto get_hash = [&](uint64_t i, uint64_t j) -> int64_t {
            int64_t right = (pref[i][j] - (pref[i - k][j] * k1) % mod + mod) % mod;
            int64_t left = (pref[i][j - k] - (pref[i - k][j - k] * k1) % mod + mod) % mod;
            return (right - (left * k2) % mod + mod) % mod;
        };
        uint64_t index = 0;
        for (uint64_t i = k; i <= n; ++i) {
            for (uint64_t j = k; j <= m; ++j) {
                hashes[index] = (hashes[index] << 32) | get_hash(i, j);
                ++index;
            }
        }
    }
    std::sort(hashes.begin(), hashes.end());
    uint64_t ans = 1;
    for (uint64_t i = 1; i < hashes.size(); ++i) {
        if (hashes[i] != hashes[i - 1]) ++ans;
    }
    std::cout << ans << '\n';
}
