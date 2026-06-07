#include <iostream>
#include <cstdint>

template<typename T>
class AVLTree {
    struct Node{
        T value_;
        uint64_t height = 1;
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

    void update(Node* node) {
        if (node != nullptr) node->height = std::max(height(node->left), height(node->right)) + 1;
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
        node left;
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
    
    bool find(Node*& node, const T& value) const {
        if (node == nullptr) return false;
        if (node->value_ == value) return true;
        if (node->value_ > value) return find(node->left, value);
        if (node->value_ < value) return find(node->right, value);
    }

    void insert(Node*& node, const T& value) {
        if (node == nullptr) node = new Node(value);
        else if (node->value_ == value) ++node->cnt;
        else if (node->value_ > value) insert(node->left, value);
        else if (node->value_ < value) insert(node->right, value);
        balance(node);
    }

    void print(Node*& node) const {
        if (node == nullptr) return;
        print(node->left);
        std::cout << node->value_  << " ";
        print(node->right);
    }

public:
    void insert(const T& value) {insert(root, value);}
    bool find (const T& value) const {return find(root, value);}
    void print() {print(root);}
    AVLTree() = default;
    ~AVLTree() {delete root;}
    uint64_t h() {return height(root);}
};

int main() {
    AVLTree<int64_t> tr;
    int64_t x;
    while (std::cin >> x && x != 0) tr.insert(x);
    tr.print();
    return 0;
}