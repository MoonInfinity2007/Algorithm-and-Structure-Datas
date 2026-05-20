#include <iostream>
#include <cstdint>
#include <deque>
#include <vector>

int main() {
    int64_t n;
    std::cin >> n;
    std::deque<std::pair<int64_t, int64_t>> q;
    std::vector<int64_t> ans(n);
    for (int64_t i = 0; i < n; ++i) {
        int64_t h = 0, m = 0, angry = 0;
        std::cin >> h >> m >> angry;
        int64_t t = h * 60 + m;
        while (!q.empty() && q.front().first <= t) {
            ans[q.front().second] = q.front().first;
            q.pop_front();
        }
        if (q.empty()) q.push_back({t + 20, i});
        else if (q.size() <= angry) q.push_back({q.back().first + 20, i});
        else ans[i] = t;
    }
    while (!q.empty()) {
        ans[q.front().second] = q.front().first;
        q.pop_front();
    }
    for (int64_t i = 0; i < n; ++i) std::cout << ans[i] / 60 << " " << ans[i] % 60 << "\n";
}