#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

struct Segment {
    uint32_t l;
    uint32_t r;
    int8_t byte;
};

int main() {
    uint32_t n, Q, a, b;
    std::cin >> n >> Q >> a >> b;
    uint32_t cur = 0;
    auto nextRand24 = [&]() -> uint32_t {
        cur = cur * a + b;
        return cur >> 8;
    };
    auto nextRand32 = [&]() -> uint32_t {
        uint32_t a1 = nextRand24();
        uint32_t b1 = nextRand24();
        return (a1 << 8) ^ b1;
    };
    std::vector<uint32_t> data(n);
    for (uint32_t i = 0; i < n; ++i) data[i] = nextRand32();
    uint32_t l = 0, r = n, need = Q -1;
    auto pivf = [](uint32_t x, uint32_t y, uint32_t z) {
        if ((x <= y && y <= z) || (z <= y && y <= x)) return y;
        if ((y <= x && x <= z) || (z <= x && x <= y)) return x;
        return z;
    };
    while (r - l > 1) {
        uint32_t mid = (r + l) / 2, pivot = pivf(data[l], data[mid], data[r - 1]);
        uint32_t lt = l, i = l, gt = r;
        while (i < gt) {
            if (data[i] < pivot) {
                std::swap(data[i], data[lt]);
                ++i;
                ++lt;
            } else if (data[i] > pivot) {
                --gt;
                std::swap(data[i], data[gt]);
            } else ++i;
        }
        if (need < lt) r = lt;
        else if (need >= gt) l = gt;
        else {
            std::cout << pivot;
            return 0;
        }
    }
    std::cout << data[l];
    return 0;
}