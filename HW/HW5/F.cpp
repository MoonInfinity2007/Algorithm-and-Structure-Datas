#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t r, c;
    std::cin >> r >> c;
    std::vector<std::string> field(r);
    for (uint64_t i = 0; i < r; ++i) std::cin >> field[i];
    auto equal = [&](uint64_t i, uint64_t j) -> bool {
        for (uint64_t k = 0; k < r; ++k) {
            if (field[k][i] != field[k][j]) return false;
        }
        return true;
    };
    std::vector<uint64_t> p(c);
    for (uint64_t i = 1; i < c; ++i) {
        uint64_t j = p[i - 1];
        while (j > 0 && !equal(i, j)) j = p[j - 1];
        if (equal(i, j)) ++j;
        p[i] = j;
    }
    uint64_t b = c - p[c - 1];
    uint64_t base1 = 257, base2 = 263;
    std::vector<uint64_t> k1(r + 1, 1), k2(b + 1, 1);
    for (uint64_t i = 1; i <= r; ++i) k1[i] = k1[i - 1] * base1;
    for (uint64_t i = 1; i <= b; ++i) k2[i] = k2[i - 1] * base2;
    std::vector<std::vector<uint64_t>> pref(r + 1, std::vector<uint64_t>(b + 1));
    for (uint64_t i = 1; i <= r; ++i) {
        for (uint64_t j = 1; j <= b; ++j) {
            pref[i][j] = field[i - 1][j - 1] + pref[i - 1][j] * base1
                + pref[i][j - 1] * base2 - pref[i - 1][j - 1] * base1 * base2;
        }
    }
    auto get_hash = [&](uint64_t top, uint64_t left, uint64_t bottom, uint64_t right) -> uint64_t {
        return pref[bottom][right] - pref[top][right] * k1[bottom - top]
            - pref[bottom][left] * k2[right - left]
            + pref[top][left] * k1[bottom - top] * k2[right - left];
    };
    for (uint64_t a = 1; 2 * a <= r; ++a) {
        for (uint64_t s = 0; s < b; ++s) {
            if (get_hash(0, 0, r - a, b - s) != get_hash(a, s, r, b)) continue;
            if (get_hash(0, b - s, r - a, b) != get_hash(a, 0, r, s)) continue;
            bool flag = true;
            for (uint64_t i = a; i < r && flag; ++i) {
                for (uint64_t j = 0; j < b; ++j) {
                    if (field[i][(j + s) % b] != field[i - a][j]) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                std::cout << a << ' ' << b << ' ' << s << '\n';
                return 0;
            }
        }
    }
}
