#include <iostream>
#include <cstdint>
#include <vector>

struct Node {
    int64_t value = 0;
    uint64_t begin = 0, end = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(uint64_t begin, uint64_t end, uint64_t value):begin(begin), end(end), value(value) {
        if (begin + 1 < end) {
            uint64_t mid = (begin + end) / 2;
            left = new Node(begin, mid, value);
            right = new Node(mid, end, value);
        }
    }
    ~Node() {
        delete left;
        delete right;
    }
};

class SegmentTree {
    Node* root = nullptr;
    int64_t get(Node*& node, uint64_t value) {
        if (node->begin + 1 == node->end) {
            node->value -= value;
            return node->begin;
        }
        uint64_t ans;
        if (node->left->value >= value) ans = get(node->left, value);
        else ans = get(node->right, value);
        node->value = std::max(node->left->value, node->right->value);
        return ans;
    }
    public:
    SegmentTree(uint64_t begin, uint64_t end, uint64_t value) {root = new Node(begin, end, value);}
    int64_t get(uint64_t value) {
        if (root->value < value) return -1; 
        int64_t ans = get(root, value);
        return ans;
    }
};

int main() {
    uint64_t H, W, N;
    std::cin >> H >> W >> N;
    SegmentTree tree(1, std::min(H, N) + 1, W);
    N++;
    while (--N) {
        uint64_t x;
        std::cin >> x;
        std::cout << tree.get(x) << "\n";
    }
}