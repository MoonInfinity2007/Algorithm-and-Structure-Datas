#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>

int main() {
    int64_t n;
    std::cin >> n;
    int64_t cost[n];
    for (int64_t i  = 0; i < n; i++) std::cin >> cost[i];
    int64_t dp[n + 4];
    dp[0] = 0;
    dp[1] = cost[0];
    for (int64_t i = 2; i < n + 1; i++) {
        dp[i] = std::min<int64_t>(dp[i - 1], dp[i - 2]) + cost[i - 1];
    }
    std::cout << dp[n];
}