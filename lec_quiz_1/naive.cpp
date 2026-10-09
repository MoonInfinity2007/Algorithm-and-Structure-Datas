
    
  
#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <algorithm>
#include <utility>

// 1. Обычный поиск подстроки.
std::vector<int64_t> naive_search(const std::string& t, const std::string& p) {
    std::vector<int64_t> ans;
    int64_t n = t.size(), m = p.size();
    if (m == 0) return ans;

    for (int64_t i = 0; i + m <= n; ++i) {
        int64_t j = 0;
        while (j < m && t[i + j] == p[j]) ++j;
        if (j == m) ans.push_back(i);
    }
    return ans;
}


int main() {
    std::string t = "ABABABA", p = "ABA";
    for (int64_t x : naive_search(t, p)) std::cout << x << ' ';
    std::cout << '\n';
    return 0;
}

