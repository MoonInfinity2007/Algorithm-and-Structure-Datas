#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <cstdint>
#include <string>

std::mt19937_64 rd(time(nullptr));

struct Node {
    int64_t value = 0;
    uint64_t p = rd();
    int64_t size = 1;
    bool rev = false;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int64_t value) : value(value) {}
} *root = nullptr;

int64_t size(Node* tree) {return tree ? tree->size : 0;}

void update(Node* tree) {
    if (!tree) return;
    tree->size = size(tree->left) + size(tree->right) + 1;
}

void push(Node* tree) {
    if (!tree) return;
    if (tree->rev) {
        std::swap(tree->left, tree->right);
        if (tree->left) tree->left->rev ^= 1;
        if (tree->right) tree->right->rev ^= 1;
        tree->rev = false;
    }
}

std::pair<Node*, Node*> split(Node* tree, int64_t count) {
    if (!tree) return {nullptr, nullptr};
    push(tree);
    if (size(tree->left) >= count) {
        auto [less, more] = split(tree->left, count);
        tree->left = more;
        update(tree);
        return {less, tree};
    }
    auto [less, more] = split(tree->right, count - size(tree->left) - 1);
    tree->right = less;
    update(tree);
    return {tree, more};
}

Node* merge(Node* less, Node* more) {
    if (!less) return more;
    if (!more) return less;
    push(less);
    push(more);
    if (less->p > more->p) {
        less->right = merge(less->right, more);
        update(less);
        return less;
    }
    more->left = merge(less, more->left);
    update(more);
    return more;
}

void insert(uint64_t index, int64_t value) {
    auto [less, more] = split(root, index);
    root = merge(merge(less, new Node(value)), more);
}

void reverse_segment(uint64_t l, uint64_t r) {
    auto [a, b] = split(root, l - 1);
    auto [middle, c] = split(b, r - l + 1);
    if (middle) middle->rev ^= 1;
    root = merge(merge(a, middle), c);
}

void print(Node* tree) {
    if (!tree) return;
    push(tree);
    print(tree->left);
    std::cout << tree->value << " ";
    print(tree->right);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n = 0, m = 0;
    std::cin >> n >> m;
    for (int64_t i = 0; i < n; ++i) insert(i, i + 1);
    for (int64_t q = 0; q < m; ++q) {
        uint64_t l = 0, r = 0;
        std::cin >> l >> r;
        reverse_segment(l, r);
    }
    print(root);
    return 0;
}