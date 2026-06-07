#include <iostream>
#include <cstdint>

template<typename T>
class Tree {
    struct Node{
        T value_;
        uint64_t cnt = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(const T &value): value_(value) {}
        ~Node() {
            delete left;
            delete right;
        }
    } *root = nullptr;
    
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
    }

    void print(Node*& node) {
        if (node == nullptr) return;
        print(node->left);
        std::cout << node->value_ << " " << node->cnt << "\n";
        print(node->right);
    }

public:
    void insert(const T& value) {insert(root, value);}
    bool find (const T& value) const {return find(root, value);}
    void print() {print(root);}
    Tree() = default;
    ~Tree() {delete root;}
};

int main() {
    Tree<int64_t> tr;
    int64_t x;
    while (std::cin >> x && x != 0) tr.insert(x);
    tr.print();
    return 0;
}