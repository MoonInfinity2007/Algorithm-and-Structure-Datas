#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

std::pair<std::string, std::string> info(int64_t st) {
    std::string a, b;
    if (st % 2 == 1) a = "low";
    else a = "high";
    if (st <= 36) b = "main";
    else b = "side";
    return {a, b};
}

int main() {
    std::vector<int64_t> poss;
    for (int64_t i = 1; i <= 54; i++) poss.push_back(i);
    int64_t sh = 0;
    for (int64_t step = 0; step < 6; step++) {
        if (poss.size() == 1) break;
        int64_t bsh = sh;
        int64_t bW = 1000000;
        for (int64_t newsh = -53; newsh <= 53; newsh++) {
            int64_t d = newsh - sh;
            if (d < -54 || d > 54) continue;
            bool flag = true;
            for (int64_t p : poss) {
                int64_t st = p + newsh;
                if (st < 1 || st > 54) {
                    flag = false;
                    break;
                }
            }
            if (!flag) continue;
            int64_t lowm = 0, highm = 0, lows = 0, highs = 0;
            for (int64_t p : poss) {
                int64_t st = p + newsh;
                if (st % 2 == 1 && st <= 36) lowm++;
                else if (st % 2 == 0 && st <= 36) highm++;
                else if (st % 2 == 1 && st >= 37) lows++;
                else highs++;
            }
            int64_t worst = std::max(std::max(lowm, highm), std::max(lows, highs));
            if (worst < bW) {
                bW = worst;
                bsh = newsh;
            }
        }
        int64_t d = bsh - sh;
        sh = bsh;
        std::cout << "? " << d << std::endl;
        std::cout.flush();
        std::string first, second;
        std::cin >> first >> second;
        std::vector<int64_t> nextposs;
        for (int64_t p : poss) {
            int64_t st = p + sh;
            std::pair<std::string, std::string> cur = info(st);
            if (cur.first == first && cur.second == second) nextposs.push_back(p);
        }
        poss = nextposs;
    }
    std::cout << "! " << poss[0] << std::endl;
    std::cout.flush();
    return 0;
}