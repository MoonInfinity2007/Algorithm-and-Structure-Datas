#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <unordered_set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    s = '\0' + s;
    uint64_t n = s.size();
    int64_t base = 257;
    std::vector<int64_t> k(n), pref(n);
    k[0] = 1;
    int64_t c = 0;
    for (uint64_t i = 1; i < n; ++i) {
        k[i] = (k[i - 1] * base);
        pref[i] = (pref[i - 1] * base + s[i]);
    }
    std::vector<int64_t> ans;
    auto get_hash = [&](uint64_t left, uint64_t right) -> int64_t {
        return (pref[right] - (pref[left - 1] * k[right - left + 1]));
    };
    std::unordered_set<int64_t> st;
    for (uint64_t i = 0; i < n; i++) {
        for (uint64_t j = i + 1; j < n; j++) {
            int64_t h = get_hash(i + 1, j);
            st.insert(h);
        }
    }
    std::cout << st.size();
}