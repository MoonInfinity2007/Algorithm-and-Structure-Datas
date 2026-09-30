#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

int main() {
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
    while (r - l > 1) {
        bool flag = false;
        uint64_t mid = (l + r) / 2;
        for (uint64_t i = 1; i < n - mid; ++i) {
            for (uint64_t j = 1; j < n - mid; ++j) {
                if (get_hash_s1(i, i + mid) == get_hash_s2(j, j + mid)) {
                    ans1 = i;
                    flag = true;
                }
            }
        }
        if (flag) l = mid;
        else r = mid;
    }
    for (int i = ans1; i < ans1 + r; ++i) {std::cout << s1[i];}
}