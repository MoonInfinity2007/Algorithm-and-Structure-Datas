#include <iostream>
#include <cstdint>
#include <vector>

int main() {
    int64_t N, x;
    std::cin >> N;
    std::vector<int64_t> dp(N + 1, 0);
    for (int64_t i = 1; i <= N; ++i) {
        std::cin >> x;
        dp[i] = dp[i - 1] + ((x == 0) ? 1 : 0);
    }
    int64_t K;
    std::cin >> K;
    for (int64_t i = 0; i < K; ++i) {
        int64_t l, r;
        std::cin >> l >> r;
        std::cout << dp[r] - dp[l - 1] << " ";
    }
}