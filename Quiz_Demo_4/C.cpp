#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<int64_t> vi;
typedef std::string str;

vi z_func(str& t, str& p) {
    str s = p + '$' + t;
    int64_t n = s.size();
    vi z(n, 0);
    int64_t l = 0, r = -1;
    for (int64_t i = 1; i < n; i++) {
        if (i < r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}

int main() {
    str t, p;
    std::cin >> p >> t;
    vi zl = z_func(t, p);
    std::reverse(t.begin(), t.end());
    std::reverse(p.begin(), p.end());
    vi zr = z_func(t, p);
    int64_t k = p.size() - 1;
    std::reverse(zr.begin() + k + 2, zr.end());
    vi ans = {};
    for (int64_t i = p.size() + 1; i < zl.size() - k; i++) {
        if (zl[i] + zr[k + i] >= k) ans.push_back(i - k - 1);
    }
    std::cout << ans.size() << "\n";
    for (auto elem : ans) std::cout << elem << " ";
}