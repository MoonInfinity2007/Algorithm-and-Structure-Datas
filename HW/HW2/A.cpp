#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

int main() {
    int64_t N;
    std::cin >> N;
    std::vector<int64_t> a(N);
    for (int64_t i = 0; i < N; ++i) std::cin >> a[i];
    std::vector<std::pair<int64_t, int64_t>> ans;
    if (N == 2) {
        std::cout << 0 << '\n';
        return 0;
    }
    int64_t pos1 = 0;
    for (int64_t i = 0; i < N; ++i) {
        if (a[i] == 1) {
            pos1 = i;
            break;
        }
    }
    std::vector<int64_t> b;
    for (int64_t i = 0; i < N; ++i) b.push_back(a[(pos1 + i) % N]);
    a = b;
    for (int64_t k = 1; k < N; ++k) {
        while (a[k] != k + 1) {
            for (int64_t pos = k; pos >= 1; --pos) {
                int64_t x = a[pos - 1];
                int64_t y = a[pos];
                if (std::abs(x - y) <= 1) {
                    std::cout << -1 << '\n';
                    return 0;
                }
                ans.push_back({x, y});
                std::swap(a[pos - 1], a[pos]);
            }
            int64_t first = a[0];
            for (int64_t i = 0; i + 1 < N; ++i) a[i] = a[i + 1];
            a[N - 1] = first;
        }
    }
    if ((int64_t)ans.size() > 50000) {
        std::cout << -1 << '\n';
        return 0;
    }
    for (auto [x, y] : ans) std::cout << x << ' ' << y << '\n';
    std::cout << 0 << '\n';

    return 0;
}