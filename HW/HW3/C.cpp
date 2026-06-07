#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <cstdint>
#include <algorithm>

std::mt19937_64 rd(time(nullptr));

struct Node {
    int64_t l = 0;
    int64_t r = 0;
    uint64_t p = rd();
    int64_t maxLen = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int64_t l, int64_t r) : l(l), r(r), maxLen(r - l + 1) {}
    ~Node() {
        delete left;
        delete right;
    }
};

int64_t len(Node* tree) {
    if (!tree) return 0;
    return tree->r - tree->l + 1;
}

int64_t maxLen(Node* tree) {
    if (!tree) return 0;
    return tree->maxLen;
}

void update(Node* tree) {
    if (!tree) return;
    tree->maxLen = std::max({len(tree), maxLen(tree->left), maxLen(tree->right)});
}

class Treap {
private:
    Node* root = nullptr;
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

    std::pair<Node*, Node*> split(Node* tree, int64_t key) {
        if (!tree) return {nullptr, nullptr};
        if (tree->l > key) {
            auto [less, more] = split(tree->left, key);
            tree->left = more;
            update(tree);
            return {less, tree};
        }
        auto [less, more] = split(tree->right, key);
        tree->right = less;
        update(tree);
        return {tree, more};
    }

    Node* erase(Node* tree, int64_t key) {
        auto [less, tmp] = split(tree, key - 1);
        auto [equal, more] = split(tmp, key);
        if (equal) {
            equal->left = nullptr;
            equal->right = nullptr;
            delete equal;
        }
        return merge(less, more);
    }

    Node* findFirst(Node* tree, int64_t k) {
        if (!tree || maxLen(tree) < k) return nullptr;
        if (maxLen(tree->left) >= k) return findFirst(tree->left, k);
        if (len(tree) >= k) return tree;
        return findFirst(tree->right, k);
    }

    Node* prevNode(Node* tree, int64_t key) {
        Node* ans = nullptr;
        while (tree) {
            if (tree->l < key) {
                ans = tree;
                tree = tree->right;
            } else tree = tree->left;
        }
        return ans;
    }

    Node* nextNode(Node* tree, int64_t key) {
        Node* ans = nullptr;
        while (tree) {
            if (tree->l > key) {
                ans = tree;
                tree = tree->left;
            } else tree = tree->right;
        }
        return ans;
    }
public:
    Treap(int64_t n) {root = new Node(1, n);}
    ~Treap() {delete root;}

    void insert(int64_t l, int64_t r) {
        auto [less, more] = split(root, l);
        root = merge(merge(less, new Node(l, r)), more);
    }
    void erase(int64_t l) {root = erase(root, l);}
    int64_t allocate(int64_t k) {
        Node* place = findFirst(root, k);
        if (!place) return -1;
        int64_t oldL = place->l;
        int64_t oldR = place->r;
        int64_t answer = oldL;
        int64_t newL = oldL + k;
        erase(oldL);
        if (newL <= oldR) insert(newL, oldR);
        return answer;
    }
    void freeSegment(int64_t l, int64_t r) {
        Node* left = prevNode(root, l);
        Node* right = nextNode(root, l);
        if (left && left->r + 1 == l) {
            l = left->l;
            erase(left->l);
        }
        if (right && r + 1 == right->l) {
            r = right->r;
            erase(right->l);
        }
        insert(l, r);
    }
};

struct Segment {
    int64_t l = -1;
    int64_t r = -1;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t N;
    int64_t M;
    std::cin >> N >> M;
    Treap memory(N);
    std::vector<Segment> req(M + 1);
    for (int64_t i = 1; i <= M; ++i) {
        int64_t x;
        std::cin >> x;
        if (x > 0) {
            int64_t k = x;
            int64_t start = memory.allocate(k);
            std::cout << start << '\n';
            if (start != -1) req[i] = {start, start + k - 1};
        } else {
            int64_t t = -x;
            if (req[t].l == -1) continue;
            memory.freeSegment(req[t].l, req[t].r);
        }
    }
    return 0;
}