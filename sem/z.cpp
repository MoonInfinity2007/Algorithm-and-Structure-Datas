#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    int64_t n = s.size(), l = 0, r = -1;
    std::vector<int64_t> z(n);
    for (int64_t i = 1; i < n; ++i) {
        if (i <= r) z[i] = std::min(z[i - l], r - i + 1); 
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])  z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

/*
abacabaabacaba
00103017000000
*/
