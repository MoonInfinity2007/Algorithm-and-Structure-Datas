#include <iostream>
#include <cstdint>

int main() {
    int64_t n, x, y;
    std::cin >> n >> x >> y;
    int64_t left = std::min(x, y) - 1, right = n * std::max(x, y), mi = std::min(x, y);
    auto f = [&](int64_t t) {
        return 1 + (t - mi)/x + (t - mi)/y;
    };
    while (right - left > 1) {
        int64_t mid = (right + left) / 2;
        if (f(mid) >= n) right = mid;
        else left = mid;
    }
    std::cout << right;
}