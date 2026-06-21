#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <cstdint>
#include <string>
#include <cstdio>

std::mt19937_64 rd(time(nullptr));

struct Node {
    int64_t value = 0;
    int64_t sum = 0;
    uint64_t p = rd();
    int64_t size = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int64_t value) : value(value), sum(value) {}
};

int64_t size(Node* tree) {return tree ? tree->size : 0;}
int64_t sum(Node* tree) {return tree ? tree->sum : 0;}

void update(Node* tree) {
    if (!tree) return;
    tree->size = size(tree->left) + size(tree->right) + 1;
    tree->sum = sum(tree->left) + sum(tree->right) + tree->value;
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

void insert(Node*& root, uint64_t index, int64_t value) {
    auto [less, more] = split(root, index);
    root = merge(merge(less, new Node(value)), more);
}

int64_t get_sum(Node*& root, int64_t l, int64_t r) {
    if (l > r) return 0;
    auto [a, b] = split(root, l - 1);
    auto [middle, c] = split(b, r - l + 1);
    int64_t ans = sum(middle);
    root = merge(merge(a, middle), c);
    return ans;
}

void swap_segments(Node*& first_root, int64_t first_l, int64_t first_r, Node*& second_root, int64_t second_l, int64_t second_r) {
    auto [a1, b1] = split(first_root, first_l - 1);
    auto [middle1, c1] = split(b1, first_r - first_l + 1);
    auto [a2, b2] = split(second_root, second_l - 1);
    auto [middle2, c2] = split(b2, second_r - second_l + 1);
    first_root = merge(merge(a1, middle2), c1);
    second_root = merge(merge(a2, middle1), c2);
}

void clear(Node* tree) {
    if (!tree) return;
    clear(tree->left);
    clear(tree->right);
    delete tree;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t test = 1;
    while (true) {
        int64_t n, m;
        std::cin >> n >> m;
        if (n == 0 && m == 0) break;
        Node* odd_root = nullptr;
        Node* even_root = nullptr;
        for (int64_t i = 1; i <= n; ++i) {
            int64_t x;
            std::cin >> x;
            if (i % 2 == 1) insert(odd_root, size(odd_root), x);
            else insert(even_root, size(even_root), x);
        }
        if (test > 1) std::cout << '\n';
        std::cout << "Swapper " << test << ":\n";
        for (int64_t q = 0; q < m; ++q) {
            int64_t type, x, y;
            std::cin >> type >> x >> y;
            if (type == 1) {
                if (x % 2 == 1) {
                    int64_t l = (x + 1) / 2;
                    int64_t r = y / 2;
                    swap_segments(odd_root, l, r, even_root, l, r);
                } else {
                    int64_t even_l = x / 2;
                    int64_t even_r = (y - 1) / 2;
                    int64_t odd_l = x / 2 + 1;
                    int64_t odd_r = (y + 1) / 2;
                    swap_segments(even_root, even_l, even_r, odd_root, odd_l, odd_r);
                }
            } else {
                int64_t a = x;
                int64_t b = y;
                int64_t ans = 0;
                int64_t first_odd = (a % 2 == 1 ? a : a + 1);
                int64_t last_odd = (b % 2 == 1 ? b : b - 1);
                if (first_odd <= last_odd) {
                    int64_t l = (first_odd + 1) / 2;
                    int64_t r = (last_odd + 1) / 2;
                    ans += get_sum(odd_root, l, r);
                }
                int64_t first_even = (a % 2 == 0 ? a : a + 1);
                int64_t last_even = (b % 2 == 0 ? b : b - 1);
                if (first_even <= last_even) {
                    int64_t l = first_even / 2;
                    int64_t r = last_even / 2;
                    ans += get_sum(even_root, l, r);
                }
                std::cout << ans << '\n';
            }
        }
        clear(odd_root);
        clear(even_root);
        ++test;
    }
    return 0;
}