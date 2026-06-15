#include <iostream>
#include <cstdint>

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    uint64_t begin = 0, end = 0;
    int64_t value = 0;
    int64_t lazy = 0;
    Node(uint64_t begin, uint64_t end): begin(begin), end(end) {
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

class Tree {
    Node* root = nullptr;

    void set(Node*& node, uint64_t index, int64_t value) {
        if (node->begin + 1 == node->end) {
            node->value = value;
            return;
        }
        if (node->left->end > index) set(node->left, index, value);
        else set(node->right, index, value);
        node->value = node->left->value + node->right->value;
    }

    int64_t get(Node*& node, uint64_t q_begin, uint64_t q_end) {
        if (q_begin <= node->begin && node->end <= q_end) return node->value;
        if (q_end <= node->begin || node->end <= q_begin) return 0;
        return get(node->left, q_begin, q_end) + get(node->right, q_begin, q_end);
    }

public:
    Tree(uint64_t begin, uint64_t end){root = new Node(begin, end);};
    void set(uint64_t index, int64_t value) {set(root, index, value);}
    int64_t get(uint64_t q_begin, uint64_t q_end) {return get(root, q_begin, q_end);}
};

int main() {
    int64_t N, K;
    std::cin >> N >> K;
    Tree tree(1, N+1);
    for (int64_t i = 0; i < K; ++i) {
        char s;
        int64_t b = 1, e = 2;
        std::cin >> s >> b >> e;
        if (s == 'A') tree.set(b, e);
        else std::cout << tree.get(b, e + 1) << "\n";
    }   
    return 0;
}