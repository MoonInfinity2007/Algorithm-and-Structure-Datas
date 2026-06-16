#include <iostream>
#include <cstdint>

struct Node {
    int64_t value = 0;
    uint64_t begin = 0, end = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(uint64_t begin, uint64_t end):begin(begin), end(end) {
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

class SegmentTree {
    Node* root = nullptr;
    void set(Node*& node, uint64_t index, int64_t value) {
        if (node->begin + 1 == node->end) {
            node->value = value;
            return;
        }
        if (node->left->end > index) set(node->left, index, value);
        else set(node->right, index, value);
        node->value = std::max(node->left->value, node->right->value);
    }

    int64_t get(Node*& node, uint64_t q_begin, uint64_t q_end) {
        if (node->begin >= q_begin && node->end <= q_end) return node->value;
        if (node->begin >= q_end || node->end <= q_begin) return 0;
        return std::max(get(node->left, q_begin, q_end), get(node->right, q_begin, q_end));
    }
public:
    SegmentTree(uint64_t begin, uint64_t end) {root = new Node(begin, end);}
    void set(uint64_t index, int64_t value) {set(root, index, value);}
    int64_t get(uint64_t begin, uint64_t end) {return get(root, begin, end);}
};


int main() {
    uint64_t N;
    std::cin >> N;
    SegmentTree tree(1, N + 1);
    for (uint64_t i = 1; i <= N; ++i) {
        int64_t x;
        std::cin >> x;
        tree.set(i, x);
    }
    int64_t K;
    std::cin >> K;
    while (K--) {
        uint64_t l, r;
        std::cin >> l >> r;
        std::cout << tree.get(l, r + 1) << " ";
    }
}