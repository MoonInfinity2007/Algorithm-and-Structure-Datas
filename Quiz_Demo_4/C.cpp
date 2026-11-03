
#include <iostream>
#include <vector>
#include <string>

std::vector<int> buildGoodSuffix(const std::string& p) {
    int m = p.size();

    std::vector<int> shift(m + 1, 0);
    std::vector<int> border(m + 1, 0);

    int i = m;
    int j = m + 1;

    border[i] = j;

    // Сильное правило хорошего суффикса
    while (i > 0) {
        while (j <= m && p[i - 1] != p[j - 1]) {
            if (shift[j] == 0) {
                shift[j] = j - i;
            }
            j = border[j];
        }

        --i;
        --j;
        border[i] = j;
    }

    // Обработка перекрытий с префиксом
    j = border[0];

    for (int i = 0; i <= m; ++i) {
        if (shift[i] == 0) {
            shift[i] = j;
        }

        if (i == j) {
            j = border[j];
        }
    }

    return shift;
}


int main() {
    std::string s = "abacaba";
    auto p = buildGoodSuffix(s);
}