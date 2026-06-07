#include <iostream>
#include <cstdint>
#include <vector>
#include <climits>

struct Node {int64_t key, left, right;};

bool check(int64_t ver, const std::vector<Node>& v, int64_t mi, int64_t ma) {
    if (ver == -1) return true;
    if (v[ver].key >= ma || v[ver].key < mi) return false;
    return check(v[ver].left, v, mi, v[ver].key) && check(v[ver].right, v, v[ver].key, ma);
}

int main() {
    uint64_t N;
    int64_t mi = INT64_MIN, ma = INT64_MAX;
    std::cin >> N;
    std::vector<Node> v(N);
    for (uint64_t i = 0; i < N; ++i) std::cin >> v[i].key >> v[i].left >> v[i].right;
    if (check(0, v, mi, ma)) std::cout << "CORRECT";
    else std::cout << "INCORRECT";
}