#include <iostream>
#include <cstdint>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string p = "caba";
    std::string s = "abacabaabacabaabacabaabacabaabacaba";
    s = '\0' + s;
    uint64_t n = s.size();
    int64_t mod = 1e9 + 9;
    int64_t base = 257;
    std::vector<int64_t> k(n), pref(n);
    int64_t h_p = 0;
    for (uint64_t i = 0; i < p.size(); ++i) h_p = (h_p * base + p[i]) % mod;
    for (uint64_t i = 1; i < n; ++i) {
        k[i] = (k[i - 1] * base) % mod;
        pref[i] = (pref[i - 1] * base + s[i]) % mod;
    }
    for (uint64_t i = 0; i < n - p.size(); ++i) {
        int64_t h_sbs = (pref[i + p.size()] - pref[i] * k[p.size()] % mod + mod) % mod;
    }
}