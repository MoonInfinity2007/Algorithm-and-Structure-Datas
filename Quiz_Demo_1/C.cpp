#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    std::vector<int64_t> a(n*m);
    for (int64_t i = 0; i < n*m; ++i) std::cin >> a[i];
    ino64_t k;
    std::cin >> k;
    std::vector<int64_t> b(k);
    for (int64_t i = 0; i < k; ++i) std::cin >> b[i];
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    int64_t i = 0, j = 0;
    while (i < k && j < n * m) {
        if (b[i] <= a[j]) {
            a[j] -= b[i];
            ++i;
        }
        ++j;
    }
    std::cout << i;
}