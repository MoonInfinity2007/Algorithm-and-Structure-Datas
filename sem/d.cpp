#include <cstdint>
#include <iostream>
#include <random>
#include <ctime>
#include <string>

std::mt19937 rd(time(nullptr));

struct Node {
    int64_t value = 0;
    uint32_t p = rd();
    int size = 1;
    Node *left = nullptr;
    Node *right = nullptr;
    explicit Node(int64_t value) : value(value) {}
} *root = nullptr;

int size(Node *tree) {
    return tree ? tree->size : 0;
}

void update(Node *tree) {
    if (!tree) return;
    tree->size = size(tree->left) + size(tree->right) + 1;
}

std::pair<Node *, Node *> split(Node *tree, int count) {
    if (!tree) return {nullptr, nullptr};
    if (size(tree->left) >= count) {
        auto [less, more] = split(tree->left, count);
        tree->left = more;
        update(tree);
        return {less, tree};
    }
    auto [less, more] = split(tree->right,
                              count - 1 - size(tree->left));
    tree->right = less;
    update(tree);
    return {tree, more};
}

Node *merge(Node *less, Node *more) {
    if (!less) return more;
    if (!more) return less;
    if (less->p > more->p) {
        less->right = merge(less->right, more);
        update(less);
        return less;
    }
    more->left = merge(less, more->left);
    update(more);
    return more;
}

void insert(int index, int64_t value) {
    auto [less, more] = split(root, index);
    root = merge(merge(less, new Node(value)), more);
}

void remove(int index) {
    auto [tmp, more] = split(root, index);
    auto [less, rem] = split(tmp, index - 1);
    root = merge(less, more);
}

void print(Node *tree) {
    if (!tree) return;
    print(tree->left);
    std::cout << tree->value << ' ';
    print(tree->right);
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    
    for (int i = 0; i < n; ++i) {
        int64_t x = 0;
        std::cin >> x;
        insert(i, x);
    }
    
    for (int q = 0; q < m; ++q) {
        std::string op;
        std::cin >> op;
        if (op == "add") {
            int index = 0;
            int64_t x = 0;
            std::cin >> index >> x;
            insert(index, x);
        } else if (op == "del") {
            int index = 0;
            std::cin >> index;
            remove(index);
        }
    }
    std::cout << size(root) << '\n';
    print(root);
    return 0;
}
