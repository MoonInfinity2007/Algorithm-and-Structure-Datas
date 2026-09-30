#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

int main() {
    std::string s, p;
    std::cin >> s >> p;
    s = p + '#' + s;
    int64_t n = s.size(), l = 0, r = -1;
    std::vector<int64_t> z(n), ans;
    for (int64_t i = 1; i < n; ++i) {
        if (i <= r) z[i] = std::min(z[i - l], r - i + 1); 
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])  z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i] - 1;
        }
       if (z[i] >= p.size()) ans.push_back(i - p.size());
    }
    std::cout << ans.size() << "\n";
    for (auto u : ans) std::cout << u << " ";
}
