#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<int32_t> vi;
typedef std::string str;

vi z_function(str& s) {
    int32_t n = s.size();
    vi z(n, 0);
    int32_t l = 0, r = 0;
    for (int32_t i = 1; i < n; ++i) {
        if (i < r) z[i] = std::min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int32_t get_period(str& s) {
    int32_t n = s.size();
    vi z = z_function(s);
    for (int32_t i = 1; 2 * i <= n; ++i) {
        if (z[i] >= (n / i - 1) * i) return i;
    }
    return n;
}

void print_word(str& s) {
    int32_t n = s.size();
    int32_t p = get_period(s);
    if (p == n) {
        std::cout << s;
        return;
    }
    std::cout << n / p << "*(" << s.substr(0, p) << ')';
    if (n % p > 0) std::cout << '+' << s.substr(n - n % p);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    str s;
    bool flag = false;
    while (std::cin >> s) {
        if (flag) std::cout << ' ';
        print_word(s);
        flag = true;
    }
    std::cout << '\n';
}
