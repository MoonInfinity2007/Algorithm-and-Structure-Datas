#include <iostream>
#include <cstdint>

int main() {
    int64_t T, D, N;
    std::cin >> T >> D >> N;
    int64_t a[N], b[N], p[N];
    for (int64_t i = 0; i < N; ++i) std::cin >> a[i];
    for (int64_t i = 0; i < N; ++i) std::cin >> b[i];
    for (int64_t i = 0; i < N; ++i) std::cin >> p[i];
    int64_t left = 0, right = a[N - 1];
    auto f = [&](int64_t speed) {
    };
    while (right - left > 1) {
        int64_t mid = (right + left) / 2;
        if (f(mid)) right = mid;
        else left = mid;
    }
    std::cout << left;
}