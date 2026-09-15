#include <iostream>
#include <cstdint>

int main() {
    int64_t N, x, y;
    std::cin >> N >> x >> y;
    auto f = [&] (int64_t t) -> int64_t {
        return t / x + t / y;
    };
    int64_t l = 0, r = N, mid;
    while (r - l > 1) {
        mid = (l + r) / 2;
        if (f(mid) > N) r = mid;
        else l = mid;
    }
    std::cout << r;
}