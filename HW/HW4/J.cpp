#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

struct Query {
    int64_t limit = 0;
    int64_t left = 0;
    int64_t right = 0;
    int64_t id = 0;
    int64_t sign = 0;
};

class Tree {
    std::vector<int64_t> tree;
    int64_t n = 0;
    int64_t get_prefix(int64_t index) {
        int64_t ans = 0;
        while (index > 0) {
            ans += tree[index];
            index -= index & -index;
        }
        return ans;
    }
public:
    Tree(int64_t size) {
        n = size;
        tree.assign(n + 1, 0);
    }
    void add(int64_t index, int64_t value) {
        while (index <= n) {
            tree[index] += value;
            index += index & -index;
        }
    }
    int64_t get(int64_t q_begin, int64_t q_end) {return get_prefix(q_end - 1) - get_prefix(q_begin - 1);}
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t N, M;
    std::cin >> N >> M;
    std::vector<int64_t> pos(N + 1);
    for (int64_t i = 1; i <= N; ++i) {
        int64_t x;
        std::cin >> x;
        pos[x] = i;
    }
    std::vector<Query> queries;
    for (int64_t i = 0; i < M; ++i) {
        int64_t x, y, k, l;
        std::cin >> x >> y >> k >> l;
        queries.push_back({l, x, y, i, 1});
        queries.push_back({k - 1, x, y, i, -1});
    }
    std::sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {return a.limit < b.limit;});
    Tree tree(N);
    std::vector<int64_t> answer(M, 0);
    int64_t current = 0;
    for (Query q : queries) {
        while (current < q.limit) {
            ++current;
            tree.add(pos[current], 1);
        }
        answer[q.id] += q.sign * tree.get(q.left, q.right + 1);
    }
    for (int64_t i = 0; i < M; ++i) std::cout << answer[i] << '\n';
    return 0;
}