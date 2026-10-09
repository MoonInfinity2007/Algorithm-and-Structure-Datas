#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>

// 4. Префикс-функция (SP на лекции).
std::vector<int64_t> prefix_function(const std::string& s) {
    int64_t n = s.size();
    std::vector<int64_t> pi(n, 0);
    for (int64_t i = 1; i < n; ++i) {
        int64_t j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

// 5. КМП через SP/префикс-функцию.
std::vector<int64_t> kmp_search(const std::string& t, const std::string& p) {
    std::vector<int64_t> ans;
    int64_t n = t.size(), m = p.size();
    if (m == 0) return ans;
    std::vector<int64_t> pi = prefix_function(p);
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
    for (int64_t x : prefix_function(p)) std::cout << x << ' ';
    std::cout << '\n';
    for (int64_t x : kmp_search(t, p)) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}

