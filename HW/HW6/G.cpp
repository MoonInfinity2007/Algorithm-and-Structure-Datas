#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<int64_t> vi;
typedef std::string str;

int64_t manacher(str& s) {
    int64_t n = s.size();
    vi d1(n), d2(n);
    int64_t l = 0, r = -1;
    int64_t ans = 0;
    for (int64_t i = 0; i < n; ++i) {
        int64_t k = 1;
        if (i <= r) k = std::min(r - i + 1, d1[l + r - i]);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;
        d1[i] = k;
        ans += k - 1;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    l = 0;
    r = -1;
    for (int64_t i = 0; i < n; ++i) {
        int64_t k = 0;
        if (i <= r) k = std::min(r - i + 1, d2[l + r - i + 1]);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
        d2[i] = k;
        ans += k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    str s;
    std::cin >> s;
    std::cout << manacher(s) << '\n';
}
