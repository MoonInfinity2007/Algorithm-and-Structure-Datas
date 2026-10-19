#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <iomanip>

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

void mul_add(vi& a, int64_t n, int64_t value) {
    int64_t base = 1000000000;
    int64_t carry = value;
    int64_t m = a.size();
    for (int64_t i = 0; i < m; ++i) {
        int64_t cur = a[i] * n + carry;
        a[i] = cur % base;
        carry = cur / base;
    }
    if (carry > 0) a.push_back(carry);
}

vi get_time(str& s, int64_t n) {
    int64_t m = s.size();
    vi pi = pi_func(s);
    std::vector<bool> used(m + 1);
    for (int64_t j = m; j > 0; j = pi[j - 1]) used[j] = true;
    vi ans(1, 0);
    for (int64_t i = m; i >= 0; --i) mul_add(ans, n, used[i]);
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n;
    str s;
    std::cin >> n >> s;
    vi ans = get_time(s, n);
    int64_t m = ans.size();
    std::cout << ans.back();
    for (int64_t i = m - 2; i >= 0; --i) std::cout << std::setw(9) << std::setfill('0') << ans[i];
    std::cout << '\n';
}
