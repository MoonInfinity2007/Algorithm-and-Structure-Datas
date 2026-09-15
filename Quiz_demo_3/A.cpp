#include <iostream>
#include <cstdint>

int64_t foo(int64_t n, int64_t k) {
    if (n <= k) return 1;
    return foo(n / 2, k) + foo((n + 1) / 2, k);
}

int main() {
    int64_t n, k;
    std::cin >> n >> k;
    std::cout << foo(n, k);
}