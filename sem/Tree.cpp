#include <iostream>

template<typename T>
class Tree {
    struct Node{
        T value_;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(const T &value): value_(value) {}
        ~Node() {
            delete left;
            delete right;
        }
    }; *root = nullptr;
    
    bool find(Node*& node, const T& value) const {
        if (node == nullptr) return false;
        if (node->value_ == value) return true;
        if (node->value_ > value) return find(node->left, value);
        if (node->value_ < value) return find(node->right, value)
    }

    void insert(Node*& node, const T& value) {
        if (node == nullptr) node = new Node(value);
        else if (node->value_ == value) return;
        else if (node->value_ > value) insert(node->left, value);
        else if (node->value_ < value) insert(node->right, value)
    }

public:
    void insert(const T& value) {
        
    }

    bool find (const T& value) const {return find(root, value);}
    Tree() = default;
    ~Tree() {delete root;}
};

int main() {
    return 0;
}