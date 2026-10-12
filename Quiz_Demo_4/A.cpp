#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

typedef std::vector<int64_t> vi;
typedef std::string str;

vi z_func(str& t, str& p) {
    str s = p + "$" + t;
    int64_t n = s.size();
    vi z(n, 0);
    int64_t l = 0, r = -1;
    for (int64_t i = 1; i < n; i++) {
        if (i < r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::string s, p;
    std::cin >> s >> p;
    vi ans(3);
    vi z1 = z_func(s, p);
    for (auto elem : z1) {
        if (elem == p.size()) ans[0]++;
    }
    p.pop_back();
    vi z2 = z_func(s, p);
    for (auto elem : z2) {
        if (elem == p.size()) ans[1]++;
    }
    p.pop_back();
    vi z3 = z_func(s, p);
    for (auto elem : z3) {
        if (elem == p.size()) ans[2]++;
    }
    for (auto elem : ans) std::cout << elem << " ";
}