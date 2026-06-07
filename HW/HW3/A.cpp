#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <cstdint>

std::mt19937_64 rd(time(nullptr));

struct Key {
    int64_t delta;
    int id;
    bool operator<(const Key& other) const {
        if (delta != other.delta) return delta < other.delta;
        return id < other.id;
    }
    bool operator==(const Key& other) const {
        return delta == other.delta && id == other.id;
    }
};

struct Node {
    Key key;
    uint64_t p = rd();
    int64_t size = 1;
    int64_t sum = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(Key key) : key(key), sum(key.delta) {}
    ~Node() {
        delete left;
        delete right;
    }
};

int64_t size(Node* tree) {return tree ? tree->size : 0;}
int64_t sum(Node* tree) {return tree ? tree->sum : 0;}

void update(Node* tree) {
    if (!tree) return;
    tree->size = size(tree->left) + size(tree->right) + 1;
    tree->sum = sum(tree->left) + sum(tree->right) + tree->key.delta;
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

    std::pair<Node*, Node*> split(Node* tree, Key key) {
        if (!tree) return {nullptr, nullptr};
        if (tree->key < key) {
            auto [less, more] = split(tree->right, key);
            tree->right = less;
            update(tree);
            return {tree, more};
        }
        auto [less, more] = split(tree->left, key);
        tree->left = more;
        update(tree);
        return {less, tree};
    }

    int64_t sumLargest(Node* tree, int64_t k) const {
        if (!tree || k <= 0) return 0;
        if (k >= size(tree)) return sum(tree);
        int64_t rightSize = size(tree->right);
        if (rightSize >= k) return sumLargest(tree->right, k);
        if (rightSize + 1 == k) return sum(tree->right) + tree->key.delta;
        return sum(tree->right) + tree->key.delta + sumLargest(tree->left, k - rightSize - 1);
    }

public:
    void insert(Key key) {
        auto [less, more] = split(root, key);
        root = merge(merge(less, new Node(key)), more);
    }

    void erase(Key key) {
        auto [less, ge] = split(root, key);
        Key nextKey{key.delta, key.id + 1};
        auto [equal, greater] = split(ge, nextKey);
        delete equal;
        root = merge(less, greater);
    }

    int64_t sumLargest(int64_t k) const {return sumLargest(root, k);}

    ~Treap() {delete root;}
};

struct Passenger {
    int64_t a, b, c, d;
    int64_t delta;
};

int main() {
    int N, M, P;
    std::cin >> N >> M >> P;
    std::vector<Passenger> pass(N);
    std::vector<std::vector<int>> add(P + 1), del(P + 1);
    for (int i = 0; i < N; ++i) {
        std::cin >> pass[i].a >> pass[i].b >> pass[i].c >> pass[i].d;
        pass[i].delta = pass[i].a - pass[i].b;
        add[pass[i].c].push_back(i);
        del[pass[i].d].push_back(i);
    }

    Treap tree;
    int64_t base = 0;
    int64_t ans = 0;
    for (int i = 1; i < P; ++i) {
        for (int id : del[i]) {
            base -= pass[id].b;
            if (pass[id].delta > 0) tree.erase({pass[id].delta, id});
        }
        for (int id : add[i]) {
            base += pass[id].b;
            if (pass[id].delta > 0) tree.insert({pass[id].delta, id});
        }
        ans += base + tree.sumLargest(M);
    }
    std::cout << ans;
}