#include <iostream>
#include <cstdint>
#include <iomanip>
#define ld long double

struct Data {
    uint64_t len = 0;
    ld pref1 = 0;
    ld pref2 = 0;
    ld suff1 = 0;
    ld suff2 = 0;
    ld best = -1e30;
};

Data merge(Data& left, Data& right) {
    if (left.len == 0) return right;
    if (right.len == 0) return left;
    Data res;
    res.len = left.len + right.len;
    res.pref1 = left.pref1;
    if (left.len >= 2) res.pref2 = left.pref2;
    else res.pref2 = left.pref1 + right.pref1;
    res.suff1 = right.suff1;
    if (right.len >= 2) res.suff2 = right.suff2;
    else res.suff2 = left.suff1 + right.suff1;
    res.best = std::max(left.best, right.best);
    res.best = std::max(res.best, (left.suff1 + right.pref1) / 2.0);
    if (left.len >= 2) res.best = std::max(res.best, (left.suff2 + right.pref1) / 3.0);
    if (right.len >= 2) res.best = std::max(res.best, (left.suff1 + right.pref2) / 3.0);
    return res;
}


struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    uint64_t begin = 0, end = 0;
    Data data;
    ld lazy = 0;
    Node(uint64_t begin, uint64_t end): begin(begin), end(end) {
        data.len = end - begin;
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

    void upd(Node* node, int64_t value) {
        if (node == nullptr) return;
        node->data.pref1 += value;
        node->data.suff1 += value;
        if (node->data.len >= 2) {
            node->data.pref2 += 2.0 * value;
            node->data.suff2 += 2.0 * value;
            node->data.best += value;
        }
        node->lazy += value;
    }

    void push(Node* node) {
        if (node == nullptr) return;
        if (node->lazy != 0) {
            upd(node->left, node->lazy);
            upd(node->right, node->lazy);
        } 
        node->lazy = 0;
    }

    void pull(Node* node) {
        if (node == nullptr) return;
        if (node->left == nullptr) return;
        node->data = merge(node->left->data, node->right->data);
    }

    void set(Node*& node, uint64_t index, ld value) {
        push(node);
        if (node->begin + 1 == node->end) {
            node->data.len = 1;
            node->data.pref1 = value;
            node->data.suff1 = value;
            node->data.pref2 = 0;
            node->data.suff2 = 0;
            node->data.best = -1e30;
            node->lazy = 0;
            return;
        }
        if (node->left->end > index) set(node->left, index, value);
        else set(node->right, index, value);
        pull(node);
    }

    Data get(Node*& node, uint64_t q_begin, uint64_t q_end) {
        push(node);
        if (q_begin <= node->begin && node->end <= q_end) return node->data;
        if (q_end <= node->begin || node->end <= q_begin) return Data();
        push(node);
        Data left = get(node->left, q_begin, q_end);
        Data right = get(node->right, q_begin, q_end);
        return merge(left, right);
    }

    void add(Node*& node, uint64_t q_begin, uint64_t q_end, int64_t value) {
        push(node);
        if (q_begin <= node->begin && q_end >= node->end) {
            upd(node, value);
            return;
        }
        if (q_end <= node->begin || q_begin >= node->end) return;
        add(node->left, q_begin, q_end, value);
        add(node->right, q_begin, q_end, value);
        pull(node);
    }

public:
    Tree(uint64_t begin, uint64_t end){root = new Node(begin, end);};
    void set(uint64_t index, ld value) {set(root, index, value);}
    Data get(uint64_t q_begin, uint64_t q_end) {return get(root, q_begin, q_end);}
    void add(uint64_t q_begin, uint64_t q_end, ld value) {add(root, q_begin, q_end, value);}
};

int main() {
    int64_t n, q;
    std::cin >> n >> q;
    Tree tree(1, n + 1);
    for (int64_t i = 0; i < n; ++i) {
        int64_t x;
        std::cin >> x;
        tree.set(i + 1, x);
    }
    std::cout << std::fixed << std::setprecision(6);
    while (q--) {
        int64_t ty, l, r, x;
        std::cin >> ty >> l >> r;
        if (ty - 1) std::cout << tree.get(l, r + 1).best << "\n";
        else {
            std::cin >> x;
            tree.add(l, r + 1, x);
        }
    }
}