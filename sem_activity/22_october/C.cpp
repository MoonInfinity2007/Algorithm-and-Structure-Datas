#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s, p;
    std::cin >> s >> p;
    s = '\0' + s;
    uint64_t n = s.size();
    int64_t mod = 1e9 + 9;
    int64_t base = 257;
    std::vector<int64_t> k(n), pref(n);
    k[0] = 1;
    int64_t h_p = 0;
    for (uint64_t i = 0; i < p.size(); ++i) h_p = (h_p * base + p[i]) % mod;
    for (uint64_t i = 1; i < n; ++i) {
        k[i] = (k[i - 1] * base) % mod;
        pref[i] = (pref[i - 1] * base + s[i]) % mod;
    }
    int64_t c = 0;
    std::vector<int64_t> ans;
    auto get_hash = [&](uint64_t left, uint64_t right) -> int64_t {
        return (pref[right] - (pref[left - 1] * k[right - left + 1]) % mod + mod) % mod;
    };
    for (uint64_t i = 1; i < n - p.size() + 1; ++i) {
        int64_t h_sbs = get_hash(i, i + p.size() - 1);
        if (h_p == h_sbs) {
            c++;
            ans.push_back(i);
        }
    }
    std::cout << c << "\n";
    for (auto u : ans) std::cout << u << " ";
}