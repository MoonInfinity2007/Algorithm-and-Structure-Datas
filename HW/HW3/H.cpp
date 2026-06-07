#include <iostream>
#include <cstdint>
#include <vector>

typedef std::vector<std::vector<int64_t>> vvi;

uint64_t dfs(uint64_t v, const vvi& vec, std::vector<bool>& us) {
    us[v] = true;
    uint64_t h = 0;
    for (auto u : vec[v]) {
        if (!us[u]) h = std::max(h, dfs(u, vec, us));
    }
    return h + 1;
}

int main() {
    uint64_t N, x, y, ma = 0;
    std::cin >> N;
    vvi vec(N);
    std::vector<bool> us(N, false);
    for (uint64_t i = 0; i < N - 1; ++i) {
        std::cin >> x >> y;
        x--;
        y--;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    for (uint64_t i = 0; i < N; ++i) {
        ma = std::max(dfs(i, vec, us), ma);
        us.clear();
        us.resize(N, 0);
    }
    std::cout << ma;
}