#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t base = 257;
    int64_t mod = 1e9 + 9;
    uint64_t n;
    std::cin >> n;
    std::string s1, s2;
    std::cin >> s1 >> s2;
    s1 = '\0' + s1;
    s2 = '\0' + s2;
    n++;
    std::vector<int64_t> k(n, 1), pref1(n), pref2(n);
    for (uint64_t i = 1; i < n; ++i) {
        k[i] = (k[i - 1] * base) % mod;
        pref1[i] = (pref1[i - 1] * base + s1[i]) % mod;
        pref2[i] = (pref2[i - 1] * base + s2[i]) % mod;
    }
    auto get_hash_s1 = [&](uint64_t left, uint64_t right) -> int64_t {
        return (pref1[right] - (pref1[left - 1] * k[right - left + 1]) % mod + mod) % mod;
    };
    auto get_hash_s2 = [&](uint64_t left, uint64_t right) -> int64_t{
        return (pref2[right] - (pref2[left - 1] * k[right - left + 1]) % mod + mod) % mod;
    };
    uint64_t l = 0, r = n;
    uint64_t ans1 = 0;
    std::unordered_multimap<int64_t, uint64_t> hashes;
    hashes.reserve(n);
    while (r - l > 1) {
        bool flag = false;
        uint64_t mid = (l + r) / 2;
        hashes.clear();
        for (uint64_t i = 1; i <= n - mid; ++i) hashes.emplace(get_hash_s1(i, i + mid - 1), i);
        for (uint64_t j = 1; j <= n - mid && !flag; ++j) {
            auto range = hashes.equal_range(get_hash_s2(j, j + mid - 1));
            for (auto it = range.first; it != range.second; ++it) {
                if (s1.compare(it->second, mid, s2, j, mid) == 0) {
                    ans1 = it->second;
                    flag = true;
                    break;
                }
            }
        }
        if (flag) l = mid;
        else r = mid;
    }
    for (uint64_t i = ans1; i < ans1 + l; ++i) {std::cout << s1[i];}
}