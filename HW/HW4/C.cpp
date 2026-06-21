#include <iostream>
#include <cstdint>

const int64_t INF = -(1LL << 60);

struct Data {
    int64_t dp[2][2];
    Data() {
        dp[0][0] = INF;
        dp[0][1] = INF;
        dp[1][0] = INF;
        dp[1][1] = INF;
    }
};

Data merge(Data& left, Data& right) {
    Data res;
    for (int left1 = 0; left1 <= 1; ++left1) {
        for (int left2 = 0; left2 <= 1; ++left2) {
            for (int right1 = 0; right1 <= 1; ++right1) {
                for (int right2 = 0; right2 <= 1; ++right2) {
                    if (left.dp[left1][left2] == INF) continue;
                    if (right.dp[right1][right2] == INF) continue;
                    if (left2 == 1 && right1 == 1) continue;
                    res.dp[left1][right2] = std::max(res.dp[left1][right2], left.dp[left1][left2] + right.dp[right1][right2]);
                }
            }
        }
    }
    return res;
}

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    uint64_t begin = 0, end = 0;
    Data data;
    Node(uint64_t begin, uint64_t end): begin(begin), end(end) {
        if (begin + 1 < end) {
            uint64_t mid = (begin + end) / 2;
            left = new Node(begin, mid);
            right = new Node(mid, end);
        }
    }
    ~Node() {
        delete left;
        delete right;
    }
};

class Tree {
    Node* root = nullptr;

    void set(Node*& node, uint64_t index, int64_t value) {
        if (node->begin + 1 == node->end) {
            node->data = Data();
            node->data.dp[0][0] = 0;
            node->data.dp[1][1] = value;
            return;
        }
        if (node->left->end > index) set(node->left, index, value);
        else set(node->right, index, value);
        node->data = merge(node->left->data, node->right->data);
    }

    int64_t get_answer(Node*& node) {
        int64_t ans = INF;
        for (int first = 0; first <= 1; ++first) {
            for (int last = 0; last <= 1; ++last) ans = std::max(ans, node->data.dp[first][last]);
        }
        return ans;
    }

public:
    Tree(uint64_t begin, uint64_t end){root = new Node(begin, end);};
    void set(uint64_t index, int64_t value) {set(root, index, value);}
    int64_t get() {return get_answer(root);}
};

int main() {
    int64_t N, M;
    std::cin >> N >> M;
    Tree tree(1, N+1);
    for (int64_t i = 0; i < N; ++i) {
        int64_t x;
        std::cin >> x;
        tree.set(i + 1, x);
    }
    
    std::cout << tree.get() << "\n";

    while (M--) {
        int64_t b, t;
        std::cin >> b >> t;
        tree.set(b, t);
        std::cout << tree.get() << "\n";
    }
    return 0;
}