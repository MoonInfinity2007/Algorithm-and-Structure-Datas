#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n, m;
    std::cin >> n >> m;
    std::vector<std::string> field(n);
    for (uint64_t i = 0; i < n; ++i) std::cin >> field[i];
    uint64_t base1 = 911382323, base2 = 972663749;
    std::vector<uint64_t> k1(n + 1, 1), k2(m + 1, 1);
    for (uint64_t i = 1; i <= n; ++i) k1[i] = k1[i - 1] * base1;
    for (uint64_t i = 1; i <= m; ++i) k2[i] = k2[i - 1] * base2;
    std::vector<std::vector<uint64_t>> pref(n + 1, std::vector<uint64_t>(m + 1));
    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t row = 0;
        for (uint64_t j = 1; j <= m; ++j) {
            row = row * base2 + field[i - 1][j - 1];
            pref[i][j] = pref[i - 1][j] * base1 + row;
        }
    }
    auto get_hash = [&](uint64_t i, uint64_t j, uint64_t len) -> uint64_t {
        return pref[i + len][j + len] - pref[i][j + len] * k1[len]
            - pref[i + len][j] * k2[len] + pref[i][j] * k1[len] * k2[len];
    };
    uint64_t l = 0, r = std::min(n, m) + 1;
    uint64_t ans1 = 0, ans2 = 0;
    std::unordered_multimap<uint64_t, uint64_t> hashes;
    hashes.reserve(n * m);
    while (r - l > 1) {
        uint64_t mid = (l + r) / 2;
        bool flag = false;
        hashes.clear();
        for (uint64_t i = 0; i + mid <= n && !flag; ++i) {
            for (uint64_t j = 0; j + mid <= m && !flag; ++j) {
                uint64_t hash = get_hash(i, j, mid);
                auto range = hashes.equal_range(hash);
                for (auto it = range.first; it != range.second; ++it) {
                    uint64_t x = it->second / m, y = it->second % m;
                    bool equal = true;
                    for (uint64_t t = 0; t < mid; ++t) {
                        if (field[i + t].compare(j, mid, field[x + t], y, mid) != 0) {
                            equal = false;
                            break;
                        }
                    }
                    if (equal) {
                        ans1 = it->second;
                        ans2 = i * m + j;
                        flag = true;
                        break;
                    }
                }
                if (!flag) hashes.emplace(hash, i * m + j);
            }
        }
        if (flag) l = mid;
        else r = mid;
    }
    std::cout << l << '\n';
    if (l > 0) {
        std::cout << ans1 / m + 1 << ' ' << ans1 % m + 1 << '\n';
        std::cout << ans2 / m + 1 << ' ' << ans2 % m + 1 << '\n';
    }
}
