#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string X, Y;
    std::cin >> X >> Y;
    std::vector<std::vector<int64_t>> posX(26), posY(26);
    for (int64_t i = 0; i < X.size(); ++i) posX[X[i] - 'a'].push_back(i);
    for (int64_t i = 0; i < Y.size(); ++i) posY[Y[i] - 'a'].push_back(i);
    int64_t curX = -1, curY = -1;
    std::string ans;
    bool found = true;
    while (found) {
        found = false;
        for (int64_t c = 25; c >= 0; --c) {
            auto itX = std::upper_bound(posX[c].begin(), posX[c].end(), curX);
            auto itY = std::upper_bound(posY[c].begin(), posY[c].end(), curY);
            if (itX != posX[c].end() && itY != posY[c].end()) {
                ans.push_back(char('a' + c));
                curX = *itX;
                curY = *itY;
                found = true;
                break;
            }
        }
    }
    std::cout << ans;
    return 0;
}