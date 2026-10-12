#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<int64_t> vi;
typedef std::string str;

vi p_func(str& t) {
    int64_t n = t.size();
    vi pi(n);
    int64_t j = 0;
    for (int64_t i = 1; i < n; ++i) {
        int64_t j = pi[i - 1];
        while (j > 0 && t[j] != t[i]) j = pi[j - 1];
        if (t[j] == t[i]) ++j;
        pi[i] = j;
    }
    return pi;
}

int main() {
    str s;
    std::cin >> s;
    vi pi1 = p_func(s);
    std::reverse(s.begin(), s.end());
    vi pi2 = p_func(s);
    for (int64_t i = s.size() - 1; i >= 0; i--) {
        if (pi1[i] == 0) {
            std::cout << i + 1;
            break;
        }
        if (pi2[i] == 0) {
            std::cout << i + 1;
            break;
        }
    }
}