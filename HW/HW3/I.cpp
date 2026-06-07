#include <iostream>
#include <cstdint>
#include <string>
#include <algorithm>

template<typename T>
class AVLTree {
    struct Node{
        T value_;
        uint64_t height = 1;
        uint64_t size = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(const T &value): value_(value) {}
        ~Node() {
            delete left;
            delete right;
        }
    } *root = nullptr;

    uint64_t height(Node* node) const {
        if (node == nullptr) return 0;
        return node->height;
    }

    uint64_t size(Node* node) const {return node ? node->size : 0;}

    void update(Node* node) {
        if (node != nullptr) {
            node->height = std::max(height(node->left), height(node->right)) + 1;
            node->size = size(node->left) + size(node->right) + 1;
        }
    }

    int64_t balanceFactor(Node* node) const {
        return height(node->right) - height(node->left);
    }

    void rotateLeft(Node*& node) {
        Node* right = node->right;
        node->right = right->left;
        right->left = node;
        update(node);
        update(right);
        node = right;
    }

    void rotateRight(Node*& node) {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        update(node);
        update(left);
        node = left;
    }

    void balance(Node*& node) {
        update(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->right) < 0) rotateRight(node->right);
            rotateLeft(node);
        } else if (balanceFactor(node) == -2) {
            if (balanceFactor(node->left) > 0) rotateLeft(node->left);
            rotateRight(node);
        }
    }
    
    bool find(Node* node, const T& value) const {
        if (node == nullptr) return false;
        if (node->value_ == value) return true;
        if (node->value_ > value) return find(node->left, value);
        if (node->value_ < value) return find(node->right, value);
    }

    Node* next(Node* node, const T& value) const {
        Node* ans = nullptr;
        while (node != nullptr) {
            if (node->value_ > value) {
                ans = node;
                node = node->left;
            } else node = node->right;
        }
        return ans;
    }

    Node* prev(Node* node, const T& value) const {
        Node* ans = nullptr;
        while (node != nullptr) {
            if (node->value_ < value) {
                ans = node;
                node = node->right;
            } else node = node->left;
        }
        return ans;
    }

    Node* kth(Node* node, const T& k) const {
        if (node == nullptr || k == 0 || k > size(node)) return nullptr;
        if (k == size(node->left) + 1) return node;
        if (k <= size(node->left)) return kth(node->left, k);
        return kth(node->right, k - size(node->left) - 1);
    }

    void insert(Node*& node, const T& value) {
        if (node == nullptr) node = new Node(value);
        else if (node->value_ == value) return;
        else if (node->value_ > value) insert(node->left, value);
        else if (node->value_ < value) insert(node->right, value);
        balance(node);
    }

    Node* extractMin(Node*& node) {
        if (node->left == nullptr) {
            Node* res = node;
            node = node->right;
            res->right = nullptr;
            return res;
        }
        Node* res = extractMin(node->left);
        balance(node);
        return res;
    }

    void erase(Node*& node, const T& value) {
        if (node == nullptr) return;
        if (value < node->value_) erase(node->left, value);
        else if (value > node->value_) erase(node->right, value);
        else {
            Node* left = node->left;
            Node* right = node->right;
            node->left = nullptr;
            node->right = nullptr;
            delete node;
            if (right == nullptr) node = left;
            else {
                Node* mn = extractMin(right);
                mn->left = left;
                mn->right = right;
                node = mn;
                balance(node);
            }
            return;
        }
        balance(node);
    }

    void print(Node* node) const {
        if (node == nullptr) return;
        print(node->left);
        std::cout << node->value_  << " ";
        print(node->right);
    }

public:
    void insert(const T& value) {insert(root, value);}
    bool find (const T& value) const {return find(root, value);}
    const T* next(const T& value) const {
        Node* res = next(root, value);
        return res ? &res->value_ : nullptr;
    }
    const T* prev(const T& value) const {
        Node* res = prev(root, value);
        return res ? &res->value_ : nullptr;
    }
    const T* kth(uint64_t k) const {
        Node* res = kth(root, k);
        return res ? &res->value_ : nullptr;
    }
    void print() {print(root);}
    AVLTree() = default;
    ~AVLTree() {delete root;}
    uint64_t h() {return height(root);}
    void erase(const T& value) {erase(root, value);}
};

int main() {
    AVLTree<int64_t> tr;
    std::string s;
    int64_t x;
    while (std::cin >> s >> x) {
        if (s == "insert") tr.insert(x);
        else if (s == "delete") tr.erase(x);
        else if (s == "exists") std::cout << (tr.find(x) ? "true" : "false") << '\n';
        else if (s == "next") {
            auto res = tr.next(x);
            if (res) std::cout << *res << '\n';
            else std::cout << "none\n";
        } else if (s == "prev") {
            auto res = tr.prev(x);
            if (res) std::cout << *res << '\n';
            else std::cout << "none\n";
        } else if (s == "kth") {
            auto res = tr.kth(x);
            if (res) std::cout << *res << '\n';
            else std::cout << "none\n";
        }
    }
    return 0;
}