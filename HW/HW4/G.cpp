#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

struct Query {
    int64_t deleted = 0;
    int64_t l = 0;
    int64_t id = 0;
};

class Tree {
    std::vector<int64_t> tree;
    int64_t n = 0;
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
    int64_t get(int64_t index) {
        int64_t ans = 0;
        while (index > 0) {
            ans += tree[index];
            index -= index & -index;
        }

        return ans;
    }
    int64_t lower_bound(int64_t value) {
        int64_t pos = 0;
        int64_t step = 1;
        while (step * 2 <= n) step *= 2;
        while (step > 0) {
            if (pos + step <= n && tree[pos + step] < value) {
                value -= tree[pos + step];
                pos += step;
            }
            step /= 2;
        }
        return pos + 1;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string x;
    std::cin >> x;
    int64_t n = x.size();
    std::vector<int64_t> st;
    std::vector<int64_t> deleted_order;
    for (int64_t i = 1; i <= n; ++i) {
        while (!st.empty() && x[st.back() - 1] < x[i - 1]) {
            deleted_order.push_back(st.back());
            st.pop_back();
        }
        st.push_back(i);
    }
    while (!st.empty()) {
        deleted_order.push_back(st.back());
        st.pop_back();
    }
    int64_t m;
    std::cin >> m;
    std::vector<Query> queries(m);
    for (int64_t i = 0; i < m; ++i) {
        int64_t k, l;
        std::cin >> k >> l;
        queries[i].deleted = n - k;
        queries[i].l = l;
        queries[i].id = i;
    }
    std::sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {return a.deleted < b.deleted;});
    Tree tree(n);
    for (int64_t i = 1; i <= n; ++i) tree.add(i, 1);
    std::string answer(m, '0');
    int64_t cur_deleted = 0;
    for (Query q : queries) {
        while (cur_deleted < q.deleted) {
            int64_t pos = deleted_order[cur_deleted];
            tree.add(pos, -1);
            ++cur_deleted;
        }
        int64_t pos = tree.lower_bound(q.l);
        answer[q.id] = x[pos - 1];
    }
    std::cout << answer << '\n';

    return 0;
}