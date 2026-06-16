#include <iostream>
#include <cstdint>
#include <vector>

typedef std::vector<int64_t> vi;

bool foo(int64_t v, vi& k, vi& l, vi& r, vi& hi) {
    if (v == -1) return;
    foo(l[v], k, l, r, hi);
    foo(r[v], k, l, r, hi);
    if (l[v] == -1 && r[v] == -1) {
        hi[v] = 0;
        return;
    }
    if (l[v] == -1) {
        hi[v] = hi[r[v]] + 1;
        return;
    }
    if (r[v] == -1) {
        hi[v] = hi[l[v]] + 1;
        return;
    }
    hi[v] = std::max(hi[l[v]], hi[r[v]]) + 1;
}

int main() {
    int64_t n;
    std::cin >> n;
    std::vector<int64_t> key(n, 0), left(n, 0), right(n, 0), hi(n, 0);
    for (int64_t i = 0; i < n; ++i) std::cin >> key[i] >> left[i] >> right[i];
    for (int64_t i = 0; i < n; ++i) {
        foo(i, key, left, right, hi);
        if (std::abs(hi[left[i]] - hi[right[i]]) > 1) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
}