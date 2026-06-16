#include <iostream>
#include <cstdint>
#include <vector>

typedef std::vector<int64_t> vi;
int64_t n;

int64_t fix(int64_t x) {return x == -1 ? n : x;}

bool foo(int64_t v, vi& k, vi& l, vi& r, vi& hi) {
    if (v == -1) return 1;
    bool c1 = foo(l[v], k, l, r, hi);
    bool c2 = foo(r[v], k, l, r, hi);
    hi[v] = std::max(hi[fix(l[v])], hi[fix(r[v])]) + 1;
    if (std::abs(hi[fix(l[v])] - hi[fix(r[v])]) > 1) return 0;
    return c1 & c2;
}

int main() {
    std::cin >> n;
    std::vector<int64_t> key(n, 0), left(n, 0), right(n, 0), hi(n + 1, 0);
    for (int64_t i = 0; i < n; ++i) std::cin >> key[i] >> left[i] >> right[i];
    if (foo(0, key, left, right, hi)) std::cout << "YES";
    else std::cout << "NO";
}