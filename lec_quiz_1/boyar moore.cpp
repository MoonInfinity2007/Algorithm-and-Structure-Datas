#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>

// 6. Бойер-Мур: сильное правило хорошего суффикса + плохой символ.
// shift[j + 1] — сдвиг, если несовпадение произошло в позиции j.
void bm_make_shift(const std::string& p, std::vector<int64_t>& shift) {
    int64_t m = p.size();
    shift.assign(m + 1, 0);
    std::vector<int64_t> border(m + 1, 0);
    int64_t i = m, j = m + 1;
    border[i] = j;

    while (i > 0) {
        while (j <= m && p[i - 1] != p[j - 1]) {
            if (shift[j] == 0) shift[j] = j - i;
            j = border[j];
        }
        --i;
        --j;
        border[i] = j;
    }

    j = border[0];
    for (i = 0; i <= m; ++i) {
        if (shift[i] == 0) shift[i] = j;
        if (i == j) j = border[j];
    }
}

std::vector<int64_t> boyer_moore_search(const std::string& t, const std::string& p) {
    std::vector<int64_t> ans;
    int64_t n = t.size(), m = p.size();
    if (m == 0) return ans;

    std::vector<int64_t> last(256, -1);
    for (int64_t i = 0; i < m; ++i) {
        last[static_cast<unsigned char>(p[i])] = i;
    }
    std::vector<int64_t> shift;
    bm_make_shift(p, shift);

    int64_t i = 0;
    while (i + m <= n) {
        int64_t j = m - 1;
        while (j >= 0 && p[j] == t[i + j]) --j;
        if (j < 0) {
            ans.push_back(i);
            i += shift[0];
        } else {
            int64_t bad = j - last[static_cast<unsigned char>(t[i + j])];
            int64_t good = shift[j + 1];
            i += std::max(int64_t(1), std::max(bad, good));
        }
    }
    return ans;
}


int main() {
    std::string t = "ABABABA", p = "ABA";
    for (int64_t x : boyer_moore_search(t, p)) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}

