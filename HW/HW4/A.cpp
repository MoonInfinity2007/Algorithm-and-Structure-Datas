#include <iostream>
#include <cstdint>

struct Node {
    int64_t value = 0;
    uint64_t begin = 0, end = 0;
    int64_t lazy = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(uint64_t begin, uint64_t end) : begin(begin), end(end) {
        if (begin + 1 < end) {
            uint64_t mid = (begin + end) / 2;
            left = new Node(begin, mid);
            right = new Node(mid, end);
        }
    }
    ~Node() {
        delete left;
        delete right;
    }
}; 

class SegmentTree{
    Node* root = nullptr;

    void set_alot(Node*& node, uint64_t q_begin, uint64_t q_end, int64_t value) {
        if (q_begin <= node->begin && q_end >= node->end) {
            node->lazy = std::max(node->lazy, value);
            return;
        }
        if (q_begin >= node->end || q_end <= node->begin) return;
        set_alot(node->left, q_begin, q_end, value);
        set_alot(node->right, q_begin, q_end, value);
    }

    int64_t get(Node*& node, uint64_t index) {
        if (node->begin + 1 == node->end) return std::max(node->value, node->lazy);
        if (node->left->end > index) return std::max(node->lazy, get(node->left, index));
        return std::max(node->lazy, get(node->right, index));
    }

public:
    SegmentTree(uint64_t begin, uint64_t end){root = new Node(begin, end);};
    void set_alot(uint64_t q_begin, uint64_t q_end, int64_t value) {set_alot(root, q_begin, q_end, value);}
    int64_t get(uint64_t index) {return get(root, index);}
};

int main() {
    uint64_t N, M;
    std::cin >> N >> M;
    SegmentTree tree(0, N);
    for (uint64_t i = 0; i < M; ++i) {
        uint64_t type;
        std::cin >> type;
        if (!(type - 1)) {
            uint64_t l, r;
            int64_t v;
            std::cin >> l >> r >> v;
            tree.set_alot(l, r, v);
        } else {
            uint64_t l;
            std::cin >> l;
            std::cout << tree.get(l) << "\n";
        }
    }
}