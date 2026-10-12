#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<int64_t> vi;
typedef std::string str;

vi pi_func(str& s)  {
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

vi kmp(str& t, str& p) {
    int64_t n = t.size();
    vi pi = pi_func(p);
    vi ans = {};
    int64_t j = 0;
    for (int64_t i = 0; i < n; i++) {
        while (j > 0 && t[i] != p[j]) j = pi[j - 1];
        if (t[i] == p[j]) j++; 
        if (j == p.size()) {
            j = pi[j - 1];
            ans.push_back(i - p.size() + 1);
        }
    }
    return ans;
}

int main() {
    str t, p;
    std::cin >> p >> t;
    vi ans = kmp(t, p);
    std::cout << ans.size() << "\n";
    for (auto elem : ans) std::cout << elem << " ";
}