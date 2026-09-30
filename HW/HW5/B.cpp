#include <iostream>
#include <cstdint>
#include <string>

int main() {
    uint64_t n;
    std::cin >> n;
    std::string s(n, 'a');
    for (uint64_t i = 0; i < n; ++i) {
        s[i] = 'b';
        std::cout << s << '\n';
        s[i] = 'a';
    }
}
