#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>

// 2. Z-функция.
std::vector<int64_t> z_function(const std::string& s) {
    int64_t n = s.size();
    std::vector<int64_t> z(n, 0);
    int64_t l = 0, r = 0; // [l, r)
    for (int64_t i = 1; i < n; ++i) {
        if (i < r) z[i] = std::min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// 3. Поиск образца через Z-функцию (разделитель '#' уникален).
std::vector<int64_t> z_search(const std::string& t, const std::string& p) {
    std::vector<int64_t> ans;
    int64_t n = t.size(), m = p.size();
    if (m == 0) return ans;
    std::string s = p + '#' + t;
    std::vector<int64_t> z = z_function(s);
    for (int64_t i = 0; i + m <= n; ++i) {
        if (z[m + 1 + i] == m) ans.push_back(i);
    }
    return ans;
}

// 5a. Получаем SP из Z за O(m). Это было в лекции 1.
std::vector<int64_t> z_to_pi(const std::vector<int64_t>& z) {
    int64_t n = z.size();
    std::vector<int64_t> pi(n, 0);
    for (int64_t i = 1; i < n; ++i) {
        if (z[i] > 0) {
            int64_t j = i + z[i] - 1;
            pi[j] = std::max(pi[j], z[i]);
        }
    }
    for (int64_t j = n - 2; j >= 0; --j) {
        pi[j] = std::max(pi[j], pi[j + 1] - 1);
    }
    return pi;
}

// 5b. КМП с предварительной обработкой через Z, а не напрямую через SP.
std::vector<int64_t> kmp_using_z(const std::string& t, const std::string& p) {
    std::vector<int64_t> ans;
    int64_t n = t.size(), m = p.size();
    if (m == 0) return ans;
    std::vector<int64_t> pi = z_to_pi(z_function(p));
    int64_t j = 0;
    for (int64_t i = 0; i < n; ++i) {
        while (j > 0 && t[i] != p[j]) j = pi[j - 1];
        if (t[i] == p[j]) ++j;
        if (j == m) {
            ans.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return ans;
}


int main() {
    std::string t = "ABABABA", p = "ABA";
    for (int64_t x : kmp_using_z(t, p)) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}

