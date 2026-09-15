#include <iostream>
#include <cstdint>
#include <vector>

typedef std::vector<int64_t> vi;
int64_t n;

int64_t fix(int64_t x) {return x == -1 ? n : x;}

bool foo(int64_t v, vi& k, vi& l, vi& r, vi& s) {
    if (v == -1) return 1;
    if (l[v] != -1 && k[v] <= k[l[v]]) return 0;
    if (r[v] != -1 && k[v] >= k[r[v]]) return 0;
    if (s[v] != s[fix(l[v])] + s[fix(r[v])] + 1) return 0;
    return foo(l[v], k, l, r, s) && foo(r[v], k, l, r, s);
}

int main() {
    std::cin >> n;
    std::vector<int64_t> key(n + 1, 0), left(n, 0), right(n, 0), size(n + 1, 0);
    for (int64_t i = 0; i < n; ++i) {
        std::cin >> key[i] >> left[i] >> right[i] >> size[i];
    }
    if (foo(0, key, left, right, size)) std::cout << "YES";
    else std::cout << "NO";
}