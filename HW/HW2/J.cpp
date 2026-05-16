#include <iostream>
#include <cstdint>
#include <vector>

struct Point{int64_t x, y;};

typedef std::vector<Point> field;

int main() {
    int64_t N;
    std::cin >> N;
    field a(N);
    for (int64_t i = 0; i < N; ++i) std::cin >> a[i].x >> a[i].y;
    int64_t left = 0, right = 1e10;
    auto f = [&](int64_t distance) {
        int64_t maxu = -1e10, minu = 1e10, maxv = -1e10, minv = 1e10;
        for (int64_t i = 0; i < N; ++i) {
            int64_t u = a[i].x + a[i].y, v = a[i].x - a[i].y;
            maxu = std::max(u - distance, maxu);
            minu = std::min(u + distance, minu);
            maxv = std::max(v - distance, maxv);
            minv = std::min(v + distance, minv);
        }
        Point ans;
        int64_t u = (maxu + minu) / 2, v = (maxv + minv) / 2;
        if ((u + v) % 2) {
            if (u + 1 <= minu) ++u;
            else ++v;
        }
        ans.x = (u + v) / 2;
        ans.y = (u - v) / 2;
        return std::make_pair(minu >= maxu && minv >= maxv, ans);
    };
    Point ans;
    while (right - left > 1) {
        int64_t mid = (right + left) / 2;
        auto check = f(mid);
        if (check.first) {
            right = mid;
            ans = check.second;
        }
        else left = mid;
    }
    std::cout << ans.x << " " << ans.y;
}