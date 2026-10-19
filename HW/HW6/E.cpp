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

std::vector<vi> get_automaton(str& s, int64_t a) {
    int64_t n = s.size();
    vi pi = pi_func(s);
    std::vector<vi> go(n, vi(a));
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t c = 0; c < a; ++c) {
            if (s[i] == 'a' + c) go[i][c] = i + 1;
            else if (i > 0) go[i][c] = go[pi[i - 1]][c];
        }
    }
    return go;
}

int64_t get_ans(str& s, int64_t a, int64_t k) {
    int64_t n = s.size();
    std::vector<vi> go = get_automaton(s, a);
    int64_t diff = 0;
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t c = 0; c < a; ++c) diff = std::max(diff, i - go[i][c]);
    }
    return n + k * diff;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n, a, k;
    str s;
    std::cin >> n >> a >> k >> s;
    std::cout << get_ans(s, a, k) << '\n';
}
