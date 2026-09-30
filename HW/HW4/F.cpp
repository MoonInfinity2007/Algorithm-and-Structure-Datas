#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>

struct Operation {int64_t l = 0, r = 0, x = 0, y = 0;};

class Fenwick {
    std::vector<int64_t> tree;
    int64_t n = 0;
public:
    Fenwick(int64_t n = 0) {
        init(n);
    }
    void init(int64_t size) {
        n = size;
        tree.assign(n + 2, 0);
    }
    void add(int64_t index, int64_t value) {
        while (index <= n) {
            tree[index] += value;
            index += index & -index;
        }
    }
    int64_t get(int64_t index) {
        int64_t res = 0;
        while (index > 0) {
            res += tree[index];
            index -= index & -index;
        }
        return res;
    }
};

int main() {
    freopen("jam.in", "r", stdin);
    freopen("jam.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t N;
    std::cin >> N;
    std::vector<int64_t> a(N + 1);
    std::vector<int64_t> b(N + 1);
    for (int64_t i = 1; i <= N; ++i) std::cin >> a[i];
    for (int64_t i = 1; i <= N; ++i) std::cin >> b[i];
    int64_t M;
    std::cin >> M;
    std::vector<Operation> op(M + 1);
    for (int64_t i = 1; i <= M; ++i) std::cin >> op[i].l >> op[i].r >> op[i].x >> op[i].y;
    std::vector<int64_t> left(N + 1);
    std::vector<int64_t> right(N + 1);
    for (int64_t i = 1; i <= N; ++i) {
        if (a[i] >= b[i]) {
            left[i] = 0;
            right[i] = 0;
        } else {
            left[i] = 1;
            right[i] = M + 1;
        }
    }
    bool flag = true;
    while (flag) {
        flag = false;
        std::vector<std::vector<int64_t>> bucket(M + 2);
        for (int64_t i = 1; i <= N; ++i) {
            if (left[i] == 0 && right[i] == 0) continue;
            if (left[i] < right[i]) {
                flag = true;
                int64_t mid = (left[i] + right[i]) / 2;
                bucket[mid].push_back(i);
            }
        }
        if (!flag) break;
        Fenwick bitA(N + 2);
        Fenwick bitB(N + 2);
        for (int64_t i = 1; i <= M; ++i) {
            int64_t A = op[i].y;
            int64_t B = op[i].x - op[i].y * op[i].l;
            bitA.add(op[i].l, A);
            bitA.add(op[i].r + 1, -A);
            bitB.add(op[i].l, B);
            bitB.add(op[i].r + 1, -B);
            for (int64_t id : bucket[i]) {
                int64_t add = bitA.get(id) * id + bitB.get(id);
                int64_t cur = a[id] + add;
                if (cur >= b[id]) right[id] = i;
                else left[id] = i + 1;
            }
        }
    }
    for (int64_t i = 1; i <= N; ++i) {
        if (a[i] >= b[i]) std::cout << 0;
        else if (left[i] == M + 1) std::cout << -1;
        else std::cout << left[i];
        if (i < N) std::cout << ' ';
    }
    std::cout << '\n';

    return 0;
}