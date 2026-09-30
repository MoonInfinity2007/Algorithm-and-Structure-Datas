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
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int64_t value) : value(value) {}
} *root = nullptr;

int64_t size(Node* tree) {return tree ? tree->size : 0;}

void update(Node* tree) {
    if (!tree) return;
    tree->size = size(tree->left) + size(tree->right) + 1;
}

std::pair<Node*, Node*> split(Node* tree, int64_t count) {
    if (!tree) return {nullptr, nullptr};
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

void divide_company(uint64_t index, int64_t& ans) {
    auto [a, b] = split(root, index - 1);
    auto [mid, c] = split(b, 1);
    int64_t x = mid->value;
    int64_t left_part = x / 2;
    int64_t right_part = x - left_part;
    ans -= x*x;
    ans += left_part*left_part;
    ans += right_part*right_part;
    root = merge(merge(a, new Node(left_part)), merge(new Node(right_part), c));
}

void bankrupt_company(uint64_t index, int64_t& ans) {
    int64_t n = size(root);
    if (index == 1) {
        auto [mid, b] = split(root, 1);
        auto [next, c] = split(b, 1);
        int64_t x = mid->value;
        int64_t old_next = next->value;
        int64_t new_next = old_next + x;
        ans -= x*x;
        ans -= old_next*old_next;
        ans += new_next*new_next;
        next->value = new_next;
        update(next);
        root = merge(next, c);
        return;
    }
    if (index == n) {
        auto [a, b] = split(root, index - 2);
        auto [prev, c] = split(b, 1);
        auto [mid, d] = split(c, 1);
        int64_t x = mid->value;
        int64_t old_prev = prev->value;
        int64_t new_prev = old_prev + x;
        ans -= x*x;
        ans -= old_prev*old_prev;
        ans += new_prev*new_prev;
        prev->value = new_prev;
        update(prev);
        root = merge(merge(a, prev), d);
        return;
    }

    auto [a, b] = split(root, index - 2);
    auto [prev, c] = split(b, 1);
    auto [mid, d] = split(c, 1);
    auto [next, e] = split(d, 1);
    int64_t x = mid->value;
    int64_t add_left = x / 2;
    int64_t add_right = x - add_left;
    int64_t old_prev = prev->value;
    int64_t old_next = next->value;
    int64_t new_prev = old_prev + add_left;
    int64_t new_next = old_next + add_right;
    ans -= x*x;
    ans -= old_prev*old_prev;
    ans -= old_next*old_next;
    ans += new_prev*new_prev;
    ans += new_next*new_next;
    prev->value = new_prev;
    next->value = new_next;
    update(prev);
    update(next);
    root = merge(merge(a, prev), merge(next, e));
}

int main() {
    int64_t n = 0, p = 0;
    std::cin >> n >> p;
    int64_t ans = 0;
    for (int64_t i = 0; i < n; ++i) {
        int64_t x = 0;
        std::cin >> x;
        insert(i, x);
        ans += x*x;
    }
    int64_t k = 0;
    std::cin >> k;
    std::cout << ans;
    std::cout << '\n';
    for (int64_t q = 0; q < k; ++q) {
        int64_t e = 0;
        uint64_t v = 0;
        std::cin >> e >> v;
        if (e == 1) bankrupt_company(v, ans);
        else divide_company(v, ans);
        std::cout << ans;
        std::cout << '\n';
    }

    return 0;
}