#include <iostream>
#include <cstdint>
#include <algorithm>

int main() {
    int64_t N;
    std::cin >> N;
    int64_t x[N], dp[N + 1];
    for (int64_t i = 0; i < N; i++) std::cin >> x[i];
    std::sort(x, x + N);
    dp[1] = x[1] - x[0];
    if (N > 2) dp[2] = x[2] - x[0];
    for (int64_t i = 3; i < N; i++) dp[i] = std::min(dp[i - 2], dp[i - 1]) + x[i] - x[i - 1];
    std::cout << dp[N - 1];
}