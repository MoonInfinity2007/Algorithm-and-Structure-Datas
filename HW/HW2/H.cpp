#include <iostream>
#include <cstdint>

int main() {
    int64_t N, K;
    std::cin >> N >> K;
    int64_t a[N];
    for (int64_t i = 0; i < N; ++i) std::cin >> a[i];
    //int64_t left = , right = ;
    auto f = [&](int64_t t) {
        return ;
    };
    while (right - left > 1) {
        int64_t mid = (right + left) / 2;
        if (f(mid)) right = mid;
        else left = mid;
    }
    std::cout << right;
}