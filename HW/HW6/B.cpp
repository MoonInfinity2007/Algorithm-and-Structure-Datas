#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

typedef std::vector<int64_t> vi;

vi z_to_pi(vi& z) {
    int64_t n = z.size();
    vi pi(n, 0);
    for (int64_t i = 1; i < n; ++i) {
        if (z[i] > 0) {
            int64_t j = i + z[i] - 1;
            pi[j] = std::max(pi[j], z[i]);
        }
    }
    for (int64_t j = n - 2; j >= 0; --j) pi[j] = std::max(pi[j], pi[j + 1] - 1);
    return pi;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n;
    std::cin >> n;
    vi z(n);
    for (int64_t i = 0; i < n; ++i) std::cin >> z[i];
    vi pi = z_to_pi(z);
    for (auto elem : pi) std::cout << elem << ' ';
    std::cout << '\n';
}
