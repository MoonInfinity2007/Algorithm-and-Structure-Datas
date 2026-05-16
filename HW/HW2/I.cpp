#include <iostream>
#include <cstdint>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

#define LD long double

struct TL {
    LD a, b, p;
};

int main() {
    LD T, D;
    int64_t N;
    std::cin >> T >> D >> N;
    std::vector<TL> tl(N);
    for (int64_t i = 0; i < N; ++i) std::cin >> tl[i].a >> tl[i].b >> tl[i].p;
    std::sort(tl.begin(), tl.end(), [](TL a, TL b){return a.p < b.p;});
    LD left = 0, right = 1e18;
    auto f = [&](LD speed) {
        LD time = 0;
        LD past = 0;
        for (int64_t i = 0; i < N && tl[i].p <= D; ++i) {
            time += ((tl[i].p - past)/speed);
            LD phase = fmod(time, tl[i].a + tl[i].b);
            if (phase < tl[i].a) {
                time += tl[i].a - phase;
            }
            past = tl[i].p;
        }
        time += (D - past) / speed;
        return time;
    };
    for (int64_t i = 0; i < 1000; ++i) {
        LD mid = (right + left) / 2;
        if (f(mid) <= T) right = mid;
        else left = mid;
    }
    std::cout << std::setprecision(10) << std::fixed;
    if (right == 1e18) std::cout << -1.0;
    else std::cout << right;
}