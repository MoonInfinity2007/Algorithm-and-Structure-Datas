#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

typedef std::vector<int64_t> vi;

vi z_function(vi& s) {
    int64_t n = s.size();
    vi z(n, 0);
    z[0] = n;
    int64_t l = 0, r = 0;
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

vi pi_to_z(vi& pi) {
    int64_t n = pi.size();
    vi s(n, 0);
    for (int64_t i = 1; i < n; ++i) {
        if (pi[i] > 0) s[i] = s[pi[i] - 1];
        else s[i] = i;
    }
    return z_function(s);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n;
    std::cin >> n;
    vi pi(n);
    for (int64_t i = 0; i < n; ++i) std::cin >> pi[i];
    vi z = pi_to_z(pi);
    for (auto elem : z) std::cout << elem << ' ';
    std::cout << '\n';
}
