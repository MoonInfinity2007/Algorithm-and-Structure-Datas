#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    int64_t p = 0, m = 0;
    std::cin >> p >> m >> s;
    uint64_t n = s.size();
    int64_t h_p = 0;
    for (uint64_t i = n - 1; i < n; --i) h_p = (h_p * p + s[i] + 1 - 'a') % m;
    std::cout << h_p;
}