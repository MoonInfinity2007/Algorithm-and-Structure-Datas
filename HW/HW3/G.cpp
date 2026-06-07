#include <iostream>
#include <cstdint>
#include <vector>

struct Node {int64_t key, left, right;};

int64_t su(int64_t ver, const std::vector<Node>& v) {
    if (ver == -1) return 0;
    return su(v[ver].left, v) + su(v[ver].right, v) + v[ver].key;
}

int main() {
    uint64_t N;
    std::cin >> N;
    std::vector<Node> v(N);
    for (uint64_t i = 0; i < N; ++i) std::cin >> v[i].key >> v[i].left >> v[i].right;
    for (uint64_t i = 0; i < N; ++i) std::cout << su(i, v) << " ";
}