#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

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

str inverse_pi(vi& pi, int64_t m) {
    int64_t n = pi.size();
    if (pi[0] != 0) return "";
    for (int64_t i = 1; i < n; ++i) {
        if (pi[i] < 0 || pi[i] > pi[i - 1] + 1) return "";
    }
    str s(n, 'a');
    for (int64_t i = 1; i < n; ++i) {
        if (pi[i] > 0) s[i] = s[pi[i] - 1];
        else {
            std::vector<bool> used(m);
            used[0] = true;
            int64_t j = pi[i - 1];
            while (j > 0) {
                used[s[j] - 'a'] = true;
                j = pi[j - 1];
            }
            int64_t c = 0;
            while (c < m && used[c]) ++c;
            if (c == m) return "";
            s[i] = 'a' + c;
        }
    }
    if (pi_func(s) != pi) return "";
    return s;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n, m;
    while (std::cin >> n >> m) {
        vi pi(n);
        for (int64_t i = 0; i < n; ++i) std::cin >> pi[i];
        str s = inverse_pi(pi, m);
        if (s.empty()) std::cout << "NO\n";
        else std::cout << "YES\n" << s << '\n';
    }
}
