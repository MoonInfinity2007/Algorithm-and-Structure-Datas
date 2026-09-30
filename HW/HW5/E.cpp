#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t g, n;
    std::cin >> g >> n;
    std::string w, s;
    std::cin >> w >> s;
    std::vector<int64_t> count(128);
    uint64_t diff = 0, ans = 0;
    auto update = [&](char c, int64_t value) {
        if (count[c] != 0) --diff;
        count[c] += value;
        if (count[c] != 0) ++diff;
    };
    for (uint64_t i = 0; i < g; ++i) update(w[i], -1);
    for (uint64_t i = 0; i < n; ++i) {
        update(s[i], 1);
        if (i >= g) update(s[i - g], -1);
        if (i + 1 >= g && diff == 0) ++ans;
    }
    std::cout << ans << '\n';
}
