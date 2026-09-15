#include <iostream>
#include <cstdint>

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int64_t begin = 0, end = 0, value = 0;
    Node(int64_t begin, int64_t end): begin(begin), end(end) {
        if (begin + 1 < end) {
            int64_t mid = (begin + end) / 2;
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
    void set(Node*& node, int64_t index, int64_t value) {
        if (node->begin + 1 == node->end) node->value = value;
        if (node->left->end > index) set(node->left, index, value);
        else set(node->right, index, value);
        node->value = node->left->value + node->right->value;
    }
    int64_t get(Node*& node, int64_t q_b, int64_t q_e) {
        if (node->begin >= q_b && node->end <= q_e) return node->value;
        if (node->begin >= q_e || node->end <= q_b) return 0;
        return get(node->left, q_b, q_e) + get(node->right, q_b, q_e);
    }
    public:
    Tree(int64_t begin, int64_t end) {root = new Node(begin, end);};
    void set(int64_t index, int64_t value) {set(root, index, value);};
    int64_t get(int64_t begin, int64_t end) {return get(root, begin, end);};
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