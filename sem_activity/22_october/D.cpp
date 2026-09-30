#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    s = '\0' + s;
    uint64_t n = s.size();
    int64_t mod = 1e9 + 9;
    int64_t base = 257;
    std::vector<int64_t> k(n), pref(n);
    k[0] = 1;
    int64_t c = 0;
    for (uint64_t i = 1; i < n; ++i) {
        k[i] = (k[i - 1] * base) % mod;
        pref[i] = (pref[i - 1] * base + s[i]) % mod;
    }
    std::vector<int64_t> ans;
    auto get_hash = [&](uint64_t left, uint64_t right) -> int64_t {
        return (pref[right] - (pref[left - 1] * k[right - left + 1]) % mod + mod) % mod;
    };
    uint64_t M = 0;
    std::cin >> M;
    for (uint64_t i = 0; i < M; i++) {
        int64_t a, b, c, d;
        std::cin >> a >> b >> c >> d;
        int64_t h_1 = get_hash(a, b);
        int64_t h_2 = get_hash(c, d);
        if (h_1 == h_2) std::cout << "Yes\n";
        else std::cout << "No\n";
    }
}