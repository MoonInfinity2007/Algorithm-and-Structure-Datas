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
    uint32_t bc = 255;
    std::vector<Segment> st;
    st.push_back({0, n, 3});
    while (!st.empty()) {
        Segment seg = st.back();
        st.pop_back();
        uint32_t l = seg.l, r = seg.r;
        int8_t byte = seg.byte;
        if (r - l <= 1 || byte < 0) continue;
        uint32_t cnt[bc + 1]{}, start[bc + 1]{}, pos[bc + 1]{}, finish[bc + 1]{};
        for (uint32_t i = l; i < r; ++i) {
            uint32_t num = (data[i] >> (byte * 8)) & bc;
            ++cnt[num];
        }
        start[0] = l;
        for (uint32_t i = 0; i <= bc; ++i) {
            if (i != 0) start[i] = start[i - 1] + cnt[i - 1];
            pos[i] = start[i];
            finish[i] = start[i] + cnt[i];
        }
        for (uint32_t buck = 0; buck <= bc; ++buck) {
            while (pos[buck] < finish[buck]) {
                uint32_t swbuck = (data[pos[buck]] >> (byte * 8)) & bc;
                if (swbuck == buck) ++pos[buck];
                else {
                    std::swap(data[pos[buck]], data[pos[swbuck]]);
                    ++pos[swbuck];
                }
            }
        }
        for (uint32_t buck = 0; buck <= bc; ++buck) {
            if (cnt[buck] > 1) {
                //st.push_back({start[buck], finish[buck], byte - 1});
            }
        }
    }
    std::cout << data[Q - 1];
    return 0;
}