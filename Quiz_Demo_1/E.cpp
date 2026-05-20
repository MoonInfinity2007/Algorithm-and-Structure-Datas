#include <iostream>
#include <cstdint>
#include <vector>

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    std::vector<int64_t> a(m);
    for (int64_t i = 0; i < m; ++i) std::cin >> a[i];
    auto f = [&](int64_t t) {
        int64_t sum = 0;
        for (int64_t i = 0; i < m; ++i) sum += t / a[i];
        return sum;
    };
    int64_t l = 0, r = 1e18;
    while (r - l > 1) {
        int64_t mid = (l + r) / 2;
        if (f(mid) >= n) r = mid;
        else l = mid;
    }
    std::cout << r;
}
