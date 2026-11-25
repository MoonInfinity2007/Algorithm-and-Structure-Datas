#include <iostream>
#include <cstdint>
#include <vector>

int main() {
    int64_t N;
    std::cin >> N;
    int64_t A[N], B[N], C[N], dp[N + 1];
    for (int64_t i = 0; i < N; i++) std::cin >> A[i] >> B[i] >> C[i];
    dp[0] = A[0];
    if (N > 1) dp[1] = std::min(A[1] + dp[0], B[0]);
    if (N > 2) dp[2] = std::min(std::min(A[2] + dp[1], B[1] + dp[0]), C[0]);
    for (int64_t i = 3; i < N; i++) dp[i] = std::min(std::min(A[i] + dp[i - 1], dp[i - 2] + B[i - 1]), dp[i - 3] + C[i - 2]);
    std::cout << dp[N - 1];
}