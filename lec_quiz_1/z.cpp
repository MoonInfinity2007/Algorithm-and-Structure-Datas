#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>

// 2. Z-функция.
std::vector<int64_t> z_function(const std::string& s) {
    int64_t n = s.size();
    std::vector<int64_t> z(n, 0);
    int64_t l = 0, r = 0; // [l, r)
    for (int64_t i = 1; i < n; ++i) {
        if (i < r) z[i] = std::min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// 3. Поиск образца через Z-функцию (разделитель '#' уникален).
std::vector<int64_t> z_search(const std::string& t, const std::string& p) {
    std::vector<int64_t> ans;
    int64_t n = t.size(), m = p.size();
    if (m == 0) return ans;
    std::string s = p + '#' + t;
    std::vector<int64_t> z = z_function(s);
    for (int64_t i = 0; i + m <= n; ++i) {
        if (z[m + 1 + i] == m) ans.push_back(i);
    }
    return ans;
}


int main() {
    std::string t = "ABABABA", p = "ABA";
    for (int64_t x : z_function(p)) std::cout << x << ' ';
    std::cout << '\n';
    for (int64_t x : z_search(t, p)) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}

