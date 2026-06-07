#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <cstdint>
#include <queue>

using Event = std::pair<uint64_t, uint64_t>;

std::mt19937_64 rd(time(nullptr));

struct Node {
    uint64_t value_ = 0;
    uint64_t p = rd();
    Node* left = nullptr;
    Node* right = nullptr;
    Node(uint64_t value) : value_(value) {}
    ~Node() {
        delete left;
        delete right;
    }
};

class Treap {
private:
    Node* root = nullptr;
    Node* merge(Node* less, Node*more) {
        if (!less) return more;
        if (!more) return less;
        if (less->p > more->p) {
            less->right = merge(less->right, more);
            return less;
        }
        more->left = merge(less, more->left);
        return more;
    }

    std::pair<Node*, Node*> split(Node* tree, uint64_t key) {
        if (!tree) return {nullptr, nullptr};
        if (tree->value_ > key) {
            auto[less, more] = split(tree->left, key);
            tree->left = more;
            return {less, tree};
        }
        auto[less, more] = split(tree->right, key);
        tree->right = less;
        return {tree, more};
    }

    void print(Node * tree) {
        if (!tree) return;
        print(tree->left);
        std::cout << tree->value_ << " ";
        print(tree->right);
    }

    uint64_t hi(Node * tree) {
        if (!tree) return 0;
        return std::max(hi(tree->left), hi(tree->right)) + 1;
    }

public:
    void insert(uint64_t value) {
        auto[less, more] = split(root, value);
        root = merge(less, new Node(value));
        root = merge(root, more);
    }
    void erase(uint64_t value) {
        auto [less, ge] = split(root, value - 1);
        auto [equal, greater] = split(ge, value);
        delete equal;
        root = merge(less, greater);
    }
    uint64_t getMin() const {
        Node* cur = root;
        while (cur->left != nullptr) cur = cur->left;
        return cur->value_;
    }
    void print() {print(root);}
    uint64_t hi() {return hi(root);}
};

int main() {
    Treap t;
    uint64_t N = 30000, T = 10*60;
    for (uint64_t i = 1; i <= N; ++i) t.insert(i);
    std::vector<uint64_t> v(N + 1, 0); 
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
    uint64_t time;
    char type;
    while (std::cin >> time >> type) {
        while (!pq.empty() && pq.top().first <= time) {
            uint64_t bl = pq.top().second;
            uint64_t old = pq.top().first;
            pq.pop();
            if (v[bl] == old) {
                v[bl] = 0;
                t.insert(bl);
            }
        }
        if (type == '+') {
            uint64_t bl = t.getMin();
            t.erase(bl);
            v[bl] = time + T;
            pq.push({v[bl], bl});
            std::cout << bl << '\n';
        } else {
            uint64_t bl;
            std::cin >> bl;
            if (v[bl] > time) {
                v[bl] = time + T;
                pq.push({v[bl], bl});
                std::cout << "+\n";
            } else std::cout << "-\n";
        }
    }
}