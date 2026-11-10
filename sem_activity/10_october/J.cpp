#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    int64_t x1, x2, x3;
    std::cin >> x1 >> x2 >> x3;
    if (x1 == x2 + x3 || x2 == x1 + x3 || x3 == x1 + x2) {
        std::cout << 0;
        return 0;
    }
    for (int64_t i = 0; i < x1; i++) {
        if (x1 - i + x2 == i + x3) {
            std::cout << 1 << "\n";
            std::cout << x1 - i << " " << i;
            return 0;
        }
        if (x1 - i + x3 == i + x2) {
            std::cout << 1 << "\n";
            std::cout << i << " " << x1 - i;
            return 0;
        }
    }
    for (int64_t i = 0; i < x2; i++) {
        if (x2 - i + x1 == i + x3) {
            std::cout << 2 << "\n";
            std::cout << x2 - i << " " << i;
            return 0;
        }
        if (x2 - i + x3 == i + x1) {
            std::cout << 2 << "\n";
            std::cout << i << " " << x2 - i;
            return 0;
        }
    }
    for (int64_t i = 0; i < x3; i++) {
        if (x3 - i + x1 == i + x2) {
            std::cout << 3 << "\n";
            std::cout << x3 - i << " " << i;
            return 0;
        }
        if (x3 - i + x2 == i + x1) {
            std::cout << 3 << "\n";
            std::cout << i << " " << x3 - i;
            return 0;
        }
    }
    std::cout << -1;
    return 0;
}