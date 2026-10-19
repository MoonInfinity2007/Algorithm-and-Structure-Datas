#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<int64_t> vi;
typedef std::string str;

vi pi_func(str& s) {
    int64_t n = s.size();
    vi pi(n, 0);
    int64_t j = 0;
    for (int64_t i = 1; i < n; ++i) {
        j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[j] == s[i]) j++;
        pi[i] = j;
    }
    return pi;
}

vi get_parts(str& s, str& t) {
    str word = s + '#' + t;
    vi pi = pi_func(word);
    vi ans;
    int64_t n = s.size(), m = t.size();
    while (m > 0) {
        int64_t k = pi[n + m];
        if (k == 0) return {};
        ans.push_back(k);
        m -= k;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    str s, t;
    std::cin >> s >> t;
    vi ans = get_parts(s, t);
    if (ans.empty()) std::cout << "Yes\n";
    else {
        std::cout << "No\n";
        int64_t pos = 0;
        for (auto elem : ans) {
            if (pos > 0) std::cout << ' ';
            std::cout << t.substr(pos, elem);
            pos += elem;
        }
        std::cout << '\n';
    }
}
