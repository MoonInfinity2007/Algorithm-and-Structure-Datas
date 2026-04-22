#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<bool> vb;

void gen(int pos, int n, int& c, vi& a, vb& us) {
    if (c == 0) return;
    if (pos == n) {
        for (int i = 0; i < n; ++i) std::cout << a[i] << " ";
        std::cout << "\n";
        --c;
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (us[i]) continue;
        if (i == pos) continue;
        a[pos] = i + 1;
        us[i] = 1;
        gen(pos + 1, n, c, a, us);
        us[i] = false;
        if (c == 0) return;
    }
}

int main() {
    int n, t;
    std::cin >> n >> t;
    vi a(n);
    vb us(n);
    gen(0, n, t, a, us);
}
