#include <iostream>
#include <cstdint>

int main() {
    int64_t N, K;
    std::cin >> N >> K;
    int64_t a[N];
    for (int64_t i = 0; i < N; ++i) std::cin >> a[i];
    int64_t left = 0, right = a[N - 1];
    auto f = [&](int64_t distance) {
        int64_t past = -distance, count = 0;
        for (int i = 0; i < N; ++i) {
            if (past + distance <= a[i]) {
                ++count;
                past = a[i];
            }
        }
        return count;
    };
    while (right - left > 1) {
        int64_t mid = (right + left) / 2;
        if (f(mid) < K) right = mid;
        else left = mid;
    }
    std::cout << left;
}