#include <iostream>
#include <vector>
#include <cstdint>

typedef std::vector<int64_t> vi;

class Tree {
    vi tree, arr;
    uint64_t sz = 1;
    
    void build(uint64_t v, uint64_t left, uint64_t right) {
        if (left + 1 == right) tree[v] = left < arr.size() ? arr[left] : 0;
        else {
            uint64_t mid = (left + right) / 2;
            build(2 * v + 1, left, mid);
            build(2 * v + 2, mid, right);
            tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
        }
    }

    int64_t get(uint64_t v, uint64_t left, uint64_t right, uint64_t q_left, uint64_t q_right) {
        if (q_left <= left && right <= q_right) return tree[v];
        if (q_right <= left || right <= q_left) return 0;
        uint64_t mid = (left + right) >> 1;
        return get(2 * v + 1, 0, sz, q_left, q_right) + get(2 * v + 2, 0, sz, q_left, q_right);
    }

public:
    explicit Tree(const std::vector<int64_t>& arr) : arr(arr) {
        while (sz < arr.size()) sz <<= 1;
        tree.resize(2 * sz - 1);
    };
};

int main() {
    return 0;
}