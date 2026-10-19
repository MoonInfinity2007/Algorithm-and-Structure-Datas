#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<int64_t> vi;
typedef std::string str;

vi z_function(str& s) {
    int64_t n = s.size();
    vi z(n, 0);
    int64_t l = 0, r = 0;
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

vi a_function(str& s) {
    int64_t n = s.size();
    str t = s;
    std::reverse(t.begin(), t.end());
    t = s + '#' + t;
    vi z = z_function(t);
    vi ans(n);
    for (int64_t i = 0; i < n; ++i) ans[i] = z[2 * n - i];
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n;
    str s;
    std::cin >> n >> s;
    vi ans = a_function(s);
    for (auto elem : ans) std::cout << elem << ' ';
    std::cout << '\n';
}
